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

#ifndef MDLSUBMODEL_H
#define MDLSUBMODEL_H
#include <string>
#include <vector>
#include "MDLMesh.h"

using namespace std;

class MDLSubModel
{
public:
  MDLSubModel();
  MDLSubModel(const MDLSubModel& other);
  ~MDLSubModel();
  void addMDLMesh(MDLMesh* mesh);
  MDLMesh* getMDLMesh(int index);
  MDLMesh* getMDLMeshArray();
  void Fill(MDLMesh* meshArray, int size);
  void SetName(string name);
  string GetName();
  void SetBoundingRadius(float boundingRadius);
  float GetBoundingRadiusIndex();
  int GetSize();
private :
    string name;
    float boundingRadius;
    vector<MDLMesh*> meshList;
};

#endif // MDLSUBMODEL_H
