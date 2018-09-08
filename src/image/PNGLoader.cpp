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

#include "PNGLoader.h"

PNGLoader::PNGLoader() {

}

PNGLoader::~PNGLoader() {

}

int PNGLoader::loadImage(const char* szFilename, Image& img) {
    png_byte header[8];

    FILE *fp = fopen(szFilename, "rb");

    if (fp == NULL)
        return IMG_ERR_NO_FILE;

    //read the header
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        return IMG_ERR_NO_FILE;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        return IMG_ERR_NO_FILE;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        fclose(fp);
        return IMG_ERR_NO_FILE;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return IMG_ERR_NO_FILE;
    }

    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return IMG_ERR_NO_FILE;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type, interlaced_type, compression_method;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
            &interlaced_type, &compression_method, NULL);

    img.setWidth(temp_width);
    img.setHeight(temp_height);


    //printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);

    if (bit_depth != 8) {
        fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", szFilename, bit_depth);
        return IMG_ERR_NO_FILE;
    }

    switch (bit_depth) {

        case 8:
            img.setImgType(Image::UNSIGNED_BYTE);
            break;
        default:
            img.setImgType(Image::UNSIGNED_BYTE);
            break;
    }

    switch (color_type) {
        case PNG_COLOR_TYPE_GRAY:
            img.setImgFormat(Image::GRAYSCALE);
            break;
        case PNG_COLOR_TYPE_RGB:
            img.setImgFormat(Image::RGB);
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            img.setImgFormat(Image::RGBA);
            break;
        default:
            fprintf(stderr, "%s: Unknown libpng color type %d.\n", szFilename, color_type);
            return IMG_ERR_NO_FILE;
    }

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes - 1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    img.setPixelData(new png_byte[rowbytes * temp_height * sizeof (png_byte) + 15]);
    if (img.getPixelData() == NULL) {
        fprintf(stderr, "error: could not allocate memory for PNG image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return IMG_ERR_NO_FILE;
    }

    // row_pointers is for pointing to image_data for reading the png with libpng
    png_byte ** row_pointers = new png_bytep[temp_height];
    if (row_pointers == NULL) {
        fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return IMG_ERR_NO_FILE;
    }

    // set the individual row_pointers to point at the correct offsets of image_data
    for (unsigned int i = 0; i < temp_height; i++) {
        row_pointers[temp_height - 1 - i] = img.getPixelData() + i * rowbytes;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);



    // clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] row_pointers;
    return IMG_OK;
}
