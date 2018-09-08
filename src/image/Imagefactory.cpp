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

#include "Imagefactory.h"
#include "PPMReader.h"

ImageFactory::ImageFactory() {

}

ImageFactory::~ImageFactory() {

}

Image* ImageFactory::loadImage(const std::string& path) {
    Image* img = NULL;
    std::string extension(path.c_str());
    std::transform(path.begin(), path.end(), extension.begin(), ::tolower);
    if (path.substr(path.find_last_of(".")) == ".tga") {
        img = new Image();
        TGALoader* tgaLoader = new TGALoader();
        int res = tgaLoader->loadImage(path.c_str(), *img);
        if (tgaLoader){
            delete tgaLoader;
        }
    } else if (path.substr(path.find_last_of(".")) == ".png") {
        img = new Image();
        PNGLoader* pngLoader = new PNGLoader();
        int res = pngLoader->loadImage(path.c_str(), *img);
        if (res == 0)
            delete pngLoader;
    }else if (path.substr(path.find_last_of(".")) == ".bmp") {
        img = new Image();
        BMPLoader* bmpLoader = new BMPLoader();
        int res = bmpLoader->loadImage(path.c_str(), *img);
        if (res == 0)
            delete bmpLoader;
    }else if (path.substr(path.find_last_of(".")) == ".pgm") {
        img = new Image();
        PPMReader* ppmLoader = new PPMReader();
        int res = ppmLoader->readPPM(path, *img);
        if (ppmLoader)
            delete ppmLoader;
    }
    return img;
}

Image* ImageFactory::loadImage(const string& path, bool equalize)
{
  Image* loaded = loadImage(path);
  Image* equalized = NULL;
  if(loaded){
    equalized = ImageFactory::equalize(*loaded);
    delete loaded;
  }
  return equalized;
}


Image* ImageFactory::resize(Image& img, ImageFactory::image_resize_alg, float ratio)
{
  Image* img_res = NULL;
  //calculamos el destino
  unsigned char* buffer;
  int width = img.getWidth()/ratio;
  int height = img.getHeight()/ratio;
  int size = width*height *img.getComponents();
  buffer = new unsigned char[size];
  int index = 0;
  int index_ratio=0;
  double x_ratio = ratio;
  double y_ratio = ratio;
  double px, py ; 
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      index = i*width + j;
      px = floor(j*x_ratio) ;
      py = floor(i*y_ratio) ;
      index_ratio = i*ratio*img.getWidth() + j*ratio;
      buffer[index] = img.getComponent((int)((py*img.getWidth())+px));
    } 
  }
  img_res = new Image(img.getImgFormat(),
		      img.getImgType(),
		      width,
		      height,
		      buffer);
  return img_res;
}

Image* ImageFactory::equalize(Image& img)
{
  Image* img_res = NULL;
  //Calculamos histograma en escala de grises
  int histogram[256];
  int sumHistogram[256];
  for(int i = 0; i < 256; i++){
    histogram[i]=0;
    sumHistogram[i]=0;
  }
  int pixels = img.getWidth()*img.getHeight();
  for (int i = 0; i < pixels; ++i )
  {
    int gray = (int)img.getPixelData()[i];
    histogram[gray]++;
  }
  int sum = 0;
  for(int i = 0; i < 256; i++){
    sum += histogram[i];
    sumHistogram[i] = sum;
  }
  unsigned char* buffer = new unsigned char[pixels];
  float ratio = 255.0f/(float)pixels;
  for (int i = 0; i < pixels; ++i )
  {
    int gray = (int)img.getPixelData()[i];
    buffer[i] = ratio * (float)sumHistogram[gray];
  }
  img_res = new Image(img.getImgFormat(),
		      img.getImgType(),
		      img.getWidth(),
		      img.getHeight(),
		      buffer);
  return img_res;
}
