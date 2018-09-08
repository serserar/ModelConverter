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

#include "RectangularPrism.h"

RectangularPrism::RectangularPrism()
{

}

RectangularPrism::RectangularPrism(MVector3<float> pointFront, MVector3<float> pointBack, float size)
{
    this->pointFront = pointFront;
    this->pointBack = pointBack;
    this->size = size;
    initMeshData();
}


RectangularPrism::RectangularPrism(const RectangularPrism& other)
{
    this->pointFront = other.pointFront;
    this->pointBack = other.pointBack;
    this->size = other.size;
    initMeshData();
}

RectangularPrism::~RectangularPrism()
{

}

void RectangularPrism::initMeshData()
{
    MVector3<float> normal ( pointBack.GetX()-pointFront.GetX(),
                             pointBack.GetY()-pointFront.GetY(),
                             pointBack.GetZ()-pointFront.GetZ());
    MVector3<float> w;//u=(0,0,0)
    if ( Math<float>::Abs(normal.GetX()) <= Math<float>::Abs(normal.GetY()) ) {
        if ( Math<float>::Abs(normal.GetX()) <= Math<float>::Abs(normal.GetZ()) ) { //x is minor
            w.SetX(1);
        } else {//z is minor
            w.SetZ(1);
        }
    } else {//y is minor ?
        if(Math<float>::Abs(normal.GetY()) <= Math<float>::Abs(normal.GetZ())) { //y is minor
            w.SetY(1);
        } else { //z is minor
            w.SetZ(1);
        }
    }
    normal.normalize();
    MVector3<float> u = normal.CrossProduct(w);
    MVector3<float> v = normal.CrossProduct(u);
    u*=size;
    v*=size;
    //MVector3<float> v0 ( pointBack.GetX()-u.GetX(), pointBack.GetY()-v.GetY(), pointBack.GetZ());//left-bottom-back
//     MVector3<float> v1 ( pointBack.GetX()+u.GetX(), pointBack.GetY()-v.GetY(), pointBack.GetZ());//right-bottom-back
//     MVector3<float> v2 ( pointBack.GetX()-u.GetX(), pointBack.GetY()+v.GetY(), pointBack.GetZ());//left-top-back
//     MVector3<float> v3 ( pointFront.GetX()-u.GetX(), pointFront.GetY()-v.GetY(), pointFront.GetZ());//left-bottom-front
//
//     //max face
//     MVector3<float> v4 ( pointBack.GetX()+u.GetX(), pointBack.GetY()+v.GetY(), pointBack.GetZ() );//right-top-back
//     MVector3<float> v5 ( pointFront.GetX()+u.GetX(), pointFront.GetY()-v.GetY(), pointFront.GetZ() );//right-bottom-front
//     MVector3<float> v6 ( pointFront.GetX()-u.GetX(), pointFront.GetY()+v.GetY(), pointFront.GetZ() );//left-top-front
//     MVector3<float> v7 ( pointFront.GetX()+u.GetX(), pointFront.GetY()+v.GetY(), pointFront.GetZ() );//right-top-front
    MVector3<float> v0 = pointBack -u-v;//left-bottom-back
    MVector3<float> v1 = pointBack +u-v;//right-bottom-back
    MVector3<float> v2 = pointBack -u+v;//left-top-back
    MVector3<float> v3 = pointFront -u-v;//left-bottom-front

    //max face
    MVector3<float> v4 = pointBack +u+v;//right-top-back
    MVector3<float> v5 = pointFront +u-v;//right-bottom-front
    MVector3<float> v6 = pointFront -u+v;//left-top-front
    MVector3<float> v7 = pointFront +u+v;//right-top-front


    std::cout <<  " normal : " << normal << endl;
    std::cout <<  " u : " << u << endl;
    std::cout <<  " v : " << v << endl;
    std::cout <<  " pointFront : " << pointFront << " left-bottom-front : " << v3 << " right-bottom-front : " << v5 << " left-top-front : " << v6 << " right-top-front : " << v7 << endl;
    std::cout <<  " pointBack : " << pointBack  <<  " left-bottom-back : " << v0 << " right-bottom-back : " << v1 << " left-top-back : " << v2 << " right-top-back : " << v4 << endl;
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
}
