/*
 * Copyright 2018 <copyright holder> <email>
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
 */

#include "Cube.h"

Cube::Cube()
{

}

Cube::Cube(float width, float height, float depth, MVector3<float> center)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    this->center = center;
    initMeshData();
}


Cube::Cube(const Cube& other)
{
    this->width = other.width;
    this->height = other.height;
    this->depth = other.depth;
    this->center = other.center;
    initMeshData();
}

Cube::~Cube()
{

}

void Cube::initMeshData()
{
    MVector3<float> v0 ( center.GetX()-width/2, center.GetY()-height/2, center.GetZ()-depth/2 );//left-bottom-back
    MVector3<float> v1 ( center.GetX()+width/2, center.GetY()-height/2, center.GetZ()-depth/2 );//right-bottom-back
    MVector3<float> v2 ( center.GetX()-width/2, center.GetY()+height/2, center.GetZ()-depth/2 );//left-top-back
    MVector3<float> v3 ( center.GetX()-width/2, center.GetY()-height/2, center.GetZ()+depth/2 );//left-bottom-front

    //max face
    MVector3<float> v4 ( center.GetX()+width/2, center.GetY()+height/2, center.GetZ()-depth/2 );//right-top-back
    MVector3<float> v5 ( center.GetX()+width/2, center.GetY()-height/2, center.GetZ()+depth/2 );//right-bottom-front
    MVector3<float> v6 ( center.GetX()-width/2, center.GetY()+height/2, center.GetZ()+depth/2 );//left-top-front
    MVector3<float> v7 ( center.GetX()+width/2, center.GetY()+height/2, center.GetZ()+depth/2 );//right-top-front
    std::cout <<  " center : " << center  << " width : " << v7.GetX()-v6.GetX() << " height : " << v2.GetY()-v0.GetY() << " deepth : " << v3.GetZ()-v2.GetZ() << endl;
    //0-left-bottom-back
    vertexCoords.push_back(v0.GetX());
    vertexCoords.push_back(v0.GetY());
    vertexCoords.push_back(v0.GetZ());
    //1-right-bottom-back
    vertexCoords.push_back(v1.GetX());
    vertexCoords.push_back(v1.GetY());
    vertexCoords.push_back(v1.GetZ());
    //2-left-top-back
    vertexCoords.push_back(v2.GetX());
    vertexCoords.push_back(v2.GetY());
    vertexCoords.push_back(v2.GetZ());
    //3-left-bottom-front
    vertexCoords.push_back(v3.GetX());
    vertexCoords.push_back(v3.GetY());
    vertexCoords.push_back(v3.GetZ());
    //4-right-top-back
    vertexCoords.push_back(v4.GetX());
    vertexCoords.push_back(v4.GetY());
    vertexCoords.push_back(v4.GetZ());
    //5-right-bottom-front
    vertexCoords.push_back(v5.GetX());
    vertexCoords.push_back(v5.GetY());
    vertexCoords.push_back(v5.GetZ());
    //6-left-top-front
    vertexCoords.push_back(v6.GetX());
    vertexCoords.push_back(v6.GetY());
    vertexCoords.push_back(v6.GetZ());
    //7-right-top-front
    vertexCoords.push_back(v7.GetX());
    vertexCoords.push_back(v7.GetY());
    vertexCoords.push_back(v7.GetZ());

    int index=0, index1=1, index2=2, index3=3, index4=4, index5=5, index6=6, index7=7;
    //back face
    indexBuffer.push_back(index);
    indexBuffer.push_back(index1);
    indexBuffer.push_back(index4);
    indexBuffer.push_back(index4);
    indexBuffer.push_back(index2);
    indexBuffer.push_back(index);
    //left face
    indexBuffer.push_back(index);
    indexBuffer.push_back(index2);
    indexBuffer.push_back(index6);
    indexBuffer.push_back(index6);
    indexBuffer.push_back(index3);
    indexBuffer.push_back(index);
    //bottom face
    indexBuffer.push_back(index);
    indexBuffer.push_back(index3);
    indexBuffer.push_back(index5);
    indexBuffer.push_back(index5);
    indexBuffer.push_back(index1);
    indexBuffer.push_back(index);
    //right face
    indexBuffer.push_back(index1);
    indexBuffer.push_back(index4);
    indexBuffer.push_back(index7);
    indexBuffer.push_back(index7);
    indexBuffer.push_back(index5);
    indexBuffer.push_back(index1);
    //front face
    indexBuffer.push_back(index5);
    indexBuffer.push_back(index7);
    indexBuffer.push_back(index6);
    indexBuffer.push_back(index6);
    indexBuffer.push_back(index3);
    indexBuffer.push_back(index5);
    //top face
    indexBuffer.push_back(index2);
    indexBuffer.push_back(index6);
    indexBuffer.push_back(index7);
    indexBuffer.push_back(index7);
    indexBuffer.push_back(index4);
    indexBuffer.push_back(index2);
    
    indexSections[0]=indexBuffer;
    indexModeBuffer.push_back(Mesh::Triangles);
    indexLenghts.push_back(12);
    UpdateTriangleList();
    computeBBox();
}


void Cube::ApplyTransform(MTransform<float>& transform)
{
    Mesh::ApplyTransform(transform);
}

void Cube::ApplyTransforms()
{   
    Mesh::ApplyTransforms();
}
