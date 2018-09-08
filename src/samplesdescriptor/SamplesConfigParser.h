/*
 * Copyright 2018 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPLESCONFIGPARSER_H
#define	SAMPLESCONFIGPARSER_H
#include <string>
#include "../util/xml/XMLParserUtil.h"
#include "../util/xml/XMLEventHandler.h"
#include "SamplesConfig.h"

class SamplesConfigParser : public XMLEventHandler {
public:
    SamplesConfigParser();
    virtual ~SamplesConfigParser();
    virtual void startElement(void * user_data, const xmlChar *name,
            const xmlChar **attrs);
    virtual void characters(void * user_data, const xmlChar * ch, int len);
    virtual void endElement(void * user_data, const xmlChar * name);
    SamplesConfig* getParsedSamplesConfig(const char* SamplesConfigFilePath);
    
private:
    
    static const std::string SAMPLES_CONFIG;
    static const std::string CONFIG;
    static const std::string CAMERA;
    static const std::string WIDTH;
    static const std::string HEIGHT;
    static const std::string EYE;
    static const std::string UP;
    static const std::string CENTER;
    static const std::string NEAR;
    static const std::string FAR;
    static const std::string FOVX;
    static const std::string FOVY;
    static const std::string VECTOR;
    static const std::string X;
    static const std::string Y;
    static const std::string Z;
    static const std::string SAMPLE_MODELS;
    static const std::string SAMPLE_MODEL;
    static const std::string FORMAT;
    static const std::string NAME;
    static const std::string FILENAME;
    static const std::string DESCRIPTION;
    static const std::string MESH_SIZE;
    static const std::string VISIBLE_MESHES;
    static const std::string VISIBLE_MESH;
    static const std::string TRANSFORMS;
    static const std::string TRANSFORM;
    static const std::string ROTATION;
    static const std::string TRANSLATION;
    
    SamplesConfig* samplesConfig;
    
    bool isSamplesConfig;
    bool isConfig;
    bool isCamera;
    bool isWidth;
    bool isHeight;
    bool isEye;
    bool isUp;
    bool isCenter;
    bool isNear;
    bool isFar;
    bool isFovx;
    bool isFovy;
    bool isVector;
    bool isX;
    bool isY;
    bool isZ;
    bool isSampleModels;
    bool isSampleModel;
    bool isFormat;
    bool isName;
    bool isFileName;
    bool isDescription;
    bool isMeshSize;
    bool isVisibleMeshes;
    bool isVisibleMesh;
    bool isTransforms;
    bool isTransform;
    bool isRotation;
    bool isTranslation;

    MVector3<float>* tmpVec;
    SampleModel* tmpSampleModel;
    MTransform<float>* tmpTransform;
};

#endif	/* RESOURCESFILEPARSER_H */

