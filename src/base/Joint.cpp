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

#include "Joint.h"


Joint::Joint()
{
    this->position = nullptr;
    this->rotation = nullptr;
    this->inverseBindPose = nullptr;
    this->globalTransform = nullptr;
    this->localTransform = nullptr;
}

Joint::Joint(string name)
{
    this->name = name;
    this->position = nullptr;
    this->rotation = nullptr;
    this->inverseBindPose = nullptr;
    this->globalTransform = nullptr;
    this->localTransform = nullptr;
}

Joint::Joint(Joint& other)
{
    this->name = other.name;
    this->parent = other.parent;
    this->position = new MVector3<float>(*other.position);
    this->rotation = new MQuaternion<float>(*other.rotation);
    this->inverseBindPose = new  MTransform<float>(*other.inverseBindPose);
    this->globalTransform = new  MTransform<float>(*other.globalTransform);
    this->localTransform = new  MTransform<float>(*other.localTransform);
}


void Joint::SetName(string name)
{
    this->name = name;
}

string Joint::GetName()
{
    return this->name;
}

void Joint::SetParent(int index)
{
    this->parent = index;
}

int Joint::GetParent()
{
    return this->parent;
}

int Joint::GetIndex()
{
    return this->index;
}

void Joint::SetIndex(int index)
{
    this->index = index;
}

void Joint::SetPosition(MVector3<float>* pos)
{
    this->position = pos;
}

MVector3<float>* Joint::GetPosition()
{
    return this->position;
}

void Joint::SetRotation(MQuaternion<float>* rot)
{
    if(rotation) {
        delete rotation;
    }
    this->rotation = rot;
}

MQuaternion<float>* Joint::GetRotation()
{
    return this->rotation;
}

void Joint::SetInverseBindPose(MTransform<float>* inverseBindPose)
{
    this->inverseBindPose = inverseBindPose;
}

void Joint::SetGlobalTransform(MTransform<float>* globalTransform)
{
    this->globalTransform = globalTransform;
}

void Joint::SetLocalTransform(MTransform<float>* localTransform)
{
    this->localTransform = localTransform;
}

MTransform<float> * Joint::GetInverseBindPose()
{
    return this->inverseBindPose;
}

MTransform<float> * Joint::GetGlobalTransform()
{
    return this->globalTransform;
}

MTransform<float> * Joint::GetLocalTransform()
{
    return this->localTransform;
}

Joint::~Joint()
{
    if(position) {
        delete position;
    }
    if(rotation) {
        delete rotation;
    }
    if(inverseBindPose) {
        delete inverseBindPose;
    }
    if(globalTransform) {
        delete globalTransform;
    }
    if(localTransform) {
        delete localTransform;
    }
}
