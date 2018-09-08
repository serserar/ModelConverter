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


#include "md5joint.h"

md5joint::md5joint()
{

}

md5joint::md5joint(string name)
{
    this->name = name;
}

void md5joint::setName(string name)
{
    this->name = name;
}

string md5joint::getName()
{
    return this->name;
}

void md5joint::setParent(int index)
{
    this->parent = index;
}

int md5joint::getParent()
{
    return this->parent;
}

void md5joint::setPosition(MVector3<float>* pos)
{
    this->position = pos;
}

MVector3<float>* md5joint::getPosition()
{
    return this->position;
}

void md5joint::setRotation(MQuaternion<float>* rot)
{
    this->rotation = rot;
}

MQuaternion<float>* md5joint::getRotation()
{
    return this->rotation;
}

void md5joint::setInverseBindPose(MTransform<float>* inverseBindPose)
{
    this->inverseBindPose = inverseBindPose;
}

void md5joint::setGlobalTransform(MTransform<float>* globalTransform)
{
    this->globalTransform = globalTransform;
}

void md5joint::setLocalTransform(MTransform<float>* localTransform)
{
    this->localTransform = localTransform;
}

MTransform<float> * md5joint::getInverseBindPose()
{
    return this->inverseBindPose;
}

MTransform<float> * md5joint::getGlobalTransform()
{
    return this->globalTransform;
}

MTransform<float> * md5joint::getLocalTransform()
{
    return this->localTransform;
}


md5joint::~md5joint()
{
    delete position;
    delete rotation;
}
