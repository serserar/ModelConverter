/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef IMAGE_H
#define IMAGE_H
#include <stddef.h>
class Image {
public:

    enum ImageDataFormat {
        COLOR_INDEX, GRAYSCALE, RGB, RGBA, BGRA, RED, GREEN, BLUE, ALPHA, LUMINANCE, LUMINANCE_ALPHA
    };

    enum ImageDataType {
        BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, INT, UNSIGNED_INT, FLOAT, BITMAT
    };
    
    enum WindowSize {WS3x3, WS7x7, WS11x11, WS25x25};//define los tamaños de ventana
    
    Image();
    Image(ImageDataFormat imgFormat, ImageDataType imgType, int width, int height);
    Image(ImageDataFormat imgFormat, ImageDataType imgType, int width, int height, unsigned char* pixelData);
    ~Image();
    int getComponents();
    void setImgFormat(ImageDataFormat imgFormat);
    ImageDataFormat getImgFormat();
    void setImgType(ImageDataType imgType);
    ImageDataType getImgType();
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    unsigned char* getPixelData();
    void setPixelData(unsigned char* pixelData);
    int getRComponent(int pixel);
    int getGComponent(int pixel);
    int getBComponent(int pixel);
    int getComponent(int pixel);
    int getComponent(int pixel, int offsetX, int offsetY);
    void setComponent(int pixel, int value);
    void SetComponent(int x,int y, int value);
    void setOffset(int offsetX, int offsetY);
    void setWriteWithOffset(bool writeWithOffset);
    unsigned char* getSubRegionWindow(int x, int y, int wsize, bool centered);
    int getSubRegionWindowSize(WindowSize windowSize);
private:

    unsigned char* pixelData;
    int width;
    int height;
    int offsetX;
    int offsetY;
    bool writeWithOffset;
    ImageDataFormat imgformat;
    int components;
    ImageDataType imgType;

};

#endif // IMAGE_H
