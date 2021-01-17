#include "xparameters.h"
#include "xgpiops.h"
#include "xspips.h"
#include "sleep.h"

#include "oled_font.h"
#include "ps_emio.h"

// Global Instances for the EMIO GPIO & SPI
static XGpioPs gpio_instance;
static XSpiPs spi_instance;

// Configure all the EMIO GPIO and SPI pins of the PS
static int configure_emio() {
	// Configure EMIO GPIO pins
	XGpioPs_Config *gpio_config_ptr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);

	if (gpio_config_ptr == NULL || XGpioPs_CfgInitialize(&gpio_instance, gpio_config_ptr, gpio_config_ptr->BaseAddr) != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Enable all GPIO pins.
	XGpioPs_SetDirectionPin(&gpio_instance, EMIO_PIN_OLED_RES, 1);
	XGpioPs_SetOutputEnablePin(&gpio_instance, EMIO_PIN_OLED_RES, 1);

	XGpioPs_SetDirectionPin(&gpio_instance, EMIO_PIN_OLED_DC, 1);
	XGpioPs_SetOutputEnablePin(&gpio_instance, EMIO_PIN_OLED_DC, 1);


	// Configure EMIO SPI pins
	XSpiPs_Config *spi_config_ptr = XSpiPs_LookupConfig(XPAR_XSPIPS_0_DEVICE_ID);

	if (spi_config_ptr == NULL || XSpiPs_CfgInitialize(&spi_instance, spi_config_ptr, spi_config_ptr->BaseAddress) != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Set PS as SPI master, slow down SPI clock for OLED
	XSpiPs_SetOptions(&spi_instance, XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);
	XSpiPs_SetClkPrescaler(&spi_instance, XSPIPS_CLK_PRESCALE_256);

	return XST_SUCCESS;
}


// The initialization sequence sent to the OLED. Found in the reference sheet.
static u8 oled_init_seq[] = {0xAE, 0xD5, 0x80, 0xA8, 0x1F, 0xD3, 0x00, 0x40,
		                     0x8D, 0x14, 0xA1, 0xC8, 0xDA, 0x02, 0x81, 0x8F,
							 0xD9, 0xF1, 0xDB, 0x40, 0xA4, 0xA6};

// Configure the OLED display itself
static int configure_oled() {
	// Reset the OLED. RES is active low.
	XGpioPs_WritePin(&gpio_instance, EMIO_PIN_OLED_RES, 0);

	// Wait for reset, then disable it.
	usleep(100);
	XGpioPs_WritePin(&gpio_instance, EMIO_PIN_OLED_RES, 1);

	// Set D/C to 0, and send control data to initialize the OLED.
	XGpioPs_WritePin(&gpio_instance, EMIO_PIN_OLED_DC, 0);
	XSpiPs_SetSlaveSelect(&spi_instance, 0x01);
	XSpiPs_PolledTransfer(&spi_instance, oled_init_seq, NULL, sizeof(oled_init_seq));

	// Clear Screen
	oled_printstr("");

	// Wait for the OLED to fully power up
	usleep(100000);

	// Turn on OLED
	u8 turn_on_cmd = 0xAF;

	XGpioPs_WritePin(&gpio_instance, EMIO_PIN_OLED_DC, 0);
	XSpiPs_SetSlaveSelect(&spi_instance, 0x01);
	XSpiPs_PolledTransfer(&spi_instance, &turn_on_cmd, NULL, sizeof(turn_on_cmd));

	return XST_SUCCESS;
}


// Set up EMIO GPIO & SPI, then configure the OLED.
int init_ps_emio() {
	// Configure EMIO
	int status = configure_emio();

	if (status != XST_SUCCESS) {
		return status;
	}

	// Configure OLED
	return configure_oled();
}


// Clean up the PS EMIO.
// Turns off the OLED.
void cleanup_ps_emio() {
	// Send OLED off command
	u8 oled_off_cmd = 0xAE;

	XGpioPs_WritePin(&gpio_instance, EMIO_PIN_OLED_DC, 0);
	XSpiPs_SetSlaveSelect(&spi_instance, 0x01);
	XSpiPs_PolledTransfer(&spi_instance, &oled_off_cmd, NULL, sizeof(oled_off_cmd));
}


// We buffer and send the data line-by-line, to use SPI more efficiently.
static u8 line_buf[128];

// Display text on the OLED display
// The OLED has four text lines.
// For each line, we first select the line with a command to D/C=0, and then we send the line's data.
// We buffer the data line-by-line for more efficient transfer.
void oled_printstr(char *str) {
	// Line 0 is selected with command 0xB0, line 1 with 0xB1, etc.
	// However, the display is upside-down on the Zedboard, so we must work backwards.
	for (u8 line_cmd = 0xB3; line_cmd >= 0xB0; line_cmd--) {
		// Set D/C=0 and select line
		XGpioPs_WritePin(&gpio_instance, EMIO_PIN_OLED_DC, 0);
		XSpiPs_SetSlaveSelect(&spi_instance, 0x01);
		XSpiPs_PolledTransfer(&spi_instance, &line_cmd, NULL, sizeof(line_cmd));

		// Write the line to the line buffer. We write character by character.
		// A character is made up of 8 1-pixel-wide columns.
		// Each column is made up of 8 pixel, which are all represented by one byte of data.
		// So each character is represented by 8 bytes of data.
		// If we reached the end of the string or the end of the line, we fill the remainder of the line buffer with
		// empty characters.
		// Again, we must work in reverse due to the upside-down display.
		for (int i = 0; i < 16; i++) {
			if (*str == '\0' || *str == '\n') {
				memset(line_buf + sizeof(line_buf) - 8*(i+1), 0, 8); // Blank char
			} else {
				memcpy(line_buf + sizeof(line_buf) - 8*(i+1), oled_font_array + 8 * (*str), 8); // Copy corresponding char data.
				str++;
			}
		}

		// Set D/C=1 and send line data
		XGpioPs_WritePin(&gpio_instance, EMIO_PIN_OLED_DC, 1);
		XSpiPs_SetSlaveSelect(&spi_instance, 0x01);
		XSpiPs_PolledTransfer(&spi_instance, line_buf, NULL, sizeof(line_buf));

		// Go to next line in string
		if (*str == '\n') str++;
	}
}
