/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
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

#ifndef MDLREADER_H
#define MDLREADER_H


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <string.h>
#include "mdlspecs.h"
#include "MDLModel.h"
#include "MDLSubModel.h"
#include "MDLMesh.h"
#include "MDLAnimation.h"
#include "MDLFrame.h"
#include "../image/Image.h"
#include "../image/TGALoader.h"

#define HL1MDL_IDST 0x54534449  /**< @brief Spells "IDST" as ASCII text. */
#define HL1MDL_IDSQ 0x51534449  /**< @brief Spells "IDSQ" as ASCII text. */

#define HL1MDL_VER 10 /**< @brief MDL version used by Half Life 1. */

using namespace std;

class MDLReader {
public:

    MDLReader();
    MDLReader(const MDLReader& other);
    ~MDLReader();
    MDLModel* readModel(string modelPath);

private:

    void readHeader(char* path);
    void readBones(MDLSkeleton& skeleton);
    void readBoneControllers();
    void readHitBoxes();
    MDLAnimation* readSequences();
    void readSequenceData(int frames, int nbones, int animindex, MDLAnimation& animation);
    void recoverBonePositionValues(int frames, int index, float bonescale, float bonecontroller, float defaulbonevalue, float* positions);
    void recoverBoneRotationValues(int frames, int index, float bonescale, float defaulbonevalue, float* rotations);
    void readAnimValues(int avaluesindex, int frames, std::vector<animvalue_s *>& valuesList);
    animvalue_s* readAnimValue();
    void getAnimValue(int frame,std::vector<animvalue_s *>& valuesList, int& value, int& nextvalue);
    void readSeqGroup();
    void readTextures();
    void readTexture(int offset, int width,
            int height, Image* img);
    void convertToRGBA(unsigned char* rawData, unsigned char* palette, unsigned char* pixelData, int size);
    void convertToRGB(unsigned char* rawData, unsigned char* palette, unsigned char* pixelData, int size);
    void readSkins();
    MDLBodyParts* readBodyParts();
    MDLSubModel* readModels(int index, int nummodels);
    int* readBoneVertsInfo(int numverts, int index);
    vec3_s* readVerts(int numverts, int index);
    int* readBoneNormalsInfo(int numnormals, int index);
    vec3_s* readNormals(int numNormals, int index);
    MDLMesh* readMeshes(int index, int numMeshes, vec3_s* modelVertex,
            int* vertexBoneInfo, vec3_s* modelNormals, int* normalsBoneInfo);
    bool isPowerOfTwo(int dimension);
    MDLTexture* BuildTextureImage(int skinRef, string textureName);
    ifstream modelFile;
    mdl_header header;
    bone_s* bones;
    bonecontroller_s* bonecontrollers;
    hbbox_s* hbboxs;
    sequence_s* sequences;
    sequencegroup_s* sequence_groups;
    texture_s* textures;
    Image* textureImages;
    short* skins;
    int nskins;
    bodypart_s* bodypartstr;
};

#endif // MDLREADER_H
