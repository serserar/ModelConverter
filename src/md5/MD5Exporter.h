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

#ifndef MD5EXPORTER_H
#define MD5EXPORTER_H
#include "../base/Model.h"
#include "../md5/md5model.h"
#include "Options.h"

class MD5Exporter
{
public:
    MD5Exporter();
    MD5Exporter(const MD5Exporter& other);
    ~MD5Exporter();
    md5model* Convert(AnimatedModel& model, Options& options);
    void buildMD5Skeleton(std::vector<md5joint*>& skeleton, Skeleton& mdlSkeleton);
    md5mesh* buildMD5Mesh(SkinnedMesh& mesh, string materialPath);
    void buildMD5Vertex(vector<md5vertex*>& vertexList, vector<md5weight*>& weightList, SkinnedMesh& mesh);
    void buildMD5Triangles(vector<md5triangle*>& triangleList, SkinnedMesh& mesh);
    void buildMD5Animations(vector<md5animation*>& animationList, Animation* animations, int size);
    md5animbaseframe* buildMD5BaseFrame(vector<md5joint*>& joints);
    md5animjointlocation* buildmd5animjointlocation(md5joint& joint);
    MTransform<float>* getBindTransform(MVector3<float>& translation, MVector3<float>& rot);
    MMatrix3<float>* buildMatrix(MVector3<float>& rot);
    string space2underscore(string text);
};

#endif // MD5EXPORTER_H
