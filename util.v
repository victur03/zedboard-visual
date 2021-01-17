module video_to_zedboard(
    vid_io_in_active_video,
    vid_io_in_data,
    vid_io_in_field,
    vid_io_in_hblank,
    vid_io_in_hsync,
    vid_io_in_vblank,
    vid_io_in_vsync,

    HD_DE,
    HD_D,
    HD_HSYNC,
    HD_VSYNC);

  (* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_io_in ACTIVE_VIDEO" *) input vid_io_in_active_video;
  (* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_io_in DATA" *) input [23:0]vid_io_in_data;
  (* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_io_in FIELD" *) input vid_io_in_field;
  (* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_io_in HBLANK" *) input vid_io_in_hblank;
  (* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_io_in HSYNC" *) input vid_io_in_hsync;
  (* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_io_in VBLANK" *) input vid_io_in_vblank;
  (* X_INTERFACE_INFO = "xilinx.com:interface:vid_io:1.0 vid_io_in VSYNC" *) input vid_io_in_vsync;

  output HD_DE;
  output [15:0] HD_D;
  output HD_HSYNC;
  output HD_VSYNC;

  assign HD_DE = vid_io_in_active_video;

  assign HD_D[15:8] = vid_io_in_data[7:0];
  assign HD_D[7:0] = vid_io_in_data[15:8];

  assign HD_HSYNC = vid_io_in_hsync;
  assign HD_VSYNC = vid_io_in_vsync;

endmodule
