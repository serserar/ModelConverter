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

#ifndef JOINT_H
#define JOINT_H
#include "../math/MTransform.h"
#include <string>
using namespace std;

class Joint
{
public:
    Joint();
    Joint(string name);
    Joint(Joint& other);
    virtual ~Joint();
    void SetPosition(MVector3<float>* pos);
    void SetRotation(MQuaternion<float>* rot);
    void SetInverseBindPose(MTransform<float>* inverseBindPose);
    void SetGlobalTransform(MTransform<float>* globalTransform);
    void SetLocalTransform(MTransform<float>* localTransform);
    void SetName(string name);
    void SetParent(int index);
    void SetIndex(int index);
    MVector3<float>* GetPosition();
    MQuaternion<float>* GetRotation();
    MTransform<float>* GetInverseBindPose();
    MTransform<float>* GetGlobalTransform();
    MTransform<float>* GetLocalTransform();
    string GetName();
    int GetParent();
    int GetIndex();
private:
    string name;
    int parent;  // Parent joint index (-1 for no parent)
    int index;
    MVector3<float>* position;
    MQuaternion<float>* rotation;
    MTransform<float>* inverseBindPose;
    MTransform<float>* globalTransform;
    MTransform<float>* localTransform;
};

#endif // JOINT_H
