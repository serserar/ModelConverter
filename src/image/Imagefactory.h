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

#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include <string>
#include <algorithm>
#include <math.h>
#include "Image.h"
#include "TGALoader.h"
#include "PNGLoader.h"
#include "BMPLoader.h"

class ImageFactory {
public:
    enum image_resize_alg {nearest_neighbor};
    ImageFactory();
    ~ImageFactory();
    static Image* loadImage(const std::string& path);
    static Image* loadImage(const std::string& path, bool equalize);
    static Image* resize(Image& img, image_resize_alg, float factor);
    static Image* equalize(Image& img);
};

#endif // IMAGEFACTORY_H
