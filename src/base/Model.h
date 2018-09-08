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

#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "Skeleton.h"
#include "SkinnedMesh.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "BBox.h"

using namespace std;
class Model {
public:
    Model();
    virtual ~Model();
    string GetName();
    void SetName(string name);
    int GetVersion();
    void SetVersion(int version);
    virtual void OnUpdate(double dt);
    void UpdateTriangleList();
    int GetNumMeshes();
    void SetNumMeshes(int numMeshes);
    Mesh* GetMesheArray();
    void AddMesh(Mesh* mesh);
    void SetMeshArray(Mesh* meshArray, int size);
    Mesh* GetMesh(int index);
    vector<Mesh*>::iterator GetBeginMeshIterator();
    vector<Mesh*>::iterator GetEndMeshIterator();
    BBox GetBoundingBox();
    virtual void ApplyTransform(MTransform<float>& transform);
    virtual bool intersect(MVector3<float>& rayOrigin, MVector3<float>& rayDest, MVector3<float>& intersectionPoint);
protected:
    virtual void ComputeBBox();
    string name;
    int version;
    BBox bbox;
    int numMeshes;
private:
    vector<Mesh*> meshes;
};

class AnimatedModel : public Model
{
public:

    AnimatedModel();
    AnimatedModel(const AnimatedModel& other);
    virtual ~AnimatedModel();
    int GetNumJoints();
    void SetNumJoints(int numJoints);
    Skeleton* GetSkeleton();
    void SetSkeleton(Skeleton* skeleton);
    Animation* GetAnimationArray();
    int GetAnimationSize();
    void AddAnimation(Animation* animation);
    Animation* GetAnimation();
    vector<SkinnedMesh*>::iterator GetBeginMeshIterator();
    vector<SkinnedMesh*>::iterator GetEndMeshIterator();
    vector<SkinnedMesh*>::iterator GetBeginVisibleMeshIterator();
    vector<SkinnedMesh*>::iterator GetEndVisibleMeshIterator();
    SkinnedMesh* GetMesheArray();
    void AddMesh(SkinnedMesh* mesh);
    void AddMesh(SkinnedMesh* mesh, bool visible);
    void SetMeshArray(SkinnedMesh* meshArray, int size);
    void SetVisibleMeshes(vector<int>& visibleMeshesIndex);
    SkinnedMesh* GetMesh(int index);
    vector<Animation*>::iterator GetBeginAnimationIterator();
    vector<Animation*>::iterator GetEndAnimationIterator();
    void FillAnimations(Animation* animationsArray, int size);
    vector<MVector3<float>*> GetVertexFinalPosition(int mesh);
    int* GetVertexIndex(int nummesh);
    void setAnimation(string animation);
    void updatePose(SkeletonPose<float>& pose);
    SkeletonPose<float>* GetCurrentPose();
    vector<Animation*> animations;
    virtual void OnUpdate(double dt);
    bool intersect(MVector3<float>& rayOrigin, MVector3<float>& rayDest, MVector3<float>& intersectionPoint) override;
    virtual void ApplyTransform(MTransform<float>& transform);
protected:
    virtual void ComputeBBox();
private:
    int numJoints;
    Skeleton* skeleton;
    vector<SkinnedMesh*> meshes;
    vector<SkinnedMesh*> visibleMeshes;
    SkeletonPose<float>* currentPose;
    AnimationManager animationManager;
};


#endif // MODEL_H
