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

#ifndef MODELSAMPLERAPP_H
#define MODELSAMPLERAPP_H
#include <string>
#include <vector>
#include <experimental/filesystem>
#include <fstream>
#include "base/Model.h"
#include "base/Camera.h"
#include "base/MDLImporter.h"
#include "mdl/MDLReader.h"
#include "util/ImageUtils.h"
#include "image/PPMReader.h"
#include "samplesdescriptor/SamplesConfigParser.h"
#include "base/VoxelizerTool.h"
/**
 * @todo write docs
 */
class ModelSamplerApp
{
public:
    /**
     * Default constructor
     */
    ModelSamplerApp(std::string inputPath, std::string destPath, std::string sampleFileName, bool sample3d);

    /**
     * Destructor
     */
    ~ModelSamplerApp();
    
    void Run();
    void SampleModel(AnimatedModel& model, Camera& cam, string modelDestPath, int samples, std::vector<MTransform<float>>& modelTransforms);
private:
    
    std::string inputPath;
    std::string destPath;
    std::string sampleFileName;
    
    MTransform<float> GenerateScaleTransformToCameraBounds(AnimatedModel& model, Camera& cam);
    vector<string> modelsPath;
    vector<string> skeletonsPath;
    bool sample2d;
    bool sample3d;
};

#endif // MODELSAMPLERAPP_H
