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

#ifndef VOXELIZERTOOL_H
#define VOXELIZERTOOL_H
#include "Mesh.h"
#include <iostream>
#include <sstream>
#include <fstream>

/**
 * @todo write docs
 */
class VoxelizerTool
{
public:
    /**
     * Default constructor
     */
    VoxelizerTool();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    VoxelizerTool(const VoxelizerTool& other);

    /**
     * Destructor
     */
    ~VoxelizerTool();

    Mesh* Voxelize(Mesh& mesh, float precision, BBox& voxelSize, bool autoSize, vector<BBox>& voxels);
    
    Mesh* VoxelixeExt(Mesh& mesh, int meshIndex, float precision, BBox& voxelSize, bool autoSize, vector<BBox>& voxels);
    
    void WriteOBJModel(Mesh& mesh, string destModelName);
private:    
    bool checkIntersection(Triangle& triangle, BBox& voxel);
};

#endif // VOXELIZERTOOL_H
