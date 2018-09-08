/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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


#include "md5animjointlocation.h"

int md5animjointlocation::getJointIndex()
{
    return this->jointIndex;
}

void md5animjointlocation::setJointIndex(int jointIndex)
{
    this->jointIndex = jointIndex;
}

MVector3<float>* md5animjointlocation::getPosition()
{
    return this->position;
}
void md5animjointlocation::setPosition(MVector3<float>* position)
{
    this->position = position;
}
MQuaternion<float>* md5animjointlocation::getRotation()
{
    return this->rotation;
}
void md5animjointlocation::setRotation(MQuaternion<float>* rotation)
{
    this->rotation = rotation;
}
