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


#include "PPMReader.h"
#include <limits>

PPMReader::PPMReader() {
}

/**
 * Método que lee un fichero PPM a partir de una ruta y
 * deja el resultado en un objeto de tipo Image.
 * 
 * @param filename string con la ruta del fichero PPM.
 * @param raster referencia donde se deja el resultado de leer la imagen PPM.
 * 
 */

bool PPMReader::readPPM(const std::string &filename, Image &raster) {
    bool res = false;
    std::ifstream in(filename.c_str(), std::ios::binary);
    if (in) {
        res = readPPM(in, raster);
	in.close();
    }
}

/**
 * Método que lee un fichero PPM tipo P6 binario a partir de un stream.
 * 
 * @param in stream del fichero PPM.
 * @param raster referencia donde se almacenará la imagen leída.
 * 
 */

bool PPMReader::readPPM(std::istream &in, Image &raster) {
    char comment; // 
    std::string magic;
    long width = 0;
    long height = 0;
    long pixel_max = 0;

    // leemos cabecera
    in >> magic >> width >> height >> pixel_max;
    // comprobamos cabecera.
    if (in &&
            (magic == "P6" || magic == "P3" || magic == "P5" || magic == "P2") &&
            width > 0 && height > 0 &&
            pixel_max > 0 && pixel_max < 256) {
        // si es válida la cabecera.
        if (magic == "P6") {
            raster.setImgFormat(Image::RGB);
            raster.getComponents();
            raster.setWidth(width);
            raster.setHeight(height);
            raster.setPixelData(new unsigned char[width * height * 3]);
            return readP6Binary(in, raster); // leemos el stream y dejamos la imagen en raster.
        } else if (magic == "P5") {
            raster.setImgFormat(Image::GRAYSCALE);
            raster.getComponents();
            raster.setWidth(width);
            raster.setHeight(height);
            raster.setPixelData(new unsigned char[width * height]);
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return readP5Binary(in, raster); // leemos el stream y dejamos la imagen en raster.
        } else if(magic == "P2") {
	    raster.setImgFormat(Image::GRAYSCALE);
            raster.getComponents();
            raster.setWidth(width);
            raster.setHeight(height);
            raster.setPixelData(new unsigned char[width * height]);
            return readPPMASCII(in, raster); // lee formato ascii (no implementado)
        }
    }

    return false;
}

/**
 * 
 * Método que lee los datos binarios (pixeles) width * height * 3 (rgb)
 * 
 */

bool PPMReader::readP6Binary(istream& in, Image& raster) {
    in.read((char*) raster.getPixelData(), raster.getWidth() * raster.getHeight() * 3);
}

bool PPMReader::readP5Binary(istream& in, Image& raster) {
    in.read((char*) raster.getPixelData(), raster.getWidth() * raster.getHeight());
}

/**
 * Método que lee un fichero PPM ASCII (no implementado)
 * 
 */
bool PPMReader::readPPMASCII(std::istream &in, Image &raster) {
  int row = 0, col = 0, numrows = raster.getHeight(), numcols = raster.getWidth();
  stringstream ss;

  // Continue with a stringstream
  ss << in.rdbuf();

  // Following lines : data
  int value = 0;
  for(row = 0; row < numrows; ++row){
    for (col = 0; col < numcols; ++col) {
      ss >> value ;
      raster.getPixelData()[row*numcols + col]= value;
    }
  }
}

/**
 * Método que escribe un fichero PPM a fichero.(testeo)
 * 
 * @param filename string con la ruta destino del fichero.
 * @param raster referencia imagen donde se almacena la imagen RGB parseada. 
 * 
 * 
 */

bool PPMReader::writePPM6(const std::string& filename, Image& raster) {
    bool res = false;
    std::ofstream out(filename.c_str(), std::ios::binary);
    if (out) {
        out << "P6" << endl << raster.getWidth() << " " << raster.getHeight() << endl << 255;
        out.write((char*) raster.getPixelData(), raster.getWidth() * raster.getHeight() * 3);
        out.close();
        res = true;
    }
    return res;
}

/**
 * Método que escribe un fichero PPM a fichero.(testeo)
 * 
 * @param filename string con la ruta destino del fichero.
 * @param raster referencia imagen donde se almacena la imagen RGB parseada. 
 * 
 * 
 */

bool PPMReader::writePGM5(const std::string& filename, Image& raster) {
    bool res = false;
    std::ofstream out(filename.c_str(), std::ios::binary);
    if (out) {
        out << "P5" << endl << raster.getWidth() << " " << raster.getHeight() << endl << 255 << endl;
        out.write((char*) raster.getPixelData(), raster.getWidth() * raster.getHeight());
        out.close();
        res = true;
    }
    return res;
}

/**
 * Método que escribe un fichero PPM a fichero.(testeo)
 * 
 * @param filename string con la ruta destino del fichero.
 * @param raster referencia imagen donde se almacena la imagen RGB parseada. 
 * 
 * 
 */

bool PPMReader::writePGM2(const std::string& filename, Image& raster) {
    bool res = false;
    std::ofstream out(filename.c_str(), std::ios::binary);
    if (out) {
        out << "P2" << endl << raster.getWidth() << " " << raster.getHeight() << endl << 255 << endl;
        out.write((char*) raster.getPixelData(), raster.getWidth() * raster.getHeight());
        out.close();
        res = true;
    }
    return res;
}