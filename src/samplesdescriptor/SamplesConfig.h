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

#ifndef SAMPLESCONFIG_H
#define SAMPLESCONFIG_H
#include <vector>
#include <string>
#include "../math/MTransform.h"
#include "../base/Camera.h"

class Config{
public:
    Camera cam;
};
class SampleModel{
public:
    std::string format;
    std::string name;
    std::string fileName;
    std::string description;
    int meshSize;
    std::vector<int> visibleMeshes;
    std::vector<MTransform<float>> transforms;
};
/**
 * @todo write docs
 */
class SamplesConfig
{
public:
    /**
     * Default constructor
     */
    SamplesConfig();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    SamplesConfig(const SamplesConfig& other);

    /**
     * Destructor
     */
    ~SamplesConfig();
    Config config;
    std::vector<SampleModel> sampleModels;

};

#endif // SAMPLESCONFIG_H
