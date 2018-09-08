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

#ifndef AUTORIG_H
#define AUTORIG_H
#include "Model.h"
#include "VoxelizerTool.h"
#include <map>
#include <limits>
#include <iostream>

class Cluster{
    
public:
    Cluster();
    Cluster(Joint& joint);
    void AddVertex(MVector3<float>& vertex);
    bool CheckInside(MVector3<float>& vertex);
    BBox box;
    string name;
    MVector3<float> center;
private:    
};

/**
 * @todo write docs
 */
class AutoRig
{
public:
    /**
     * Default constructor
     */
    AutoRig();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    AutoRig(const AutoRig& other);

    /**
     * Destructor
     */
    ~AutoRig();

    SkinnedMesh* AutoRigMesh(Mesh& mesh, int meshIndex, Skeleton& skeleton);
    
    void BuildClusters(SkinnedMesh& mesh, Skeleton& skeleton);
    
    void PrintBoneCluster(SkinnedMesh& mesh, Skeleton& skeleton, std::ostream& output);
    
private:
    map<int,Cluster> boneClusterTable;
    
    SkinnedMesh* NearestNeighbour(Mesh& mesh, Skeleton& skeleton);
    
    SkinnedMesh* CheckCluster(Mesh& mesh, Skeleton& skeleton);
    
    SkinnedMesh* CheckBoneHeat(Mesh& mesh, int meshIndex, Skeleton& skeleton);
    
    SkinnedMesh* CheckGraphCluster(Mesh& mesh, int meshIndex, Skeleton& skeleton);
};

#endif // AUTORIG_H
