/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef MD5JOINT_H
#define MD5JOINT_H
#include "../math/MTransform.h"
#include "string.h"
#include <string>


using namespace std;
// A bone joint in the skeletal structure, used for skeletal animations.
// When a vertex or point is assigned to one or more bone joints with a specified
// weight, the joint is referred to as an Influence.

//class MVector3;
//class MQuaternion;
class md5joint
{
public:
    md5joint();
    md5joint(string name);
    virtual ~md5joint();
    void setPosition(MVector3<float>* pos);
    void setRotation(MQuaternion<float>* rot);
    void setInverseBindPose(MTransform<float>* inverseBindPose);
    void setGlobalTransform(MTransform<float>* globalTransform);
    void setLocalTransform(MTransform<float>* localTransform);
    void setName(string name);
    void setParent(int index);
    MVector3<float>* getPosition();
    MQuaternion<float>* getRotation();
    MTransform<float>* getInverseBindPose();
    MTransform<float>* getGlobalTransform();
    MTransform<float>* getLocalTransform();
    string getName();
    int getParent();
private:
    string name;
    int parent;  // Parent joint index (-1 for no parent)
    MVector3<float>* position;
    MQuaternion<float>* rotation;
    MTransform<float>* inverseBindPose;
    MTransform<float>* globalTransform;
    MTransform<float>* localTransform;
};

#endif // MD5JOINT_H
