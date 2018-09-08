/*
 * Copyright 2017 <copyright holder> <email>
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

#ifndef MESHUTILS_H
#define MESHUTILS_H
#include "BBox.h"
#include "Mesh.h"
#include "Skeleton.h"
#include "Cube.h"
#include "RectangularPrism.h"

class MeshUtils
{
public:
    MeshUtils();
    MeshUtils(const MeshUtils& other);
    ~MeshUtils();
    static BBox* buildBBox(Mesh& mesh);
    static MVector3<float> GetBaryCentricCoords(Triangle& triangle, MVector3<float>& pointInside);
    static Mesh* buildMeshFromSkeleton(Skeleton& skeleton, float size);
};

#endif // MESHUTILS_H
