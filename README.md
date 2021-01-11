# Zedboard HDMI ADV7511 w/ VDMA and OLED Tutorial

This tutorial shows how to set up the Zedboard so that it can display images over HDMI and so that it can display text on its built-in OLED display.

## Vivado Setup

First, start a new project in Vivado. Vivado will generate the bitstream that will program the FPGA. To set up Vivado, a tutorial can be found [here](https://reference.digilentinc.com/vivado/getting_started/start).

1. Create a new Vivado project that targets the Zedboard.
2. Include the constraints file found in the repository.
3. Create a new block design.

### OLED Wiring

The OLED display built on the Zedboard uses the SPI protocol to receive display commands. The ARM core inside the FPGA can generate SPI signals, so we will wire the ARM core directly to the OLED, without using the FPGA PL. In addition, the OLED requires a reset and control signal that will also be generates by the ARM core.

1. Add a Zynq Processing System to the block design and run block automation.
2. Double click the Zynq to customize it.
   1. In MIO Configuration, I/O Peripherals, enable SPI 0 connected to EMIO.
   2. In MIO Configuration, I/O Peripherals, enable EMIO GPIO of width 2. These will be used for the reset and control signals.
   3. In Clock Configuration, PL Fabric Clocks, disable FCLK_CLK0. It will not be needed.
   4. Click OK and exit.
3. The Zynq block now has new output connections.
4. In the block design, create new output ports called OLED_DC, OLED_RES, OLED_SCLK, OLED_SDIN. You can verify that they are connected to the OLED on lines 136-139 of the constraints file.
5. Add the "Constant" IP to the block design. Double click it, and configure it to output a single 1.
6. Expand the SPI_0 output of the Zynq block. Connect the output of the Constant block to SPI0_SS_I. Connect SPI0_MOSI_O to OLED_SDIN. Connect SPI0_SCLK_O to OLED_SCLK. The pin SPI0_SS_I has to be connected to 1, because it is used by the ARM core to detect whether there are multiple masters on the SPI connection. If SPI0_SS_I is 0, that indicates that another master has grabbed the line, and the ARM core would refuse to send any data over SPI.
7. Add 2 slice IPs. For both, set Din Width to 2. For one, set Din From & Din Down To to 0, for the other, set Din From & Din Down To to 1.
8. Connect GPIO_O to both Slice IPs. Connect the output of the slice that captures signal 0 to OLED_RES. Connect the output of the slice that captures signal 1 to OLED_DC.
9. The Wiring for the OLED is ready, and should look like this.

### HDMI Wiring

The HDMI link is handled by an ADV7511 chip.
