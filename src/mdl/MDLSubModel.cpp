/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#include <memory>

#include "MDLSubModel.h"

MDLSubModel::MDLSubModel()
{
}

MDLSubModel::MDLSubModel(const MDLSubModel& other)
{

}

MDLSubModel::~MDLSubModel()
{

}

void MDLSubModel::addMDLMesh(MDLMesh* mesh) {
    meshList.push_back(mesh);
}

MDLMesh* MDLSubModel::getMDLMesh(int index) {
    MDLMesh* mesh = nullptr;
    if(meshList.size() > index){
        mesh = meshList.at(index);
    }
    return mesh;
}

MDLMesh * MDLSubModel::getMDLMeshArray()
{
    return meshList[0];
}


void MDLSubModel::Fill(MDLMesh* meshArray, int size) {
    for(int i = 0; i < size; i++){
        meshList.push_back(&meshArray[i]);
    }
    //meshList.assign(size, meshArray);
}

string MDLSubModel::GetName() {
    return this->name;
}

void MDLSubModel::SetName(string name) {
    this->name = name;
}

float MDLSubModel::GetBoundingRadiusIndex() {
    return this->boundingRadius;
}

void MDLSubModel::SetBoundingRadius(float boundingRadius) {
    this->boundingRadius = boundingRadius;
}

int MDLSubModel::GetSize()
{
    return this->meshList.size();
}


