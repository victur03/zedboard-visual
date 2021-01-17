#ifndef __ZED_HDMI_H__
#define __ZED_HDMI_H__

#define HDMI_IIC_SCLK_RATE 400000
#define HDMI_IIC_ADDR 0x39

#define HDMI_IIC_MSG_LEN 2

#define HDMI_HPD_MASK 0b01000000
#define HDMI_HPD_REG 0x42

int init_hdmi_interface();

void cleanup_hdmi_interface();

#endif
