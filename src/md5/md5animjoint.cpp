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


#include "md5animjoint.h"

md5animjoint::md5animjoint()
{

}

md5animjoint::~md5animjoint()
{

}

string md5animjoint::getJointName()
{
    return this->jointName;
}

void md5animjoint::setJointName(string jointName)
{
    this->jointName = jointName;
}

int md5animjoint::getParent()
{
    return this->parent;
}

void md5animjoint::setParent(int parent)
{
    this->parent = parent;
}

int md5animjoint::getFlags()
{
    return this->flags;
}

void md5animjoint::setFlags(int flags)
{
    this->flags = flags;
}

int md5animjoint::getStartIndex()
{
    return this->startIndex;
}

void md5animjoint::setStartIndex(int startIndex)
{
    this->startIndex = startIndex;
}
