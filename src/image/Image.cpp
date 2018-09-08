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


#include "Image.h"

Image::Image() {
    this->offsetX = 0;
    this->offsetY = 0;
    this->writeWithOffset = false;
}

Image::Image(ImageDataFormat imgFormat, ImageDataType imgType, int width, int height) {
    this->imgformat = imgFormat;
    this->imgType = imgType;
    this->width = width;
    this->height = height;
    this->offsetX = 0;
    this->offsetY = 0;
    this->writeWithOffset = false;
    getComponents();
}

Image::Image(ImageDataFormat imgFormat, ImageDataType imgType, int width, int height, unsigned char* pixelData) {
    this->imgformat = imgFormat;
    this->imgType = imgType;
    this->width = width;
    this->height = height;
    this->pixelData = pixelData;
    this->offsetX = 0;
    this->offsetY = 0;
    this->writeWithOffset = false;
    getComponents();
}

Image::~Image() {
    delete[] pixelData;
}

Image::ImageDataFormat Image::getImgFormat() {
    return this->imgformat;
}

void Image::setImgFormat(Image::ImageDataFormat imgFormat) {
    this->imgformat = imgFormat;
}

Image::ImageDataType Image::getImgType() {
    return this->imgType;
}

void Image::setImgType(ImageDataType imgType) {
    this->imgType = imgType;
}

int Image::getWidth() {
    return this->width;
}

void Image::setWidth(int width) {
    this->width = width;
}

int Image::getHeight() {
    return this->height;
}

void Image::setHeight(int height) {
    this->height = height;
}

unsigned char* Image::getPixelData() {
    unsigned char* pdata = 0;
    if (writeWithOffset) {
        pdata = new unsigned char[width * height];
        for (int i = 0; i < width * height; i++) {
            pdata[i] = (unsigned char) getComponent(i);
        }
        return pdata;
    } else {
        return this->pixelData;
    }
}

void Image::setPixelData(unsigned char* pixelData) {
    this->pixelData = pixelData;
}

int Image::getRComponent(int pixel) {
    int rcomp = 0;
    if (pixel < width * height) {
        rcomp = (int) this->pixelData[components * pixel];
    }
    return rcomp;
}

int Image::getGComponent(int pixel) {
    int gcomp = 0;
    if (pixel < width * height) {
        gcomp = (int) this->pixelData[components * pixel + 1];
    }
    return gcomp;
}

int Image::getBComponent(int pixel) {
    int bcomp = 0;
    if (pixel < width * height) {
        bcomp = (int) this->pixelData[components * pixel + 2];
    }
    return bcomp;
}

int Image::getComponent(int pixel) {
    int pixelComponent = 0;
    if (components == 1) {
        if (offsetX == 0 && offsetY == 0) {
            pixelComponent = (int) this->pixelData[components * pixel];
        } else {
            pixelComponent = getComponent(pixel, offsetX, offsetY);
        }
    }
    return pixelComponent;
}

int Image::getComponent(int pixel, int offsetX, int offsetY) {
    int pixelComponent = 0;
    if (components == 1) {
        int x = pixel / width + offsetX;
        int y = pixel % height + offsetY;
        if (x < 0 || x > width || y < 0 || y > height) {
            pixelComponent = 0;
        } else {
            pixelComponent = (int) this->pixelData[components * x * height + y];
        }
    }
    return pixelComponent;
}

void Image::setComponent(int pixel, int value) {
    if (components == 1) {
        this->pixelData[components * pixel] = (char) value;
    }
}

void Image::SetComponent(int x, int y, int value)
{
    int index = x*width+y;
    this->pixelData[index] = (char) value;
}


void Image::setOffset(int offsetX, int offsetY) {
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

void Image::setWriteWithOffset(bool writeWithOffset) {
    this->writeWithOffset = writeWithOffset;
}

int Image::getComponents() {

    components = 0;

    if (imgformat == COLOR_INDEX) {
        components = 1;
    } else if (imgformat == RGB) {
        components = 3;
    } else if (imgformat == RGBA) {
        components = 4;
    } else if (imgformat == BGRA) {
        components = 4;
    } else if (imgformat == RED) {
        components = 1;
    } else if (imgformat == GREEN) {
        components = 1;
    } else if (imgformat == BLUE) {
        components = 1;
    } else if (imgformat == ALPHA) {
        components = 1;
    } else if (imgformat == LUMINANCE) {
        components = 1;
    } else if (imgformat == GRAYSCALE) {
        components = 1;
    } else if (imgformat == LUMINANCE_ALPHA) {
        components = 2;
    }
    return components;
}

/*!
 *Método que extrae la ventana de correlacion de la imagen img
 *
 */
unsigned char* Image::getSubRegionWindow(int x, int y, int wsize, bool centered)
{
  unsigned char* cWindow = NULL;
  bool createWindow = true;
  float lw = wsize;
  int left = x;
  int top = y;
  if(centered){
    lw /= 2;
    left -= lw;
    top -= lw;
  }
  int leftlimit = x + lw;
  int toplimit = y + lw;
  if(left < 0 || leftlimit > width || top < 0 || toplimit > height){
    createWindow = false;
  }
  if(createWindow){
    cWindow = new unsigned char[wsize*wsize];
    for(int i = 0; i < wsize;i++){
      for(int j = 0; j < wsize;j++){
	cWindow[i*wsize + j] = 0;
      }
    }
    for(int j = 0; j < wsize; j++){
      for(int i = 0; i < wsize; i++){
	cWindow[j*wsize +i] = pixelData[(top + j)*width + left + i];
      }
    } 
  }
  return cWindow;
}

/*!
 * 
 * Método que devuelve el tamaño de la ventana
 * de correlación.
 * @param WindowSize windowSize tipo de tamaño de la ventana
 * @return int el tamaño de la ventana de correlacion.
 */
int Image::getSubRegionWindowSize(WindowSize windowSize)
{
  int size = 0;
  switch(windowSize){
    case WS3x3:
	size = 3;
	break;
    case WS7x7:
	size = 7;
	break;
    case WS11x11:
	size = 11;
	break;
    case WS25x25:
	size = 25;
	break;
    default:
      size = 0;
      break;
  }
  return size;
}
