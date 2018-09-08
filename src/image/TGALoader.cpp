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

#include "TGALoader.h"

TGALoader::TGALoader() {
    pImage = pPalette = pData = NULL;
    iWidth = iHeight = iBPP = bEnc = 0;
    lImageSize = 0;
}

TGALoader::~TGALoader() {
    if (pImage) {
        delete [] pImage;
        pImage = NULL;
    }

    if (pPalette) {
        delete [] pPalette;
        pPalette = NULL;
    }

    if (pData) {
        delete [] pData;
        pData = NULL;
    }
}

int TGALoader::loadImage(const char* szFilename, Image& img) {
    int resp = load(szFilename);
    if (resp == IMG_OK) {
        img.setPixelData(pImage);
        img.setWidth(iWidth);
        img.setHeight(iHeight);
        img.setImgType(Image::UNSIGNED_BYTE);
        switch (bEnc) {
            case 1:
                img.setImgFormat(Image::COLOR_INDEX);
                break;
            case 2:
                if (iBPP > 3) {
                    img.setImgFormat(Image::RGBA);
                } else {
                    img.setImgFormat(Image::RGB);
                }
                break;
            case 3:
                img.setImgFormat(Image::GRAYSCALE);
                break;
            case 9:
                img.setImgFormat(Image::COLOR_INDEX);
                break;
            case 10:
                img.setImgFormat(Image::RGB);
                break;
            default:
                img.setImgFormat(Image::RGB);
                break;
        }
    }
    return resp;
}

int TGALoader::load(const char* szFilename) {
    using namespace std;
    ifstream fin;
    unsigned long ulSize;
    int iRet;

    // Clear out any existing image and palette
    if (pImage) {
        delete [] pImage;
        pImage = NULL;
    }

    if (pPalette) {
        delete [] pPalette;
        pPalette = NULL;
    }

    // Open the specified file
    fin.open(szFilename, ios::binary);

    if (!fin) {
        return IMG_ERR_NO_FILE;
    }

    // Get file size
    fin.seekg(0, ios_base::end);
    ulSize = fin.tellg();
    fin.seekg(0, ios_base::beg);

    // Allocate some space
    // Check and clear pDat, just in case
    if (pData) {
        delete [] pData;
    }

    pData = new unsigned char[ulSize];

    if (pData == NULL) {
        fin.close();
        return IMG_ERR_MEM_FAIL;
    }

    // Read the file into memory
    fin.read((char*) pData, ulSize);

    fin.close();

    // Process the header
    iRet = ReadHeader();

    if (iRet != IMG_OK) {
        return iRet;
    }

    switch (bEnc) {
        case 1:
        { // Raw Indexed
            // Check filesize against header values
            if ((lImageSize + 18 + pData[0] + 768) > ulSize) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Double check image type field
            if (pData[1] != 1) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Load image data
            iRet = LoadRawData();
            if (iRet != IMG_OK) {
                return iRet;
            }

            // Load palette
            iRet = LoadTgaPalette();
            if (iRet != IMG_OK) {
                return iRet;
            }

            break;
        }

        case 2:
        { // Raw RGB
            // Check filesize against header values
            if ((lImageSize + 18 + pData[0]) > ulSize) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Double check image type field
            if (pData[1] != 0) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Load image data
            iRet = LoadRawData();
            if (iRet != IMG_OK) {
                return iRet;
            }

            BGRtoRGB(); // Convert to RGB
            break;
        }
        case 3: //raw grayscale
            // Check filesize against header values
            if ((lImageSize + 18 + pData[0]) > ulSize) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Double check image type field
            if (pData[1] != 0) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Load image data
            iRet = LoadRawData();
            if (iRet != IMG_OK) {
                return iRet;
            }

            break;
        case 9:
        { // RLE Indexed
            // Double check image type field
            if (pData[1] != 1) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Load image data
            iRet = LoadTgaRLEData();
            if (iRet != IMG_OK) {
                return iRet;
            }

            // Load palette
            iRet = LoadTgaPalette();
            if (iRet != IMG_OK) {
                return iRet;
            }

            break;
        }

        case 10:
        { // RLE RGB
            // Double check image type field
            if (pData[1] != 0) {
                return IMG_ERR_BAD_FORMAT;
            }

            // Load image data
            iRet = LoadTgaRLEData();
            if (iRet != IMG_OK) {
                return iRet;
            }

            BGRtoRGB(); // Convert to RGB
            break;
        }

        default:
            return IMG_ERR_UNSUPPORTED;
    }

    // Check flip bit
    if ((pData[17] & 0x10)) {
        FlipImg();
    }

    // Release file memory
    delete [] pData;
    pData = NULL;

    return IMG_OK;
}

int TGALoader::ReadHeader() // Examine the header and populate our class attributes
{
    short ColMapStart, ColMapLen;
    short x1, y1, x2, y2;

    if (pData == NULL) {
        return IMG_ERR_NO_FILE;
    }

    if (pData[1] > 1) { // 0 (RGB) and 1 (Indexed) are the only types we know about
        return IMG_ERR_UNSUPPORTED;
    }

    bEnc = pData[2]; // Encoding flag  1 = Raw indexed image
    //                2 = Raw RGB
    //                3 = Raw greyscale
    //                9 = RLE indexed
    //               10 = RLE RGB
    //               11 = RLE greyscale
    //               32 & 33 Other compression, indexed

    if (bEnc > 11) { // We don't want 32 or 33
        return IMG_ERR_UNSUPPORTED;
    }


    // Get palette info
    memcpy(&ColMapStart, &pData[3], 2);
    memcpy(&ColMapLen, &pData[5], 2);

    // Reject indexed images if not a VGA palette (256 entries with 24 bits per entry)
    if (pData[1] == 1) { // Indexed
        if (ColMapStart != 0 || ColMapLen != 256 || pData[7] != 24) {
            return IMG_ERR_UNSUPPORTED;
        }
    }

    // Get image window and produce width & height values
    memcpy(&x1, &pData[8], 2);
    memcpy(&y1, &pData[10], 2);
    memcpy(&x2, &pData[12], 2);
    memcpy(&y2, &pData[14], 2);

    iWidth = (x2 - x1);
    iHeight = (y2 - y1);

    if (iWidth < 1 || iHeight < 1) {
        return IMG_ERR_BAD_FORMAT;
    }

    // Bits per Pixel
    iBPP = pData[16];

    // Check flip / interleave byte
    if (pData[17] > 40) { // Interleaved data
        return IMG_ERR_UNSUPPORTED;
    }


    // Calculate image size
    lImageSize = (iWidth * iHeight * (iBPP / 8));

    return IMG_OK;
}

int TGALoader::LoadRawData() // Load uncompressed image data
{
    short iOffset;

    if (pImage) { // Clear old data if present
        delete [] pImage;
    }

    pImage = new unsigned char[lImageSize];

    if (pImage == NULL) {
        return IMG_ERR_MEM_FAIL;
    }

    iOffset = pData[0] + 18; // Add header to ident field size

    if (pData[1] == 1) { // Indexed images
        iOffset += 768; // Add palette offset
    }

    memcpy(pImage, &pData[iOffset], lImageSize);

    return IMG_OK;
}

int TGALoader::LoadTgaRLEData() // Load RLE compressed image data
{
    short iOffset, iPixelSize;
    unsigned char *pCur;
    unsigned long Index = 0;
    unsigned char bLength, bLoop;

    // Calculate offset to image data
    iOffset = pData[0] + 18;

    // Add palette offset for indexed images
    if (pData[1] == 1) {
        iOffset += 768;
    }

    // Get pixel size in bytes
    iPixelSize = iBPP / 8;

    // Set our pointer to the beginning of the image data
    pCur = &pData[iOffset];

    // Allocate space for the image data
    if (pImage != NULL) {
        delete [] pImage;
    }

    pImage = new unsigned char[lImageSize];

    if (pImage == NULL) {
        return IMG_ERR_MEM_FAIL;
    }

    // Decode
    while (Index < lImageSize) {
        if (*pCur & 0x80) { // Run length chunk (High bit = 1)
            bLength = *pCur - 127; // Get run length
            pCur++; // Move to pixel data

            // Repeat the next pixel bLength times
            for (bLoop = 0; bLoop != bLength; ++bLoop, Index += iPixelSize) {
                memcpy(&pImage[Index], pCur, iPixelSize);
            }

            pCur += iPixelSize; // Move to the next descriptor chunk
        } else { // Raw chunk
            bLength = *pCur + 1; // Get run length
            pCur++; // Move to pixel data

            // Write the next bLength pixels directly
            for (bLoop = 0; bLoop != bLength; ++bLoop, Index += iPixelSize, pCur += iPixelSize) {
                memcpy(&pImage[Index], pCur, iPixelSize);
            }
        }
    }

    return IMG_OK;
}

int TGALoader::LoadTgaPalette() // Load a 256 color palette
{
    unsigned char bTemp;
    short iIndex, iPalPtr;

    // Delete old palette if present
    if (pPalette) {
        delete [] pPalette;
        pPalette = NULL;
    }

    // Create space for new palette
    pPalette = new unsigned char[768];

    if (pPalette == NULL) {
        return IMG_ERR_MEM_FAIL;
    }

    // VGA palette is the 768 bytes following the header
    memcpy(pPalette, &pData[pData[0] + 18], 768);

    // Palette entries are BGR ordered so we have to convert to RGB
    for (iIndex = 0, iPalPtr = 0; iIndex != 256; ++iIndex, iPalPtr += 3) {
        bTemp = pPalette[iPalPtr]; // Get Blue value
        pPalette[iPalPtr] = pPalette[iPalPtr + 2]; // Copy Red to Blue
        pPalette[iPalPtr + 2] = bTemp; // Replace Blue at the end
    }

    return IMG_OK;
}

void TGALoader::BGRtoRGB() // Convert BGR to RGB (or back again)
{
    unsigned long Index, nPixels;
    unsigned char *bCur;
    unsigned char bTemp;
    short iPixelSize;

    // Set ptr to start of image
    bCur = pImage;

    // Calc number of pixels
    nPixels = iWidth*iHeight;

    // Get pixel size in bytes
    iPixelSize = iBPP / 8;

    for (Index = 0; Index != nPixels; Index++) { // For each pixel
        bTemp = *bCur; // Get Blue value
        *bCur = *(bCur + 2); // Swap red value into first position
        * (bCur + 2) = bTemp; // Write back blue to last position

        bCur += iPixelSize; // Jump to next pixel
    }

}

void TGALoader::FlipImg() // Flips the image vertically (Why store images upside down?)
{
    unsigned char bTemp;
    unsigned char *pLine1, *pLine2;
    int iLineLen, iIndex;

    iLineLen = iWidth * (iBPP / 8);
    pLine1 = pImage;
    pLine2 = &pImage[iLineLen * (iHeight - 1)];

    for (; pLine1 < pLine2; pLine2 -= (iLineLen * 2)) {
        for (iIndex = 0; iIndex != iLineLen; pLine1++, pLine2++, iIndex++) {
            bTemp = *pLine1;
            *pLine1 = *pLine2;
            *pLine2 = bTemp;
        }
    }

}

int TGALoader::GetBPP() {
    return iBPP;
}

int TGALoader::GetWidth() {
    return iWidth;
}

int TGALoader::GetHeight() {
    return iHeight;
}

unsigned char* TGALoader::GetImg() {
    return pImage;
}

unsigned char* TGALoader::GetPalette() {
    return pPalette;
}

void TGALoader::R_VerticalFlip(unsigned char* data, int width, int height) {
    int i, j;
    int temp;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height / 2; j++) {
            temp = *((int*) data + j * width + i);
            * ((int*) data + j * width + i) = *((int*) data + (height - 1 - j) * width + i);
            * ((int*) data + (height - 1 - j) * width + i) = temp;
        }
    }
}

void TGALoader::write(Image& img, const char* path) {
    if (path) {
        std::ofstream tgafile(path);
        int width = img.getWidth();
        int height = img.getHeight();
        //write header
        unsigned char header[ 18 ] = {0};
        header[ 2 ] = 2; // truecolor
        header[ 12 ] = width & 0xFF;
        header[ 13 ] = (width >> 8) & 0xFF;
        header[ 14 ] = height & 0xFF;
        header[ 15 ] = (height >> 8) & 0xFF;
        header[ 16 ] = 24; // bits per pixel
        header[ 17 ] = 1 << 5;// inverted origin
        tgafile.write((const char*) header, 18);
        //write data
        unsigned char* data = img.getPixelData();
        // The image data is stored bottom-to-top, left-to-right
        //         for ( int y = height -1; y >= 0; y-- )
        //             for ( int x = 0; x < width*3;x+=3) {
        //                 tgafile.put ( ( char ) data[ ( y * width ) + x ] );
        //                 tgafile.put ( ( char ) data[ ( y * width ) + x + 1] );
        //                 tgafile.put ( ( char ) data[ ( y * width ) + x + 2] );               
        //         }
        tgafile.write((char*) data, width * height * 3);
        // The file footer. This part is totally optional.
        static const char footer[ 26 ] =
                "\0\0\0\0" // no extension area
                "\0\0\0\0" // no developer directory
                "TRUEVISION-XFILE" // yep, this is a TGA file
                ".";
        tgafile.write(footer, 26);

        tgafile.close();
    }
}
