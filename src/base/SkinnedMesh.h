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
 * 
 */

#ifndef SKINNEDMESH_H
#define SKINNEDMESH_H
#include "Mesh.h"
#include "SkeletonPose.h"
#include <vector>
using namespace std;

class SkinnedMesh : public Mesh
{
public:
    SkinnedMesh();
    SkinnedMesh(Mesh& mesh);
    void SetBindPoseMesh(Mesh* bindPoseMesh);
    Mesh* GetBindPoseMesh();
    void updatePose(SkeletonPose<float>& pose);
    int weightsPerVertex;
    vector<float> weights;
    vector<int> jointIndices;    
    void applyPose();
    virtual void ApplyTransform(MTransform<float>& transform);
    virtual void ApplyTransforms();
private:
    Mesh* bindPoseMesh;
    SkeletonPose<float>* currentPose;
    string textureName;
};

#endif // SKINNEDMESH_H
