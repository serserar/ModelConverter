/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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


#ifndef PPMREADER_H
#define PPMREADER_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "Image.h"

using namespace std;

/**
 * Clase que se encarga de convertir (leer/escribir) un fichero PPM
 * a imagen y viceversa (imagen a fichero PPM)
 * 
 * El tipo de imagen con la que trabaja el conversor es PPM P6 (raw binario).
 * 
 */

class PPMReader {
public:

    PPMReader();

    bool readPPM(const std::string &filename, Image &raster); //lee un fichero PPM tipo P6 binarion a partir de una ruta.
    bool readPPM(std::istream &in, Image &raster); //lee cabecera de un fichero PXX.
    bool writePPM6(const std::string &filename, Image &raster); //escribe una imagen (Image) en formato PPM 6 en una ruta.
    bool writePGM5(const std::string &filename, Image &raster); //escribe una imagen (Image) en formato PPM 6 en una ruta.
    bool writePGM2(const std::string& filename, Image& raster);//
private:

    bool readP6Binary(std::istream &in, Image &raster); //lee un fichero PPM tipo P6 binario a partir de un stream.
    bool readP5Binary(std::istream &in, Image &raster); //lee un fichero PPM tipo P6 binario a partir de un stream.
    bool readPPMASCII(std::istream &in, Image &raster);

};

#endif // PPMREADER_H
