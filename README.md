# Zedboard HDMI and OLED Tutorial (In Progress)

The goal of this tutorial is to show how to program the Zedboard in order to display images over HDMI and to display text on its built-in OLED display.
Both the OLED and HDMI will be controlled from software by the ARM core inside of the Zynq-7000.

For the OLED, this tutorial provides a `printstr()`-like function to print up to 4 lines of text on the built-in display.
For the HDMI, this tutorial provides a method to send a raw image stored inside of the FPGA's DDR memory through the HDMI link. It reads the image from memory by using a VDMA IP, and then transmits it to the ADV7511 HDMI controller on the Zedboard.

The HDMI and OLED sections are in separate files, and can each be implemented indepentedly, without needing the other.
Reference material related to the Zedboard can be found [here](https://reference.digilentinc.com/reference/programmable-logic/zedboard/start).

[Zedboard Pin Assignment](https://reference.digilentinc.com/_media/reference/programmable-logic/zedboard/zedboard_ug.pdf)

[Zedboard Schematic](https://reference.digilentinc.com/_media/reference/programmable-logic/zedboard/zedboard_sch.pdf)

## PL Setup

The first step is to set up the FPGA's PL (Programmable Logic, the FPGA's reprogrammable hardware). While everything will be controlled from the PS (Processing System, the ARM core inside of the FPGA), the PL is required to route the signals that the PS generates to the appropriate pins, and to generate signals that the PS is unable to create.

The PL setup is done using Vivado. A quick start guide can be found [here](https://reference.digilentinc.com/vivado/getting_started/start).

1. Create a new Vivado project that targets the Zedboard.
2. Include the constraints file and the Verilog file found in the repository.
3. Create a new block design.
4. Add a Zynq Processing System to the block design and run block automation.

### OLED Wiring

The Zedboard has an Inteltronic/Wisechip UG-2832HSWEG04 OLED Display ([reference](https://cdn-shop.adafruit.com/datasheets/UG-2832HSWEG04.pdf)).

As seen in the schematic, the OLED Display has multiple pins connected to the FPGA.
In order to send commands and data to the OLED, the FPGA uses a reduced subset of the SPI protocol. The FPGA has two wires connected to the OLED: a clock wire, and a data wire. Each time the OLED sees a rising edge on the clock wire, it reads the bit on the data wire.
In addition, there is a wire called the D/C (Data/Control) wire. The OLED memory is split into two parts: the data memory, and the control registers. The data memory stores which pixels should be enabled to display the desired text. The control registers store configuration information about the OLED display itself, such as whether the OLED is currently turned on or in sleep mode. When the OLED receives bits over SPI, the D/C wire determines where those bits should be sent. If D/C=1, then the bits are sent directly in the OLED's data memory. If D/C=0, the bits are sent to the OLED's controller. The controller decodes the bits into commands, and it sets control registers accordingly. Finally, there is also a reset wire.

Thus, the high-level procedure for using the OLED is as follows: reset the OLED, set D/C=0, send the "turn on" command over SPI, set D/C=1, send the pixel bitmap over SPI.

The Zynq-7000 has a feature called EMIO, which allows it to send and receive data in common protocols directly from the ARM core. Namely, the Zynq-7000 ARM core has built-in SPI and GPIO controllers. This means the PL does not need to do any processing at all. All signals will be generated in the ARM core, and the PL simply needs to route those signals to the appropriate pins.

In a full SPI implementation, multiple master and slave devices can be connected using the same wires. A special "chip select" wire is used by a master to tell a specific slave that it is sending data only to it. In addition, if other masters see that a specific slave's "slave select" line is toggled, they will not send any messages to that slave to avoid interference. In SPI, the "slave select" line is active low. Therefore, if the ARM core's SPI controller detects that the OLED's "slave select" is low, it will believe that another master is talking to the OLED, and it will not send any data. Hence, it is necessary to tie the ARM core's "slave select" line to 1, so that the controller will transmit data.

1. Double click the Zynq to customize it.
   1. In MIO Configuration, I/O Peripherals, enable SPI 0 connected to EMIO.
   2. In MIO Configuration, I/O Peripherals, enable EMIO GPIO of width 2. These will be used for the reset and control signals.
   3. Click OK and exit.
2. The Zynq block now has new output connections.
3. In the block design, create new output ports called `OLED_DC`, `OLED_RES`, `OLED_SCLK`, `OLED_SDIN`. You can verify that they are connected to the OLED on lines 136-139 of the constraints file.
5. Add a "Constant" IP to the block design. Double click it, and configure it to output a single 1.
6. Expand the `SPI_0` output of the Zynq block. Connect the output of the "Constant" IP to `SPI0_SS_I` (the SPI slave select signal). Connect `SPI0_MOSI_O` to `OLED_SDIN` (the SPI data signal). Connect `SPI0_SCLK_O` to `OLED_SCLK` (the SPI clock signal).
7. Add 2 "Slice" IPs. For both, set `Din Width` to 2. For one slice, set `Din From` and `Din Down To` to 0, for the other, set `Din From` and `Din Down To` to 1.
8. Connect `GPIO_O` to both "Slice" IPs. Connect the output of the slice that captures `GPIO_O[0]` to `OLED_RES`. Connect the output of the slice that captures `GPIO_O[1]` to `OLED_DC`.
9. The Wiring for the OLED is ready, and should look like this.

### HDMI Wiring

The HDMI link is handled by an ADV7511 chip.
