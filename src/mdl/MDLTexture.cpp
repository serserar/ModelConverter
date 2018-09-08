/* 
 * File:   MDLTexture.cpp
 * Author: serserar
 * 
 * Created on February 21, 2016, 12:14 AM
 */

#include "MDLTexture.h"

MDLTexture::MDLTexture() {
}

MDLTexture::MDLTexture(const MDLTexture& orig) {
}

MDLTexture::~MDLTexture() {
    if(img){
        delete img;
    }
}

Image* MDLTexture::GetImage() {
    return this->img;
}

void MDLTexture::SetTextureImage(Image* img) {
    this->img = img;
}

string MDLTexture::GetTextureName()
{
    return this->textureName;
}

void MDLTexture::SetTextureName(string textureName)
{
    this->textureName = textureName;
}
