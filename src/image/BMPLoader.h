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

#ifndef BMPLOADER_H
#define BMPLOADER_H
#include "Image.h"
#include <stdlib.h> 
#include <fstream>

class BMPLoader {
#pragma pack(push, 2)

    typedef struct {
        char id[2];
        unsigned int filesize;
        unsigned int nada0;
        unsigned int offBytes;
        unsigned int nada1;
        int ancho, alto;
        short uno;
        short bpp;
        unsigned int compresion;
        unsigned char randomcrap[20];
    } BMP_SIMPLIFICADO;
#pragma pack(pop)
public:
    BMPLoader();
    ~BMPLoader();
    int loadImage(const char* filename, Image& img);
};

#endif // BMPLOADER_H
