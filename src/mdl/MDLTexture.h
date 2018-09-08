/* 
 * File:   MDLTexture.h
 * Author: serserar
 *
 * Created on February 21, 2016, 12:14 AM
 */

#ifndef MDLTEXTURE_H
#define	MDLTEXTURE_H
#include "../image/Image.h"
#include <string>

using namespace std;

class MDLTexture {
public:
    MDLTexture();
    MDLTexture(const MDLTexture& orig);
    virtual ~MDLTexture();
    Image* GetImage();
    void SetTextureImage(Image* img);
    string GetTextureName();
    void SetTextureName(string textureName);
private:
    Image* img;
    string textureName;
};

#endif	/* MDLTEXTURE_H */

