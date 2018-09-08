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

#ifndef SKELETON_H
#define SKELETON_H
#include <vector>
#include <string>
#include "Joint.h"

class Skeleton
{
public:
    Skeleton();
    Skeleton(Skeleton& skeleton);
    ~Skeleton();
    Skeleton& operator=(Skeleton& skeleton);
    int getSize();
    string getName();
    void setName(string name);
    void AddJoint(Joint* joint);
    Joint* GetJoint(int index);
    void FillJoints(Joint* jointsArray, int size);
    Joint* GetJointArray();
    int GetJointSize();
    Joint* GetParentJoint();
    vector<Joint*> joints;
    Joint* parentJoint;
    void ApplyTransform(MTransform<float>& transform);
    void ApplyRotation(MQuaternion<float>& rotation);
private:
    string name;
};

#endif // SKELETON_H
