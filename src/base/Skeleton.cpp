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

#include "Skeleton.h"

Skeleton::Skeleton()
{
    this->parentJoint = nullptr;
    this->name="";
}

Skeleton::Skeleton(Skeleton& skeleton)
{
    this->parentJoint = new Joint(*skeleton.parentJoint);
    this->name = skeleton.name;
    for(auto joint : skeleton.joints){
        this->joints.push_back(new Joint(*joint));
    }
}


Skeleton::~Skeleton()
{
    for(Joint* joint : joints){
        if(joint != parentJoint){
            delete joint;
        }
    }
    delete parentJoint;
}

Skeleton& Skeleton::operator=(Skeleton& skeleton)
{
    this->parentJoint = new Joint(*skeleton.parentJoint);
    this->name = skeleton.name;
    for(auto joint : skeleton.joints){
        this->joints.push_back(new Joint(*joint));
    }
    return *this;
}


int Skeleton::getSize()
{
    return joints.size();
}


string Skeleton::getName()
{
    return name;
}

void Skeleton::setName(string name)
{
    this->name = name;
}

void Skeleton::AddJoint(Joint* joint) {
    joints.push_back(joint);
}

Joint* Skeleton::GetJoint(int index) {
    Joint* joint = nullptr;
    if (joints.size() > index) {
        joint = joints.at(index);
    }
    return joint;
}

void Skeleton::FillJoints(Joint* jointsArray, int size) {
    for(int i = 0; i < size; i++){
        if(jointsArray[i].GetParent() == 1){
            this->parentJoint = &jointsArray[i]; 
        }
        joints.push_back(&jointsArray[i]);
    }
    //joints.assign(size, jointsArray);
}

Joint* Skeleton::GetJointArray() {
    return joints[0];
}

int Skeleton::GetJointSize() {
    return joints.size();
}

Joint * Skeleton::GetParentJoint()
{
    if(!parentJoint){
        for(Joint* joint : joints){
            if(joint->GetParent()==-1){
                parentJoint = joint;
                break;
            }
        }
    }
    return parentJoint;
}

void Skeleton::ApplyTransform(MTransform<float>& transform)
{
    if(!parentJoint){
        GetParentJoint();
    }
    if(parentJoint){
        MQuaternion<float>* q1 = parentJoint->GetRotation();
        MQuaternion<float> q2;
        q2.FromRotationMatrix(transform.matrix);
        MQuaternion<float>* res = q2 * *q1;
        parentJoint->SetRotation(res);
    }
}

void Skeleton::ApplyRotation(MQuaternion<float>& rotation)
{
    if(!parentJoint){
        GetParentJoint();
    }
    if(parentJoint){
        MQuaternion<float>* q1 = parentJoint->GetRotation();
        MQuaternion<float>* res = rotation * *q1;
        parentJoint->SetRotation(res);
        //parentJoint->SetPosition(rotation.rotate(*parentJoint->GetPosition()));
    }
}
