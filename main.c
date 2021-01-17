#include "xparameters.h"
#include "xil_io.h"
#include "sleep.h"

#include "zed_hdmi.h"
#include "ps_emio.h"

#include "image.h"

static int ps_emio_ready = 0;
static int hdmi_ready = 0;

static int cleanup_system();
static int init_system();

int main() {
	xil_printf("Zedboard Visual Test.\r\n");

	int status = init_system();

	if (status != XST_SUCCESS) {
		if (ps_emio_ready) {
			if (status == XST_NO_ACCESS) {
				oled_printstr("Error during HDMI setup.\nHPD is not high.\nConnect HDMI cable.");
			} else {
				oled_printstr("General error during HDMI setup.");
			}
		}

		xil_printf("Error during system init. Status: %x.\r\n", status);
		sleep(30);
	} else {
		if (ps_emio_ready) {
			oled_printstr("Zedboard HDMI\nTest Start!");
		}

		// Configure MM2S_VDMACR to 0x8B
		Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0x00, 0x8B);

		// Set the start addresses of the 3 frame buffers
		Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0x5C, (u32)&image_data); // MM2S_Start_Address1 0x10000000

		// Set the video resolution
		// HSIZE is in bytes: we have 2 bytes per pixel.
		Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0x58, 1920*2); // MM2S_FRMDLY_STRIDE
		Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0x54, 1920*2); // MM2S_HSIZE
		Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0x50, 1080); // MM2S_VSIZE

		sleep(180);
	}

	return cleanup_system();
}

// Initialize the system
static int init_system() {
	int status;

	// Start by setting up EMIO to have access to the OLED.
	if (init_ps_emio() != XST_SUCCESS) {
    	xil_printf("Error: Could not setup PS EMIO connections. Quitting.\r\n");
    	return XST_FAILURE;
    }

	ps_emio_ready = 1;

	// Then set up the HDMI
	if ((status = init_hdmi_interface()) != XST_SUCCESS) {
		return status;
	}

	hdmi_ready = 1;

	return XST_SUCCESS;
}

// Only clean up modules that we successfully started.
static int cleanup_system() {
	if (ps_emio_ready) {
		cleanup_ps_emio();
	}

	if (hdmi_ready) {
		cleanup_hdmi_interface();
	}

	return (ps_emio_ready && hdmi_ready) ? XST_SUCCESS : XST_FAILURE;
}
