#ifndef __OLED_FONT_H__
#define __OLED_FONT_H__

// Font data for all ASCII characters to display on the OLED.
// From: http://www.harald-rosenfeldt.de/2018/01/24/zedboard-using-the-oled-display/
// But flipped for the display
static u8 oled_font_array[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xfa, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0x00,
		0x00, 0x24, 0x64, 0x3c, 0x26, 0x64, 0x3c, 0x26,
		0x00, 0x4c, 0x92, 0x92, 0xfe, 0x92, 0x92, 0x64,
		0x00, 0x84, 0x4a, 0x24, 0x10, 0x48, 0xa4, 0x42,
		0x00, 0x14, 0x1a, 0x44, 0xaa, 0x72, 0x0a, 0x04,
		0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x82, 0x44, 0x38, 0x00, 0x00,
		0x00, 0x00, 0x38, 0x44, 0x82, 0x00, 0x00, 0x00,
		0x00, 0xa8, 0xa8, 0x70, 0x70, 0xa8, 0xa8, 0x00,
		0x00, 0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x00,
		0x00, 0x00, 0x00, 0x0c, 0x0a, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
		0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02,
		0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x7c, 0x00,
		0x00, 0x00, 0x00, 0x02, 0xfe, 0x82, 0x00, 0x00,
		0x00, 0x00, 0x76, 0x92, 0x8a, 0x86, 0x42, 0x00,
		0x00, 0x00, 0x6c, 0x92, 0x92, 0x82, 0x44, 0x00,
		0x00, 0x00, 0x08, 0xfe, 0x48, 0x28, 0x18, 0x00,
		0x00, 0x00, 0x8e, 0x92, 0x92, 0x92, 0xe4, 0x00,
		0x00, 0x00, 0x0e, 0x12, 0x92, 0x52, 0x3c, 0x00,
		0x00, 0x00, 0xc0, 0xb0, 0x88, 0x84, 0xc2, 0x00,
		0x00, 0x00, 0x6c, 0x92, 0x92, 0x92, 0x6c, 0x00,
		0x00, 0x00, 0x78, 0x94, 0x92, 0x90, 0x60, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x0c, 0x4a, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x44, 0x28, 0x28, 0x10, 0x00, 0x00,
		0x00, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x00,
		0x00, 0x00, 0x10, 0x28, 0x28, 0x44, 0x00, 0x00,
		0x00, 0x00, 0x40, 0xa0, 0x9a, 0x80, 0x40, 0x00,
		0x00, 0x74, 0x8a, 0xb2, 0xaa, 0xba, 0x82, 0x7c,
		0x00, 0x02, 0x3e, 0x52, 0x90, 0x52, 0x3e, 0x02,
		0x00, 0x6c, 0x92, 0x92, 0x92, 0x92, 0xfe, 0x82,
		0x00, 0x44, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38,
		0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0xfe, 0x82,
		0x00, 0xc6, 0x82, 0xba, 0x92, 0x92, 0xfe, 0x82,
		0x00, 0xc0, 0x80, 0xb8, 0x90, 0x92, 0xfe, 0x82,
		0x00, 0x10, 0x5c, 0x92, 0x92, 0x82, 0x44, 0x38,
		0x00, 0x82, 0xfe, 0x10, 0x10, 0x10, 0xfe, 0x82,
		0x00, 0x00, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x00,
		0x00, 0x80, 0x80, 0xfc, 0x82, 0x82, 0x02, 0x0c,
		0x00, 0x82, 0x86, 0x48, 0x30, 0x10, 0xfe, 0x82,
		0x00, 0x06, 0x02, 0x02, 0x02, 0x82, 0xfe, 0x82,
		0x00, 0x82, 0xfe, 0x42, 0x30, 0x42, 0xfe, 0x82,
		0x00, 0x80, 0xfe, 0x88, 0x30, 0x42, 0xfe, 0x82,
		0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38,
		0x00, 0x60, 0x90, 0x90, 0x90, 0x92, 0xfe, 0x82,
		0x00, 0x32, 0x4a, 0x86, 0x84, 0x84, 0x48, 0x30,
		0x00, 0x62, 0x96, 0x98, 0x90, 0x90, 0xfe, 0x82,
		0x00, 0xcc, 0x92, 0x92, 0x92, 0x92, 0x92, 0x66,
		0x00, 0xc0, 0x80, 0x82, 0xfe, 0x82, 0x80, 0xc0,
		0x00, 0x80, 0xfc, 0x82, 0x02, 0x82, 0xfc, 0x80,
		0x00, 0x80, 0xf0, 0x8c, 0x02, 0x8c, 0xf0, 0x80,
		0x00, 0x80, 0xf8, 0x86, 0x28, 0x86, 0xf8, 0x80,
		0x00, 0x82, 0x82, 0x6c, 0x10, 0x6c, 0x82, 0x82,
		0x00, 0x80, 0xc0, 0x22, 0x1e, 0x22, 0xc0, 0x80,
		0x00, 0x86, 0xc2, 0xa2, 0x92, 0x8a, 0x86, 0xc2,
		0x00, 0x00, 0x00, 0x82, 0x82, 0xfe, 0x00, 0x00,
		0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
		0x00, 0x00, 0x00, 0xfe, 0x82, 0x82, 0x00, 0x00,
		0x00, 0x20, 0x40, 0x80, 0x80, 0x40, 0x20, 0x00,
		0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00,
		0x00, 0x02, 0x3c, 0x52, 0x52, 0x52, 0x2c, 0x00,
		0x00, 0x0c, 0x12, 0x12, 0x12, 0xfc, 0x82, 0x00,
		0x00, 0x00, 0x24, 0x42, 0x42, 0x42, 0x3c, 0x00,
		0x00, 0x02, 0xfc, 0x92, 0x12, 0x12, 0x0c, 0x00,
		0x00, 0x00, 0x34, 0x52, 0x52, 0x52, 0x3c, 0x00,
		0x00, 0x00, 0x90, 0x92, 0x7e, 0x12, 0x00, 0x00,
		0x00, 0x80, 0xfc, 0x92, 0x92, 0x92, 0x64, 0x00,
		0x00, 0x02, 0x1e, 0x22, 0x20, 0x12, 0xfe, 0x82,
		0x00, 0x00, 0x00, 0x02, 0xbe, 0x22, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xbc, 0x22, 0x02, 0x00, 0x00,
		0x00, 0x42, 0x42, 0x24, 0x18, 0x08, 0xfe, 0x82,
		0x00, 0x00, 0x02, 0x02, 0xfe, 0x82, 0x02, 0x00,
		0x00, 0x02, 0x7e, 0x40, 0x3e, 0x40, 0x7e, 0x42,
		0x00, 0x02, 0x3e, 0x42, 0x40, 0x22, 0x7e, 0x42,
		0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x3c, 0x00,
		0x00, 0x60, 0x90, 0x90, 0x92, 0xfe, 0x82, 0x00,
		0x00, 0x82, 0xfe, 0x92, 0x90, 0x90, 0x60, 0x00,
		0x00, 0x20, 0x40, 0x40, 0x22, 0x7e, 0x42, 0x00,
		0x00, 0x00, 0x6c, 0x52, 0x52, 0x52, 0x26, 0x00,
		0x00, 0x00, 0x04, 0x22, 0x22, 0xfc, 0x20, 0x00,
		0x02, 0x7e, 0x44, 0x02, 0x02, 0x7c, 0x40, 0x00,
		0x00, 0x40, 0x70, 0x4c, 0x02, 0x4c, 0x70, 0x40,
		0x00, 0x40, 0x78, 0x46, 0x18, 0x46, 0x78, 0x40,
		0x00, 0x42, 0x46, 0x28, 0x10, 0x28, 0x46, 0x42,
		0x00, 0x80, 0xc0, 0xa0, 0x1c, 0xa2, 0xc2, 0x80,
		0x00, 0x46, 0x62, 0x52, 0x4a, 0x46, 0x62, 0x00,
		0x00, 0x00, 0x00, 0x82, 0x6c, 0x10, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x10, 0x6c, 0x82, 0x00, 0x00, 0x00,
		0x00, 0x18, 0x08, 0x08, 0x10, 0x10, 0x18, 0x00,
		0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55,
};

#endif
