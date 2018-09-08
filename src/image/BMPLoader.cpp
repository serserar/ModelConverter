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

#include "BMPLoader.h"

BMPLoader::BMPLoader() {

}

BMPLoader::~BMPLoader() {

}

int BMPLoader::loadImage(const char* filename, Image& img) {
    FILE *f;
    BMP_SIMPLIFICADO bmph;
    unsigned int i, tam, c;
    unsigned char *mem, paleta[256 * 4];
    int error = 0;

    if ((f = fopen(filename, "rb")) == NULL) {
        error = -1;
    }

    if (fread(&bmph, sizeof (BMP_SIMPLIFICADO), 1, f) != 1) {
        error = -2;
    }

    if (bmph.id[0] != 'B' || bmph.id[1] != 'M'
            || (bmph.bpp != 24 && bmph.bpp != 8) || bmph.compresion != 0) {
        error = -3;
    }

    if (bmph.bpp == 8) {
        fseek(f, sizeof (BMP_SIMPLIFICADO), SEEK_SET);
        fread(paleta, sizeof (unsigned char)*4, 256, f);
    }

    fseek(f, bmph.offBytes, SEEK_SET);
    mem = (unsigned char *) malloc(sizeof (unsigned char)*bmph.alto * bmph.ancho * 4);
    if (mem == NULL) {
        error = -4;
    }
    img.setImgFormat(Image::RGB);
    img.setImgType(Image::UNSIGNED_BYTE);
    img.setPixelData(mem);
    img.setWidth(bmph.ancho);
    img.setHeight(bmph.alto);
    tam = bmph.alto * bmph.ancho;
    for (i = 0; i < tam; i++) {
        mem[3] = 255;
        if (bmph.bpp == 8) {
            c = fgetc(f);
            mem[2] = paleta[c * 4];
            mem[1] = paleta[c * 4 + 1];
            mem[0] = paleta[c * 4 + 2];
        } else {
            mem[2] = fgetc(f);
            mem[1] = fgetc(f);
            mem[0] = fgetc(f);
        }
        mem += 4;
    }
    fclose(f);
    return error;
}
