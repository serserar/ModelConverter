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


#include "md5model.h"
#include "iostream"

md5model::md5model()
{

}

string md5model::getName()
{
    return this->name;
}

void md5model::setName(string name)
{
    this->name = name;
}

int md5model::getVersion()
{
    return this->version;
}

void md5model::setVersion(int version)
{
    this->version = version;
}

int md5model::getNumJoints()
{
    return this->numJoints;
}

void md5model::setNumJoints(int numJoints)
{
    this->numJoints = numJoints;
}

int md5model::getNumMeshes()
{
    return this->numMeshes;
}

void md5model::setNumMeshes(int numMeshes)
{
    this->numMeshes = numMeshes;
}

std::vector<md5joint*> md5model::getSkeleton()
{
    return this->skeleton;
}

void md5model::setSkeleton(std::vector<md5joint*> skeleton)
{
    this->skeleton = skeleton;
}

std::vector<md5mesh*> md5model::getMeshes()
{
    return this->meshes;
}

void md5model::setMeshes(std::vector<md5mesh*> meshes)
{
    this->meshes = meshes;
}

std::vector< md5animation* > md5model::getAnimations()
{
    return this->animations;
}

void md5model::setAnimations(std::vector< md5animation* > animations)
{
    this->animations = animations;
}

std::vector<MVector3<float>*> md5model::getVertexFinalPosition(int nummesh)
{
    vector<MVector3<float>*> finalVertexLocation;
    int i, j;
    md5mesh* mesh = this->meshes.at(nummesh);
    md5weight* weight = 0;
    md5joint* joint = 0;
    MVector3<float>* finalVertex;
    /* Setup vertices */
    for (i = 0; i < mesh->numverts; ++i)
    {
        /* Calculate final vertex to draw with weights */
        for (j = 0; j < mesh->vertexList.at(i)->countWeight; ++j)
        {
            weight = mesh->weightList[mesh->vertexList[i]->startWeight + j];
            joint = this->skeleton[weight->joint];
            /* Calculate transformed vertex for this weight */
            //vec3_t wv;
            //Quat_rotatePoint (joint->getRotation(), weight->pos, wv);
            finalVertex = new MVector3<float>(*joint->getRotation()->rotate(*weight->pos));
            finalVertex->operator+=(*joint->getPosition());
            finalVertex->operator*=(weight->bias);
            //finalVertex->operator*(weight->bias);
            /* The sum of all weight->bias should be 1.0 */
            //finalVertex[0] += (joint->pos[0] + wv[0]) * weight->bias;
            //finalVertex[1] += (joint->pos[1] + wv[1]) * weight->bias;
            //finalVertex[2] += (joint->pos[2] + wv[2]) * weight->bias;
        }
        finalVertexLocation.push_back(finalVertex);
        //vertexArray[i][0] = finalVertex[0];
        //vertexArray[i][1] = finalVertex[1];
        //vertexArray[i][2] = finalVertex[2];
    }
    return finalVertexLocation;
}
int* md5model::getVertexIndex(int nummesh)
{
    int i, j, k;
    md5mesh* mesh = this->meshes.at(nummesh);
    int* vertexIndices = new int[mesh->numtris * 3];
    /* Setup vertex indices */
    for (k = 0, i = 0; i < mesh->numtris; ++i)
    {
        for (j = 0; j < 3; ++j, ++k)
            vertexIndices[k] = mesh->triangleList.at(i)->vertIndex[j];
    }
    return vertexIndices;
}


md5model::~md5model()
{

}

