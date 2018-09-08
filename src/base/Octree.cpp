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

#include "Octree.h"

Octree::Octree(BBox& bbox, std::vector<OctreeEntity*>& entitiesList)
{
    this->bbox=bbox;
    this->entitiesList = entitiesList;
}

Octree::Octree(const Octree& other)
{

}

Octree::~Octree()
{
    for(auto octree : children)
        delete octree;
}

void Octree::BuildTree()
{
//     MVector3<float> half = bbox.boundMax - bbox.boundMin;
//     half/=2;
//     MVector3<float> center = bbox.boundMin + half;
//     MVector3<float> o0min=bbox.boundMin;
//     MVector3<float> o0max=center;
//     MVector3<float> o1min(center.GetX(),o0min.GetY(), o0min.GetZ());
//     MVector3<float> o1max(bbox.boundMax.GetX(),center.GetY(), center.GetZ());
//     MVector3<float> o2min(o0min.GetX(),o0min.GetY(), center.GetZ());
//     MVector3<float> o2max(center.GetX(),center.GetY(), bbox.boundMax.GetZ());
//     MVector3<float> o3min(center.GetX(), o1min.GetY(), center.GetZ());
//     MVector3<float> o3max(bbox.boundMax.GetX(),center.GetY(), bbox.boundMax.GetZ());
//     MVector3<float> o4min(bbox.boundMin.GetX(), center.GetY(), bbox.boundMin.GetZ());
//     MVector3<float> o4max(center.GetX(), bbox.boundMax.GetY(), center.GetZ());
//     MVector3<float> o5min(center.GetX(), center.GetY(), bbox.boundMin.GetZ());
//     MVector3<float> o5max(bbox.boundMax.GetX(), bbox.boundMax.GetY(), center.GetZ());
//     MVector3<float> o6min(bbox.boundMin.GetX(), center.GetY(), center.GetZ());
//     MVector3<float> o6max(center.GetX(), bbox.boundMax.GetY(), bbox.boundMax.GetZ());
//     MVector3<float> o7min=center;
//     MVector3<float> o7max=bbox.boundMax;
//     BBox octant[8]= {BBox(o0min, o0max), BBox(o1min, o1max), BBox(o2min, o2max), BBox(o3min, o3max),
//                      BBox(o4min, o4max), BBox(o5min, o5max), BBox(o6min, o6max), BBox(o7min, o7max)};
    BBox* octant = bbox.OcTreeSubDivision();
    for(auto octreeEntity : entitiesList) {

    }
}
