#!/usr/bin/python3

import numpy as np
import cv2

# Target Width and Height
W, H = 1920, 1080

def get_yuv(img="pic.jpg"):
  # Read image and convert to YCrCb
  img = cv2.imread(img)
  img = cv2.resize(img, (W, H))
  img = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)

  # Subsample image: alternate Cb and Cr values
  sub = np.empty((H, W, 2), dtype=img.dtype)

  sub[:,:,0] = img[:,:,0]

  sub[:,0::2,1] = img[:,0::2,2] # Get Cb
  sub[:,1::2,1] = img[:,1::2,1] # Get Cr

  return sub

def make_c_header(img):
  # Generate C file for FPGA
  with open("image.h", "w") as f:
    text_lines = ["#ifndef __IMAGE_H__\n", "#define __IMAGE_H__\n", "\n", "u8 image_data[] __attribute__ ((aligned (64))) = {\n"]

    for line in range(H):
      text_line = "  "
      for col in range(W):
        text_line += hex(img[line, col, 0]) + ", " + hex(img[line, col, 1]) + ", "

      text_line += "\n"
      text_lines.append(text_line)

    text_lines.extend(["};\n", "\n", "#endif\n"])

    f.writelines(text_lines)

def main():
    name = input("Image Filename: ")

    img = get_yuv(name)
    make_c_header(img)

main()
