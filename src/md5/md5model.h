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


#ifndef MD5MODEL_H
#define MD5MODEL_H
#include <vector>
#include <map>
#include "md5joint.h"
#include "md5mesh.h"
#include "md5animation.h"
#include "../math/MTransform.h"


class md5model
{

public:
    md5model();
    virtual ~md5model();
    string getName();
    void setName(string name);
    int getVersion();
    void setVersion(int version);
    int getNumJoints();
    void setNumJoints(int numJoints);
    int getNumMeshes();
    void setNumMeshes(int numMeshes);
    vector<md5joint*> getSkeleton();
    void setSkeleton(vector<md5joint*> skeleton);
    vector<md5mesh*> getMeshes();
    void setMeshes(vector<md5mesh*> meshes);
    vector<md5animation*> getAnimations();
    void setAnimations(vector<md5animation*> animations);
    vector<MVector3<float>*> getVertexFinalPosition(int mesh);
    int* getVertexIndex(int nummesh);
private:
    string name;
    int version;
    int numJoints;
    int numMeshes;
    vector<md5joint*> skeleton;
    vector<md5mesh*> meshes;
    vector<md5animation*> animations;
};

#endif // MD5MODEL_H
