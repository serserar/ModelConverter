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

#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}


string Model::GetName()
{
    return this->name;
}

void Model::SetName(string name)
{
    this->name = name;
}

int Model::GetVersion()
{
    return this->version;
}

void Model::SetVersion(int version)
{
    this->version = version;
}

void Model::ComputeBBox()
{
}
void Model::OnUpdate(double dt)
{
}
BBox Model::GetBoundingBox()
{
    return this->bbox;
}

bool Model::intersect(MVector3<float>& rayOrigin, MVector3<float>& rayDest, MVector3<float>& intersectionPoint)
{
    bool intersect = false;
    for(auto mesh : meshes) {
        if(mesh->intersect(rayOrigin, rayDest, intersectionPoint)) {
            intersect = true;
            break;
        }
    }
    return intersect;
}

int Model::GetNumMeshes()
{
    return this->meshes.size();
}

void Model::SetNumMeshes(int numMeshes)
{
    this->numMeshes = numMeshes;
}

vector<Mesh *>::iterator Model::GetBeginMeshIterator()
{
    return meshes.begin();
}

vector<Mesh *>::iterator Model::GetEndMeshIterator()
{
    return meshes.end();
}

Mesh * Model::GetMesheArray()
{
    return meshes[0];
}

Mesh* Model::GetMesh(int index)
{
    Mesh* mesh = nullptr;
    if(index < meshes.size()) {
        mesh = meshes[index];
    }
    return mesh;
}

void Model::AddMesh(Mesh* mesh)
{
    meshes.push_back(mesh);
    ComputeBBox();
}


void Model::SetMeshArray(Mesh* meshArray, int size)
{
    for(int i = 0; i < size; i++) {
        meshes.push_back(&meshArray[i]);
    }
    ComputeBBox();
}

void Model::ApplyTransform(MTransform<float>& transform)
{
    auto it = meshes.begin();
    auto endit = meshes.end();
    Mesh* modelMesh;
    while(it != endit) {
        modelMesh = *it;
        modelMesh->ApplyTransform(transform);
        modelMesh->ApplyTransforms();
        ++it;
    }
}


AnimatedModel::AnimatedModel():Model()
{
    this->skeleton = nullptr;
}

AnimatedModel::AnimatedModel(const AnimatedModel& other)
{

}

AnimatedModel::~AnimatedModel()
{
    visibleMeshes.clear();
    for(auto mesh : meshes) {
        delete mesh;
    }
    meshes.clear();
}

SkinnedMesh * AnimatedModel::GetMesheArray()
{
    return meshes[0];
}

SkinnedMesh* AnimatedModel::GetMesh(int index)
{
    SkinnedMesh* mesh = nullptr;
    if(index < meshes.size()) {
        mesh = meshes[index];
    }
    return mesh;
}

void AnimatedModel::AddMesh(SkinnedMesh* mesh)
{
    AddMesh(mesh, true);
}

void AnimatedModel::AddMesh(SkinnedMesh* mesh, bool visible)
{
    meshes.push_back(mesh);
    if(visible) {
        visibleMeshes.push_back(mesh);
    }
    ComputeBBox();
}


void AnimatedModel::SetMeshArray(SkinnedMesh* meshArray, int size)
{
    visibleMeshes.clear();
    for(int i = 0; i < size; i++) {
        meshes.push_back(&meshArray[i]);
        visibleMeshes.push_back(&meshArray[i]);
    }
    ComputeBBox();
}

void AnimatedModel::SetVisibleMeshes(vector<int>& visibleMeshesIndex)
{
    visibleMeshes.clear();
    for(auto mindex : visibleMeshesIndex) {
        if(mindex < meshes.size()) {
            visibleMeshes.push_back(meshes.at(mindex));
        }
    }
}


vector<SkinnedMesh *>::iterator AnimatedModel::GetBeginMeshIterator()
{
    return meshes.begin();
}

vector<SkinnedMesh *>::iterator AnimatedModel::GetEndMeshIterator()
{
    return meshes.end();
}

vector<SkinnedMesh *>::iterator AnimatedModel::GetBeginVisibleMeshIterator()
{
    return visibleMeshes.begin();
}

vector<SkinnedMesh *>::iterator AnimatedModel::GetEndVisibleMeshIterator()
{
    return visibleMeshes.end();
}


Skeleton * AnimatedModel::GetSkeleton()
{
    return this->skeleton;
}

void AnimatedModel::SetSkeleton(Skeleton* skeleton)
{
    if(this->skeleton) {
        delete this->skeleton;
    }
    this->skeleton = skeleton;
}

int AnimatedModel::GetNumJoints()
{
    return this->numJoints;
}

void AnimatedModel::SetNumJoints(int numJoints)
{
    this->numJoints = numJoints;
}


Animation * AnimatedModel::GetAnimationArray()
{
    return animations[0];
}

int AnimatedModel::GetAnimationSize()
{
    return animations.size();
}


void AnimatedModel::AddAnimation(Animation* animation)
{
    this->animations.push_back(animation);
    this->animationManager.addAnimation(animation);
}

void AnimatedModel::FillAnimations(Animation* animationsArray, int size)
{
    for(int i = 0; i < size; i++) {
        animations.push_back(&animationsArray[i]);
    }
}

vector<Animation *>::iterator AnimatedModel::GetBeginAnimationIterator()
{
    return animations.begin();
}

vector<Animation *>::iterator AnimatedModel::GetEndAnimationIterator()
{
    return animations.end();
}


void AnimatedModel::ComputeBBox()
{
    float xmin = 0.0f,ymin = 0.0f,zmin = 0.0f,xmax = 0.0f,ymax = 0.0f,zmax = 0.0f;
    bbox.boundMax.SetX(xmax);
    bbox.boundMax.SetY(ymax);
    bbox.boundMax.SetZ(zmax);
    bbox.boundMin.SetX(xmin);
    bbox.boundMin.SetY(ymin);
    bbox.boundMin.SetZ(zmin);
    for(auto mesh : meshes) {
        mesh->computeBBox();
        xmin = mesh->bbox.boundMin.GetX();
        ymin = mesh->bbox.boundMin.GetY();
        zmin = mesh->bbox.boundMin.GetZ();
        xmax = mesh->bbox.boundMax.GetX();
        ymax = mesh->bbox.boundMax.GetY();
        zmax = mesh->bbox.boundMax.GetZ();
        if ( xmin < bbox.boundMin.GetX() ) bbox.boundMin.SetX(xmin);
        if ( ymin < bbox.boundMin.GetY() ) bbox.boundMin.SetY(ymin);
        if ( zmin < bbox.boundMin.GetZ() ) bbox.boundMin.SetZ(zmin);
        if ( xmax > bbox.boundMax.GetX() ) bbox.boundMax.SetX(xmax);
        if ( ymax > bbox.boundMax.GetY() ) bbox.boundMax.SetY(ymax);
        if ( zmax > bbox.boundMax.GetZ() ) bbox.boundMax.SetZ(zmax);
    }

}

void AnimatedModel::OnUpdate(double dt)
{
    this->animationManager.update(dt);
    if(this->animationManager.needsloadFrame) {
        updatePose(*this->animationManager.GetFrame()->GetSkeletonPose());
        ComputeBBox();
    }else {
        
    }
}

void AnimatedModel::updatePose(SkeletonPose<float>& pose)
{
    this->currentPose = &pose;
    this->currentPose->SetBindPose();
    for(auto mesh : meshes) {
        mesh->updatePose(*currentPose);
    }
}

void AnimatedModel::setAnimation(string animation)
{
    this->animationManager.SetAnimation(animation);
    updatePose(*this->animationManager.GetFrame()->GetSkeletonPose());
}


SkeletonPose<float> * AnimatedModel::GetCurrentPose()
{
    return this->currentPose;
}

bool AnimatedModel::intersect(MVector3<float>& rayOrigin, MVector3<float>& rayDest, MVector3<float>& intersectionPoint)
{
    bool intersect = false;
    for(auto mesh : meshes) {
        if(mesh->intersect(rayOrigin, rayDest, intersectionPoint)) {
            intersect = true;
            break;
        }
    }
    return intersect;
}

void AnimatedModel::ApplyTransform(MTransform<float>& transform)
{
    auto it = meshes.begin();
    auto endit = meshes.end();
    Mesh* modelMesh;
    while(it != endit) {
        modelMesh = *it;
        modelMesh->ApplyTransform(transform);
        modelMesh->ApplyTransforms();
        ++it;
    }
    ComputeBBox();
}
