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

#include "SamplesConfigParser.h"

const std::string SamplesConfigParser::SAMPLES_CONFIG = "SamplesConfig";
const std::string SamplesConfigParser::CONFIG = "Config";
const std::string SamplesConfigParser::CAMERA = "Camera";
const std::string SamplesConfigParser::WIDTH = "Width";
const std::string SamplesConfigParser::HEIGHT = "Height";
const std::string SamplesConfigParser::EYE = "Eye";
const std::string SamplesConfigParser::UP = "Up";
const std::string SamplesConfigParser::CENTER = "Center";
const std::string SamplesConfigParser::NEAR = "Near";
const std::string SamplesConfigParser::FAR = "Far";
const std::string SamplesConfigParser::FOVX = "Fovx";
const std::string SamplesConfigParser::FOVY = "Fovy";
const std::string SamplesConfigParser::VECTOR = "Vector";
const std::string SamplesConfigParser::X = "X";
const std::string SamplesConfigParser::Y = "Y";
const std::string SamplesConfigParser::Z = "Z";
const std::string SamplesConfigParser::SAMPLE_MODELS = "SampleModels";
const std::string SamplesConfigParser::SAMPLE_MODEL = "SampleModel";
const std::string SamplesConfigParser::FORMAT = "Format";
const std::string SamplesConfigParser::NAME = "Name";
const std::string SamplesConfigParser::FILENAME = "FileName";
const std::string SamplesConfigParser::DESCRIPTION = "Description";
const std::string SamplesConfigParser::MESH_SIZE = "MeshSize";
const std::string SamplesConfigParser::VISIBLE_MESHES = "VisibleMeshes";
const std::string SamplesConfigParser::VISIBLE_MESH = "VisibleMesh";
const std::string SamplesConfigParser::TRANSFORMS = "Transforms";
const std::string SamplesConfigParser::TRANSFORM = "Transform";
const std::string SamplesConfigParser::ROTATION = "Rotation";
const std::string SamplesConfigParser::TRANSLATION = "Translation";

SamplesConfigParser::SamplesConfigParser() {
    this->isSamplesConfig = false;
    this->isConfig = false;
    this->isCamera = false;
    this->isWidth = false;
    this->isHeight = false;
    this->isEye = false;
    this->isUp = false;
    this->isCenter = false;
    this->isNear = false;
    this->isFar = false;
    this->isFovx = false;
    this->isFovy = false;
    this->isVector = false;
    this->isX = false;
    this->isY = false;
    this->isZ = false;
    this->isSampleModels = false;
    this->isSampleModel = false;
    this->isFormat = false;
    this->isFileName = false;
    this->isName = false;
    this->isDescription = false;
    this->isMeshSize = false;
    this->isVisibleMeshes = false;
    this->isVisibleMesh = false;
    this->isTransforms = false;
    this->isTransform = false;
    this->isRotation = false;
    this->isTranslation = false;
    this->tmpVec = nullptr;
    this->tmpSampleModel = nullptr;
    this->tmpTransform = nullptr;
}

SamplesConfigParser::~SamplesConfigParser() {
}

SamplesConfig* SamplesConfigParser::getParsedSamplesConfig(const char* SamplesConfigFilePath) {
    XmlParserUtil parser;
    parser.parseXML(SamplesConfigFilePath, *this);
    return this->samplesConfig;
}

void SamplesConfigParser::startElement(void* user_data, const xmlChar* name,
                                       const xmlChar** attrs) {
    std::string nodeName = (char*) name;
    if (nodeName.compare(SamplesConfigParser::SAMPLES_CONFIG) == 0) {
        isSamplesConfig = true;
        samplesConfig = new SamplesConfig();
    } else if (nodeName.compare(SamplesConfigParser::CONFIG) == 0) {
        isConfig = true;
    } else if (nodeName.compare(SamplesConfigParser::CAMERA) == 0) {
        isCamera = true;
    } else if (nodeName.compare(SamplesConfigParser::WIDTH) == 0) {
        isWidth = true;
    } else if (nodeName.compare(SamplesConfigParser::HEIGHT) == 0) {
        isHeight = true;
    } else if (nodeName.compare(SamplesConfigParser::EYE) == 0) {
        isEye = true;
    } else if (nodeName.compare(SamplesConfigParser::UP) == 0) {
        isUp = true;
    } else if (nodeName.compare(SamplesConfigParser::CENTER) == 0) {
        isCenter = true;
    } else if (nodeName.compare(SamplesConfigParser::NEAR) == 0) {
        isNear = true;
    } else if (nodeName.compare(SamplesConfigParser::FAR) == 0) {
        isFar = true;
    } else if (nodeName.compare(SamplesConfigParser::FOVX) == 0) {
        isFovx = true;
    } else if (nodeName.compare(SamplesConfigParser::FOVY) == 0) {
        isFovy = true;
    } else if (nodeName.compare(SamplesConfigParser::VECTOR) == 0) {
        isVector = true;
        this->tmpVec = new MVector3<float>();
    } else if (nodeName.compare(SamplesConfigParser::X) == 0) {
        isX = true;
    } else if (nodeName.compare(SamplesConfigParser::Y) == 0) {
        isY = true;
    } else if (nodeName.compare(SamplesConfigParser::Z) == 0) {
        isZ = true;
    } else if (nodeName.compare(SamplesConfigParser::SAMPLE_MODELS) == 0) {
        isSampleModels = true;
    } else if (nodeName.compare(SamplesConfigParser::SAMPLE_MODEL) == 0) {
        tmpSampleModel = new SampleModel();
        isSampleModel = true;
    } else if (nodeName.compare(SamplesConfigParser::FORMAT) == 0) {
        isFormat = true;
    } else if (nodeName.compare(SamplesConfigParser::FILENAME) == 0) {
        isFileName = true;
    }else if (nodeName.compare(SamplesConfigParser::NAME) == 0) {
        isName = true;
    } else if (nodeName.compare(SamplesConfigParser::DESCRIPTION) == 0) {
        isDescription = true;
    } else if (nodeName.compare(SamplesConfigParser::MESH_SIZE) == 0) {
        isMeshSize = true;
    } else if (nodeName.compare(SamplesConfigParser::VISIBLE_MESHES) == 0) {
        isVisibleMeshes = true;
    } else if (nodeName.compare(SamplesConfigParser::VISIBLE_MESH) == 0) {
        isVisibleMesh = true;
    } else if (nodeName.compare(SamplesConfigParser::TRANSFORMS) == 0) {
        isTransforms = true;
    } else if (nodeName.compare(SamplesConfigParser::TRANSFORM) == 0) {
        tmpTransform = new MTransform<float>();
        isTransform = true;
    } else if (nodeName.compare(SamplesConfigParser::ROTATION) == 0) {
        isRotation = true;
    } else if (nodeName.compare(SamplesConfigParser::TRANSLATION) == 0) {
        isTranslation = true;
    }
}

void SamplesConfigParser::characters(void* user_data, const xmlChar* ch, int len) {
    std::string nodeChars;
    nodeChars.append((char*) ch, len);
    if (isWidth) {
        int width = std::stoi(nodeChars);
        samplesConfig->config.cam.SetWidth(width);
    } else if (isHeight) {
        int height = std::stoi(nodeChars);
        samplesConfig->config.cam.SetHeight(height);
    } else if (isVector) {
        if (isX) {
            float x = std::stof(nodeChars);
            if(isRotation) {
                x = Math<float>::DegreesToRadians(x);
            }
            tmpVec->SetX(x);
        } else if (isY) {
            float y = std::stof(nodeChars);
            if(isRotation) {
                y = Math<float>::DegreesToRadians(y);
            }
            tmpVec->SetY(y);
        } else if (isZ) {
            float z = std::stof(nodeChars);
            if(isRotation) {
                z = Math<float>::DegreesToRadians(z);
            }
            tmpVec->SetZ(z);
        }
    } else if (isNear) {
        float near = std::stof(nodeChars);
        samplesConfig->config.cam.SetNear(near);
    } else if (isFar) {
        float far = std::stof(nodeChars);
        samplesConfig->config.cam.SetFar(far);
    } else if (isFovx) {
        float fovx = std::stof(nodeChars);
        samplesConfig->config.cam.SetFovX(fovx);
    } else if (isFovy) {
        float fovy = std::stof(nodeChars);
        samplesConfig->config.cam.SetFovY(fovy);
    } else if (isFormat) {
        tmpSampleModel->format=nodeChars;
    } else if (isFileName) {
        tmpSampleModel->fileName=nodeChars;
    }  else if (isName) {
        tmpSampleModel->name=nodeChars;
    } else if (isDescription) {
        tmpSampleModel->description=nodeChars;
    } else if (isMeshSize) {
        int meshSize = std::stoi(nodeChars);
        tmpSampleModel->meshSize=meshSize;
    } else if (isVisibleMesh) {
        int visibleMesh = std::stoi(nodeChars);
        tmpSampleModel->visibleMeshes.push_back(visibleMesh);
    }
}

void SamplesConfigParser::endElement(void* user_data, const xmlChar* name) {
    std::string nodeName = (char*) name;
    if (nodeName.compare(SamplesConfigParser::SAMPLES_CONFIG) == 0) {
        isSamplesConfig = false;
    } else if (nodeName.compare(SamplesConfigParser::CONFIG) == 0) {
        isConfig = false;
    } else if (nodeName.compare(SamplesConfigParser::CAMERA) == 0) {
        samplesConfig->config.cam.init();
        isCamera = false;
    } else if (nodeName.compare(SamplesConfigParser::WIDTH) == 0) {
        isWidth = false;
    } else if (nodeName.compare(SamplesConfigParser::HEIGHT) == 0) {
        isHeight = false;
    } else if (nodeName.compare(SamplesConfigParser::EYE) == 0) {
        isEye = false;
    } else if (nodeName.compare(SamplesConfigParser::UP) == 0) {
        isUp = false;
    } else if (nodeName.compare(SamplesConfigParser::CENTER) == 0) {
        isCenter = false;
    } else if (nodeName.compare(SamplesConfigParser::NEAR) == 0) {
        isNear = false;
    } else if (nodeName.compare(SamplesConfigParser::FAR) == 0) {
        isFar = false;
    } else if (nodeName.compare(SamplesConfigParser::FOVX) == 0) {
        isFovx = false;
    } else if (nodeName.compare(SamplesConfigParser::FOVY) == 0) {
        isFovy = false;
    } else if (nodeName.compare(SamplesConfigParser::VECTOR) == 0) {
        if(isEye) {
            samplesConfig->config.cam.SetEye(*tmpVec);
        } else if(isUp) {
            samplesConfig->config.cam.SetUp(*tmpVec);
        } else if (isCenter) {
            samplesConfig->config.cam.SetCenter(*tmpVec);
        } else if(isTransform) {
            if(isRotation) {
                tmpTransform->SetRotation(*tmpVec);
            }else if(isTranslation){
                tmpTransform->SetTranslation(*tmpVec);
            }
        }
        delete this->tmpVec;
        this->tmpVec = nullptr;
        isVector = false;
    } else if (nodeName.compare(SamplesConfigParser::X) == 0) {
        isX = false;
    } else if (nodeName.compare(SamplesConfigParser::Y) == 0) {
        isY = false;
    } else if (nodeName.compare(SamplesConfigParser::Z) == 0) {
        isZ = false;
    } else if (nodeName.compare(SamplesConfigParser::SAMPLE_MODELS) == 0) {
        isSampleModels = false;
    } else if (nodeName.compare(SamplesConfigParser::SAMPLE_MODEL) == 0) {
        this->samplesConfig->sampleModels.push_back(*tmpSampleModel);
        isSampleModel = false;
    } else if (nodeName.compare(SamplesConfigParser::FORMAT) == 0) {
        isFormat = false;
    } else if (nodeName.compare(SamplesConfigParser::FILENAME) == 0) {
        isFileName = false;
    } else if (nodeName.compare(SamplesConfigParser::NAME) == 0) {
        isName = false;
    } else if (nodeName.compare(SamplesConfigParser::DESCRIPTION) == 0) {
        isDescription = false;
    } else if (nodeName.compare(SamplesConfigParser::MESH_SIZE) == 0) {
        isMeshSize = false;
    } else if (nodeName.compare(SamplesConfigParser::VISIBLE_MESHES) == 0) {
        isVisibleMeshes = false;
    } else if (nodeName.compare(SamplesConfigParser::VISIBLE_MESH) == 0) {
        isVisibleMesh = false;
    } else if (nodeName.compare(SamplesConfigParser::TRANSFORMS) == 0) {
        isTransforms = false;
    } else if (nodeName.compare(SamplesConfigParser::TRANSFORM) == 0) {
        tmpSampleModel->transforms.push_back(*tmpTransform);
        delete tmpTransform;
        isTransform = false;
    } else if (nodeName.compare(SamplesConfigParser::ROTATION) == 0) {
        isRotation = false;
    } else if (nodeName.compare(SamplesConfigParser::TRANSLATION) == 0) {
        isTranslation = false;
    }
}


