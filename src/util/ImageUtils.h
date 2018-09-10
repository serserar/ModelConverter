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

#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H
#include "../base/Model.h"
#include "../base/MeshUtils.h"
#include "../base/Camera.h"
#include "../image/Image.h"
#include "../math/MVector3.h"
/**
 * @todo write docs
 */
class ImageUtils
{
public:
    /**
     * Default constructor
     */
    ImageUtils();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    ImageUtils(const ImageUtils& other);


    /**
     * Destructor
     */
    ~ImageUtils();

    
    static void Snapshot(Camera& camera, AnimatedModel& model, vector<Ray>& rayList, int type, vector<Image*>& imageList);
    
    static Image* Snapshot(Camera& camera, AnimatedModel& model, bool printDebug = false);
    
    static Image* Snapshot(Camera& camera, Mesh& mesh, bool printDebug = false);
    
    static Mesh* GetMeshFromDepthImageList(Camera& camera, vector<Image*>& imgList, bool printDebug = false);
    
    static Mesh* GetMeshFromDepthImage(Camera& camera, Image& img, bool printDebug = false);
    
private:
     static void toGrayScaleImage(vector<Mesh*> meshes);  
     static void Snapshot(Image& modelImage, Camera& camera, Mesh& mesh, bool printDebug = false);
};

#endif // IMAGEUTILS_H
