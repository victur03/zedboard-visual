#include "xparameters.h"
#include "xiicps.h"
#include "sleep.h"

#include "zed_hdmi.h"

// Global EMIO IIC instance
static XIicPs iic_instance;

// Configure the EMIO IIC driver.
static int configure_emio_iic() {
	XIicPs_Config *iic_config_ptr = XIicPs_LookupConfig(XPAR_XIICPS_0_DEVICE_ID);

	if (iic_config_ptr == NULL) {
		return XST_FAILURE;
	}

	int status = XIicPs_CfgInitialize(&iic_instance, iic_config_ptr, iic_config_ptr->BaseAddress);

	if (status != XST_SUCCESS) {
		return status;
	}

	// Set the IIC serial clock rate to 400 kHz.
	return XIicPs_SetSClk(&iic_instance, HDMI_IIC_SCLK_RATE);
}


// Helper function for reading the value of registers on the HDMI chip
// The function reads 4 consecutive regs, and stores their values in *dst.
// To read a reg, we first write the desired address, and without releasing the bus, we let the ADV7511 send data back.
// Therefore, we need to use repeated start.
static int iic_read_reg(u8 reg_addr, u32 *dst) {
	int status;

	// Enable repeated start
	if ((status = XIicPs_SetOptions(&iic_instance, XIICPS_REP_START_OPTION)) != XST_SUCCESS) {
		return status;
	}

	// Send data
	if ((status = XIicPs_MasterSendPolled(&iic_instance, &reg_addr, sizeof(reg_addr), HDMI_IIC_ADDR)) != XST_SUCCESS) {
		return status;
	}

	// Disable repeated start
	if ((status = XIicPs_ClearOptions(&iic_instance, XIICPS_REP_START_OPTION)) != XST_SUCCESS) {
		return status;
	}

	// Recv data
	if ((status = XIicPs_MasterRecvPolled(&iic_instance, (u8 *)dst, sizeof(*dst), HDMI_IIC_ADDR)) != XST_SUCCESS) {
		return status;
	}

	// Wait till all the data is received.
	while (XIicPs_BusIsBusy(&iic_instance));

	return XST_SUCCESS;
}


// The IIC data that will be sent to the HDMI chip.
static u8 hdmi_init_seq[] = {
		// Power-up the Tx
		0x41, 0x10,

		// Fixed registers that must be set on power up
		0x98, 0x03,
		0x9A, 0xE0,
		0x9C, 0x30,
		0x9D, 0x61,
		0xA2, 0xA4,
		0xA3, 0xA4,
		0xE0, 0xD0,
		0x55, 0x12,
		0xF9, 0x00,

		// Set up the video input mode (Table 18)
		0x15, 0x01, // Select YCbCr 422
		0x16, 0x3D, // Set 444 output, 8 bit, style 3, YCrCb clipping
		0x17, 0x02, // Set aspect ratio to 16:9, external DE
		0x48, 0x08, // Set right justified data

		// Set up the video output mode
		0xAF, 0x04, // Set DVI mode
		0x40, 0x00, // Disable non-video packets
		0x4C, 0x04, // Set 24-bit output color depth
};

// The IIC data that will set up the YCbCr to RGB CSC.
// HDTV YCbCr (Limited Range) to RGB (Limited Range)
static u8 hdmi_csc_seq[] = {
		0x18, // Address of first reg.

		// A B C rows.
		0xAC, 0x53, 0x08, 0x00, 0x00, 0x00, 0x19, 0xD6,
		0x1C, 0x56, 0x08, 0x00, 0x1E, 0x88, 0x02, 0x91,
		0x1F, 0xFF, 0x08, 0x00, 0x0E, 0x85, 0x18, 0xBE,
};

// Configure the ADV7511
static int configure_hdmi_tx() {
	int status;

	// Wait 200 ms for the HDMI chip to be ready
	usleep(200000);

	// Verify that HPD is high
	u32 hpd_reg;

	if ((status = iic_read_reg(HDMI_HPD_REG, &hpd_reg)) != XST_SUCCESS) {
		return status;
	}

	if (!(hpd_reg & HDMI_HPD_MASK)) {
		return XST_NO_ACCESS;
	}

	// Send init data
	for (u8 *msg_ptr = hdmi_init_seq; msg_ptr < hdmi_init_seq + sizeof(hdmi_init_seq); msg_ptr += HDMI_IIC_MSG_LEN) {
		if ((status = XIicPs_MasterSendPolled(&iic_instance, msg_ptr, HDMI_IIC_MSG_LEN, HDMI_IIC_ADDR)) != XST_SUCCESS) {
			return status;
		}

		while (XIicPs_BusIsBusy(&iic_instance));
	}

	// Send CSC data.
	if ((status = XIicPs_MasterSendPolled(&iic_instance, hdmi_csc_seq, sizeof(hdmi_csc_seq), HDMI_IIC_ADDR)) != XST_SUCCESS) {
		return status;
	}

	while (XIicPs_BusIsBusy(&iic_instance));

	return XST_SUCCESS;
}

// Set up EMIO IIC, then configure the ADV7511.
int init_hdmi_interface() {
	int status = configure_emio_iic();

	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	return configure_hdmi_tx();
}

// Cleanup HDMI modules
// Turns off the chip
void cleanup_hdmi_interface() {
	// Send HDMI off command
	u8 hdmi_off_cmd[] = {0x41, 0x50};

	if (XIicPs_MasterSendPolled(&iic_instance, hdmi_off_cmd, sizeof(hdmi_off_cmd), HDMI_IIC_ADDR) != XST_SUCCESS) {
		return;
	}

	while (XIicPs_BusIsBusy(&iic_instance));
}
