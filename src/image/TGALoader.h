/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#ifndef TGALOADER_H
#define TGALOADER_H
#include "Image.h"

/*
 * BYTE    ITEM         SIZE    DESCRIPTION
 * ****   *****        *****   ************ 
 * 0       Offset         1     Usually 0, 
 *                             add 18 to this value to find the start of the palette/image data.
 * 1       ColorType      1     Image type. 0 = RGB, 1 = Indexed.
 * 2       ImageType      1     0 = None, 1 = Indexed, 2 = RGB, 3 = Greyscale,
 *                            +8 = RLE encoded.
 * 3       PaletteStart   2     Start of palette.
 * 5       PaletteLen     2     Number of palette entries.
 * 7       PalBits        1     Bits per colour entry.
 * 8       X Origin       2     Image X Origin
 * 10      Y Origin       2     Image Y Origin
 * 12      Width          2     Image width (Pixels).
 * 14      Height         2     Image height (Pixels)
 * 16      BPP            1     Bits per pixel (8,16,24 or 32)
 * 17      Orientation    1     If Bit 5 is set, the image will be upside down (like BMP)
 *
 */

#include <iostream>
#include <fstream>
#include <memory.h>

#define IMG_OK              0x1
#define IMG_ERR_NO_FILE     0x2
#define IMG_ERR_MEM_FAIL    0x4
#define IMG_ERR_BAD_FORMAT  0x8
#define IMG_ERR_UNSUPPORTED 0x40

class TGALoader {
public:
    TGALoader();
    ~TGALoader();
    int loadImage(const char* szFilename, Image& img);
    int load(const char* szFilename);
    int GetBPP();
    int GetWidth();
    int GetHeight();
    unsigned char* GetImg(); // Return a pointer to image data
    unsigned char* GetPalette(); // Return a pointer to VGA palette
    void write(Image& img, const char* path);

private:
    short int iWidth, iHeight, iBPP;
    unsigned long lImageSize;
    char bEnc;
    unsigned char *pImage, *pPalette, *pData;

    // Internal workers
    int ReadHeader();
    int LoadRawData();
    int LoadTgaRLEData();
    int LoadTgaPalette();
    void BGRtoRGB();
    void FlipImg();
    void R_VerticalFlip(unsigned char* data, int width, int height);
};

#endif // TGALOADER_H
