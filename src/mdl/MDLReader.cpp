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

#include "MDLReader.h"

MDLReader::MDLReader() {

}

MDLReader::MDLReader(const MDLReader& other) {

}

MDLReader::~MDLReader() {

}

MDLModel* MDLReader::readModel(string modelPath) {
    MDLModel* model = nullptr;
    modelFile.open(modelPath.c_str(), ios::binary);
    if (modelFile.is_open()) {
        readHeader((char*)modelPath.c_str()); //read mdl header
        model = new MDLModel();
        model->SetName(header.name);
        model->SetSkeleton(new MDLSkeleton());
        readBones(*model->GetSkeleton());
        readBoneControllers();
        readHitBoxes();
        model->FillAnimation(readSequences(),header.numseq);
        readSeqGroup();
        readTextures();
        readSkins();
        model->FillBodyParts(readBodyParts(), header.numbodyparts);
    }
    return model;
}

void MDLReader::readHeader(char* path) {
    modelFile.read((char*) &header, sizeof ( header));
    std::cout << header.name << std::endl;
}

void MDLReader::readBones(MDLSkeleton& skeleton) {
    modelFile.seekg(header.boneindex);
    bones = new bone_s[header.numbones];
    MDLJoint* joint;
    for (unsigned int i = 0; i < header.numbones; i++) {
        modelFile.read((char*) &bones[i], sizeof ( bones[i]));
        std::cout << bones[i].name << std::endl;
        joint = new MDLJoint();
        joint->SetName(bones[i].name);
        joint->SetParent(bones[i].parent);
        joint->SetId(i);
        joint->SetTranslation(bones[i].value[0],bones[i].value[1],bones[i].value[2]);
        joint->SetRotation(bones[i].value[3],bones[i].value[4],bones[i].value[5]);
        skeleton.AddMDLJoint(joint);
    }
}

void MDLReader::readBoneControllers() {
    if (header.numbonecontrollers > 0) {
        modelFile.seekg(header.bonecontrollerindex);
        bonecontrollers = new bonecontroller_s[header.numbonecontrollers];
        for (unsigned int i = 0; i < header.numbonecontrollers; i++) {
            modelFile.read((char*) &bonecontrollers[i], sizeof ( bonecontrollers[i]));
            std::cout << bonecontrollers[i].bone << std::endl;
        }
    }
}

void MDLReader::readHitBoxes() {
    if (header.numhitboxes > 0) {
        modelFile.seekg(header.hitboxindex);
        hbboxs = new hbbox_s[header.numhitboxes];
        for (unsigned int i = 0; i < header.numhitboxes; i++) {
            modelFile.read((char*) &hbboxs[i], sizeof ( hbboxs[i]));
            std::cout << hbboxs[i].bone << std::endl;
        }
    }
}

MDLAnimation* MDLReader::readSequences() {
    MDLAnimation* animation = nullptr;
    if (header.numseq > 0) {
        modelFile.seekg(header.seqindex);
        sequences = new sequence_s[header.numseq];
        long filepointer = header.seqindex;
        animation = new MDLAnimation[header.numseq];
        string animname;
        for (unsigned int i = 0; i < header.numseq; i++) {
            modelFile.read((char*) &sequences[i], sizeof ( sequences[i]));
            string animname(sequences[i].label);
            animation[i].SetName(animname);
            std::cout << animation[i].GetName() << std::endl;
            filepointer = modelFile.tellg();
            readSequenceData(sequences[i].numframes,
                    header.numbones, sequences[i].animindex, animation[i]);
            animation[i].Setfps(sequences[i].fps); 
            //_animations.add(mSeqDesc);
            modelFile.seekg(filepointer);
        }
    }
    return animation;
}

void MDLReader::readSequenceData(int frames, int nbones, int animindex, MDLAnimation& animation) {
    MDLSkeleton* skeletonFrames = new MDLSkeleton[frames];
    for(int f = 0; f < frames; f++){
        skeletonFrames[f].FillJoints( new MDLJoint[nbones], nbones);
    }
    float* positionsx = new float[frames];
    float* positionsy = new float[frames];
    float* positionsz = new float[frames];
    float* rotationsx = new float[frames];
    float* rotationsy = new float[frames];
    float* rotationsz = new float[frames];
    //for each joint recover all dof (position + rotation) for all animation frames
    for (int i = 0; i < nbones; i++) {
            //read dof pointer for position x
            modelFile.seekg(animindex);
            unsigned short dof;
            modelFile.read(reinterpret_cast<char *>(&dof), sizeof(dof));
            //store pointer for next dof
            long dofFilepointerIndex = modelFile.tellg(); 
            //recover position x
            recoverBonePositionValues(frames, dof == 0 ? 0 : animindex +dof,
                        bones[i].scale[0],
                        bones[i].bonecontroller[0]==-1?0:bones[i].bonecontroller[0],
                        bones[i].value[0], positionsx);
            //read dof pointer for position y
            modelFile.seekg(dofFilepointerIndex);
            modelFile.read(reinterpret_cast<char *>(&dof), sizeof(dof));
            //store pointer for next dof
            dofFilepointerIndex = modelFile.tellg();
            recoverBonePositionValues(frames, dof == 0 ? 0 : animindex +dof,
                        bones[i].scale[1],
                        bones[i].bonecontroller[1]==-1?0:bones[i].bonecontroller[1],
                        bones[i].value[1], positionsy);
            //recover position z
            modelFile.seekg(dofFilepointerIndex);
            modelFile.read(reinterpret_cast<char *>(&dof), sizeof(dof));
            //store pointer for next dof
            dofFilepointerIndex = modelFile.tellg();
            recoverBonePositionValues(frames, dof == 0 ? 0 : animindex +dof,
                        bones[i].scale[2],
                        bones[i].bonecontroller[2]==-1?0:bones[i].bonecontroller[2],
                        bones[i].value[2], positionsz);
            //recover rotation x
            modelFile.seekg(dofFilepointerIndex);
            modelFile.read(reinterpret_cast<char *>(&dof), sizeof(dof));
            //store pointer for next dof
            dofFilepointerIndex = modelFile.tellg();
            recoverBoneRotationValues(frames, dof == 0 ? 0 : animindex +dof,
                        bones[i].scale[3],
                        bones[i].value[3],
                        rotationsx);
            //recover rotation y
            modelFile.seekg(dofFilepointerIndex);
            modelFile.read(reinterpret_cast<char *>(&dof), sizeof(dof));
            //store pointer for next dof
            dofFilepointerIndex = modelFile.tellg();
            recoverBoneRotationValues(frames, dof == 0 ? 0 : animindex +dof,
                        bones[i].scale[4],
                        bones[i].value[4],
                        rotationsy);
            //recover rotation z
            modelFile.seekg(dofFilepointerIndex);
            modelFile.read(reinterpret_cast<char *>(&dof), sizeof(dof));
            dofFilepointerIndex = modelFile.tellg();
            recoverBoneRotationValues(frames, dof == 0 ? 0 : animindex +dof,
                        bones[i].scale[5],
                        bones[i].value[5],
                        rotationsz);
            //store pointer for next dof for next joint
            animindex = dofFilepointerIndex;
            //store all frames positions, rotations for joint i
            for(int f = 0; f < frames; f++){
                skeletonFrames[f].GetMDLJoint(i)->SetName(bones[i].name);
                skeletonFrames[f].GetMDLJoint(i)->SetId(i);
                skeletonFrames[f].GetMDLJoint(i)->SetParent(bones[i].parent);
                skeletonFrames[f].GetMDLJoint(i)->SetTranslation(positionsx[f],positionsy[f],positionsz[f]);
                skeletonFrames[f].GetMDLJoint(i)->SetRotation(rotationsx[f], rotationsy[f], rotationsz[f]);
                //clean frame position and rotations
                positionsy[f]=0.0f;
                positionsx[f]=0.0f;
                positionsz[f]=0.0f;
                rotationsx[f]=0.0f;
                rotationsy[f]=0.0f;
                rotationsz[f]=0.0f;
            }
    }
    animation.FillSkeletons(skeletonFrames, frames);
    delete[] positionsx;
    delete[] positionsy;
    delete[] positionsz;
    delete[] rotationsx;
    delete[] rotationsy;
    delete[] rotationsz;
}
//recupera los datos de un grado de libertad de un hueso para todos los frames de una animacion
void MDLReader::recoverBonePositionValues(int frames, int index, float bonescale, float bonecontroller, float defaulbonevalue, float* positions) {
    float weight = 1.0f;
    if (index == 0) {
        for (int i = 0; i < frames; i++) {
            positions[i] = defaulbonevalue;
        }
    } else {
        std::vector<animvalue_s *> valuesList;
        readAnimValues(index, frames, valuesList);
        int value, nextvalue;
        for (int i = 0; i < frames; i++) {
            positions[i] = defaulbonevalue;
            value = -1;
            nextvalue = -1;
            getAnimValue(i, valuesList, value, nextvalue);
            if (nextvalue == -1) {
                // El valor del fotograma actual y del siguiente son el
                // mismo. No hay que interpolar.
                positions[i] += (float)value * bonescale;
            } else {
                // Ambos valores son diferentes. Tenemos que interpolar.
                positions[i] += ((float)value * (1.0 - 0) + (nextvalue * 0)) * bonescale;
                positions[i] += (float)bonecontroller;
                if (weight != 1.0f) {
                    // Hay que hacer algunas cuentas.
                    float w1;
                    w1 = 1.0f - weight;
                    //sino no hay mezcla. Nos ahorramos los calculos de la interpolación.
                    positions[i] = w1 * positions[i] + weight * positions[i];
                }
            }
        }
    }
}

void MDLReader::recoverBoneRotationValues(int frames, int index, float bonescale, float defaulbonevalue, float* rotations) {
    if (index == 0) {
        for (int i = 0; i < frames; i++) {
            rotations[i] = defaulbonevalue;
        }
    } else {
        std::vector<animvalue_s *> valuesList;
        readAnimValues(index, frames, valuesList);
        int value, nextvalue;
        for (int i = 0; i < frames; i++) {
            rotations[i] = defaulbonevalue;
            value = -1;
            nextvalue = -1;
            getAnimValue(i, valuesList, value, nextvalue);
            if (nextvalue == -1 || value == nextvalue) {
                // El valor del fotograma actual y del siguiente son el
                // mismo. No hay que interpolar.
                rotations[i] += (float)value * bonescale;
            } else {
                // Ambos valores son diferentes. Tenemos que interpolar.
                rotations[i] += ((float)value * (1.0 - 0) + (nextvalue * 0)) * bonescale;
            }
        }
    }
}

void MDLReader::readAnimValues(int avaluesindex, int frames, std::vector<animvalue_s *>& valuesList)
{
 long filepointer = modelFile.tellg();    
 modelFile.seekg(avaluesindex);
 animvalue_s * value = readAnimValue();
 valuesList.push_back(value);
 int cont = value->num.valid + 1;
 while (value->num.total < frames) {
     // Todavia no hemos llegado. Avanzamos
    frames -= value->num.total;
    for (int j = 0; j < cont; j++) {//recogemos las validas
        value = readAnimValue();
        valuesList.push_back(value);
    }
    cont += value->num.valid + 1;
    if (value->num.total == 0) {
      break;
    }
}
//rest of frames
for (int j = 0; j < frames; j++) {
    value = readAnimValue();
    valuesList.push_back(value);
}
modelFile.seekg(filepointer);
}

animvalue_s * MDLReader::readAnimValue()
{
    animvalue_s * aninvalue = new animvalue_s;
    modelFile.read(reinterpret_cast<char *>(&aninvalue->num.valid), sizeof(aninvalue->num.valid));
    modelFile.read(reinterpret_cast<char *>(&aninvalue->num.total), sizeof(aninvalue->num.total));
    //modelFile.read(reinterpret_cast<char *>(&aninvalue->value), sizeof(aninvalue->value));
    return aninvalue;
}

void MDLReader::getAnimValue(int frame, std::vector<animvalue_s *>& valuesList, int& value, int& nextvalue)
{
        int count;
        count = frame;
        // Desplazamos span hasta que apunte a la cabecera del bloque
        // donde estó el fotograma buscado.
        int i = 0;
        while (valuesList[i]->num.total <= count) {
            count -= valuesList[i]->num.total;
            i += valuesList[i]->num.valid + 1;
            if (i >= valuesList.size()) {
                break;
            }
        }
        // Tenemos span apuntando a la cabecera del lapso donde esta
        // la información del fotograma, y en count el nómero de fotograma
        // relativo al lapso de span.
        // Hay que devolver el valor para count y para count+1. Tenemos
        // cuatro casos:
        if (valuesList[i]->num.valid > count) {
            if (i + count + 1 >= valuesList.size()) {//no hay mós componentes, hay que devolver 0
                value = 0;
            }else{
                // La información del fotograma solicitado estó en la zona
                // inicial, es decir no estó "comprimido".
                value = valuesList[i + count + 1]->value;
                if (valuesList[i]->num.valid > count + 1) {
                    if (i + count + 2 >= valuesList.size()) {//no hay mós componentes, hay que devolver 0
                        value = 0;
                    }else{
                        // El fotograma siguiente tampoco estó en la parte
                        // "comprimida".
                        nextvalue = valuesList[i + count + 2]->value;
                    }
                } else {
                    // El fotograma siguiente se encuentra en la parte comprimida.
                    nextvalue = valuesList[i + count + 1]->value;
                }
            }
        } else {
            if (i + valuesList[i]->num.valid >= valuesList.size()) {//no hay mós componentes, hay que devolver 0
                    value = 0;
            }else{
                    // El fotograma solicitado estó en la parte "comprimida".
                    value = valuesList[i + valuesList[i]->num.valid]->value;
                    if (valuesList[i]->num.total <= count + 1) {
                        // El fotograma siguiente estó en el lapso siguiente, no en
                        // el actual.
                        if (valuesList[i]->num.valid + 2 >= valuesList.size()
                            || i + valuesList[i]->num.valid + 2 >= valuesList.size()) {
                            //no hay mós componentes, hay que devolver 0
                            nextvalue = 0;
                        }else{
                            nextvalue = valuesList[i + valuesList[i]->num.valid + 2]->value;
                        }
                } else {
                    if (valuesList[i]->num.valid + i >= valuesList.size()) {//no hay mós componentes, hay que devolver 0
                        nextvalue = 0;
                    }else{
                        nextvalue = valuesList[i + valuesList[i]->num.valid]->value;
                    }
                }

            }
    }
}
    
void MDLReader::readSeqGroup() {
    if (header.numseqgroups > 0) {
        modelFile.seekg(header.seqgroupindex);
        sequence_groups = new sequencegroup_s[header.numseqgroups];
        for (unsigned int i = 0; i < header.numseqgroups; i++) {
            modelFile.read((char*) &sequence_groups[i], sizeof ( sequence_groups[i]));
            std::cout << sequence_groups[i].label << std::endl;
        }
    }
}

void MDLReader::readTextures() {
    if (header.numtextures > 0) {
        modelFile.seekg(header.textureindex);
        textures = new texture_s[header.numtextures];
        textureImages = new Image[header.numtextures];
        for (unsigned int i = 0; i < header.numtextures; i++) {
            modelFile.read((char*) &textures[i], sizeof ( textures[i]));
            std::cout << textures[i].name << std::endl;
            //save pointer
            int offset = modelFile.tellg();
            //recover texture data
            readTexture(textures[i].index,
                    textures[i].width,
                    textures[i].height,
                    &textureImages[i]);
            TGALoader reader;
            size_t lastindex = string(textures[i].name).find_last_of("."); 
            string rawname = string(textures[i].name).substr(0, lastindex);
            std::copy(rawname.begin(), rawname.end(), textures[i].name);
            for(int c = rawname.size(); c < 64; c++){
                textures[i].name[c]= '\0';
            }
            reader.write(textureImages[i], string(rawname + ".tga").c_str());
            //set offset for next texture
            modelFile.seekg(offset);
        }
    }
}

void MDLReader::readTexture(int offset, int width, int height, Image * img) {
    modelFile.seekg(offset);
    if (isPowerOfTwo(width) && isPowerOfTwo(height)) {
        img->setWidth(width);
        img->setHeight(height);
        int size = width * height;
        unsigned char* rawData = new unsigned char[size]; //raw data
        modelFile.read((char*) rawData, size);
        unsigned char* palette = new unsigned char[768];
        modelFile.read((char*) palette, 768);
        unsigned char* pixelData = new unsigned char[size * 3];
        convertToRGB(rawData, palette, pixelData, size);
        img->setPixelData(pixelData);
    } else {
        img->setWidth(width);
        img->setHeight(height);
        int size = width * height;
        unsigned char* rawData = new unsigned char[size]; //raw data
        modelFile.read((char*) rawData, size);
        unsigned char* palette = new unsigned char[768];
        modelFile.read((char*) palette, 768);
        unsigned char* pixelData = new unsigned char[size * 3];
        convertToRGB(rawData, palette, pixelData, size);
        img->setPixelData(pixelData);
    }
}

void MDLReader::convertToRGBA(unsigned char* rawData, unsigned char* palette, unsigned char* pixelData, int size) {
    for (int i = 0; i < size; i++) {
        pixelData[i * 4 + 0] = palette[rawData[i] * 3];
        pixelData[i * 4 + 1] = palette[rawData[i] * 3 + 1];
        pixelData[i * 4 + 2] = palette[rawData[i] * 3 + 2];
        pixelData[i * 4 + 3] = 255;
    }
}

void MDLReader::convertToRGB(unsigned char* rawData,
        unsigned char* palette,
        unsigned char* pixelData, int size) {
    int index;
    for (int i = 0; i < size; i++) {
        index = i * 3;
        pixelData[index] = palette[rawData[i] * 3 + 2];
        pixelData[index + 1] = palette[rawData[i] * 3 + 1];
        pixelData[index + 2] = palette[rawData[i] * 3];
    }
}

void MDLReader::readSkins() {
    nskins = header.numskinfamilies * header.numskinref;
    if (nskins > 0) {
        modelFile.seekg(header.skinindex);
        skins = new short[nskins];
        for (int i = 0; i < nskins; i++) {
            modelFile.read((char*) &skins[i], sizeof ( skins[i]));
            //std::cout << skins[i] << std::endl;
        }
    }
}

MDLBodyParts * MDLReader::readBodyParts() {
    MDLBodyParts* bodyparts = nullptr;
    if (header.numbodyparts > 0) {
        modelFile.seekg(header.bodypartindex);
        bodypartstr = new bodypart_s[header.numbodyparts];
        bodyparts = new MDLBodyParts[header.numbodyparts];
        for (int i = 0; i < header.numbodyparts; i++) {
            modelFile.read((char*) &bodypartstr[i], sizeof ( bodypartstr[i]));
            int offset = modelFile.tellg();
            std::cout << bodypartstr[i].name << std::endl;
            bodyparts[i].Fill(readModels(bodypartstr[i].modelindex, bodypartstr[i].nummodels),
                    bodypartstr[i].nummodels);
            modelFile.seekg(offset);
        }
    }
    return bodyparts;
}

MDLSubModel * MDLReader::readModels(int index, int nummodels) {
    MDLSubModel* model = nullptr;
    if (nummodels > 0) {
        model_s* models_str = new model_s[nummodels];
        model = new MDLSubModel[nummodels];
        modelFile.seekg(index);
        for (int i = 0; i < nummodels; i++) {
            modelFile.read((char*) &models_str[i], sizeof ( models_str[i]));
            std::cout << models_str[i].name << std::endl;
            model[i].SetName(models_str[i].name);
            model[i].SetBoundingRadius(models_str[i].boundingradius);
            int offset = modelFile.tellg();
            int* boneVertsInfo = readBoneVertsInfo(models_str[i].numverts, models_str[i].vertinfoindex);
            vec3_s* verts = readVerts(models_str[i].numverts, models_str[i].vertindex);
            int* boneNormalsInfo = readBoneNormalsInfo(models_str[i].numnorms, models_str[i].norminfoindex); //read bones normals
            vec3_s* normals = readNormals(models_str[i].numnorms, models_str[i].normindex);
            modelFile.seekg(offset);
            model[i].Fill(readMeshes(models_str[i].meshindex, models_str[i].nummesh,
                    verts, boneVertsInfo, normals, boneNormalsInfo), models_str[i].nummesh);
            modelFile.seekg(offset);
        }
        delete[] models_str;
    }
    return model;
}

int* MDLReader::readBoneVertsInfo(int numverts, int index) {
    int* boneVertsInfo = nullptr;
    unsigned char* bonesId = nullptr;
    if (numverts > 0) {
        modelFile.seekg(index);
        boneVertsInfo = new int[numverts];
        bonesId = new unsigned char[numverts];
        for (int i = 0; i < numverts; i++) {
            //modelFile.read((char*)&boneVertsInfo[i], sizeof(char));
            modelFile.read((char*)&bonesId[i], sizeof(char));
            boneVertsInfo[i] = (int)bonesId[i];
        }
        delete[]bonesId;
    }
    return boneVertsInfo;
}

vec3_s * MDLReader::readVerts(int numverts, int index) {
    vec3_s* verts = nullptr;
    if (numverts > 0) {
        modelFile.seekg(index);
        verts = new vec3_s[numverts];
        for (int i = 0; i < numverts; i++) {
            modelFile.read((char*) &verts[i], sizeof ( verts[i]));
        }
    }
    return verts;
}

int* MDLReader::readBoneNormalsInfo(int numnormals, int index) {
    int* boneNormalsInfo = nullptr;
    if (numnormals > 0) {
        modelFile.seekg(index);
        boneNormalsInfo = new int[numnormals];
        for (int i = 0; i < numnormals; i++) {
            modelFile.read((char*) &boneNormalsInfo[i], sizeof ( boneNormalsInfo[i]));
        }
    }
    return boneNormalsInfo;
}

vec3_s * MDLReader::readNormals(int numNormals, int index) {
    vec3_s* normals = nullptr;
    if (numNormals > 0) {
        modelFile.seekg(index);
        normals = new vec3_s[numNormals];
        for (int i = 0; i < numNormals; i++) {
            modelFile.read((char*) &normals[i], sizeof ( normals[i]));
        }
    }
    return normals;
}

MDLMesh * MDLReader::readMeshes(int index, int numMeshes, vec3_s* modelVertex,
        int* vertexBoneInfo, vec3_s* modelNormals, int* normalsBoneInfo) {
    MDLMesh* meshArray = nullptr;
    if (numMeshes > 0) {
        float uFactor, vFactor;
        mesh_s* mesh_str = new mesh_s[numMeshes];
        meshArray = new MDLMesh[numMeshes];
        for (int i = 0; i < numMeshes; i++) {
            modelFile.seekg(index);
            modelFile.read((char*) &mesh_str[i], sizeof ( mesh_str[i]));
            if(header.numtextures > 0){
                meshArray[i].SetTexture(*BuildTextureImage(mesh_str[i].skinref, textures[mesh_str[i].skinref].name));
                if (nskins != 0) {
                    uFactor = 1.0f / (float) textures[mesh_str[i].skinref].width;
                    vFactor = 1.0f / (float) textures[mesh_str[i].skinref].height;
                } else {//No hay texturas ?
                    uFactor = 1.0f;
                    vFactor = 1.0f;
                }                
            }else{
                uFactor = 1.0f;
                vFactor = 1.0f;
            }
            index = modelFile.tellg();
            meshArray[i].SetNumTriangles(mesh_str[i].numtris);
            modelFile.seekg(mesh_str[i].triindex);
            short triIndex;
            modelFile.read((char*) &triIndex, sizeof (triIndex));
            int numVert = triIndex;
            int triangleType = 0;
            int triangleIndex = 1;
            vertexinfo_s * vertexInfo = nullptr;
            vector<vertexinfo_s *>vertexInfoList;
            Triangles<vertexinfo_s *>* triangles;
            int index = 0;
            while (numVert != 0) {
                triangles = new Triangles<vertexinfo_s *>();
                if (numVert < 0) {
                    numVert = -numVert;
                    triangleType = 1;
                    triangleIndex = 1;
                    triangles->type = triangles->TRIANGLE_FAN;
                } else {
                    triangleType = 0;
                    triangleIndex = 1;
                    triangles->type = triangles->TRIANGLE_STRIP;
                }
                for (int v = 0; v < numVert; v++) {
                    vertexInfo = new vertexinfo_s();
                    vertexInfo->index = index;
                    vertexInfo->triangletype = triangleType;
                    vertexInfo->triangleTypeIndex = v;
                    modelFile.read((char*) &triIndex, sizeof (triIndex));
                    // El valor apuntado por tris es el óndice del vórtice.
                    vertexInfo->bone = vertexBoneInfo[triIndex];
                    vertexInfo->vertex = modelVertex[triIndex];
                    // El valor apuntado por tris es el óndice de la normal.
                    modelFile.read((char*) &triIndex, sizeof (triIndex));
                    vertexInfo->normal = modelNormals[triIndex];
                    // El valor apuntado por tris es la coordenada u.
                    modelFile.read((char*) &triIndex, sizeof (triIndex));
                    vertexInfo->ucoord = uFactor * triIndex;
                    vertexInfo->ucoords = triIndex;
                    // El valor apuntado por tris es la coordenada v.
                    modelFile.read((char*) &triIndex, sizeof (triIndex));
                    vertexInfo->vcoord = vFactor * triIndex;
                    vertexInfo->vcoords = triIndex;
                    vertexInfo->triangleIndex = triangleIndex;
                    if ((v + 1) % 3 == 0) {
                        triangleIndex = 1;
                    } else {
                        triangleIndex++;
                    }
                    vertexInfoList.push_back(vertexInfo);
                    triangles->vertexList.push_back(vertexInfo);
                    index++;
                }
                modelFile.read((char*) &triIndex, sizeof (triIndex));
                numVert = triIndex;
                meshArray[i].AddTriangles(triangles);
            } // while que recorre todos los vertices.
            meshArray[i].Fill(vertexInfoList, vertexInfoList.size());
        }
        delete[] mesh_str;
    }

    return meshArray;
}

bool MDLReader::isPowerOfTwo(int dimension) {
    return!(dimension == 0) && !(dimension & (dimension - 1));
}

MDLTexture * MDLReader::BuildTextureImage(int skinRef, string textureName) {
    MDLTexture* texture = nullptr;
    if (skinRef < nskins) {
        texture = new MDLTexture();
        texture->SetTextureImage(&textureImages[skins[skinRef]]);
        texture->SetTextureName(textureName);
    }
    return texture;
}
