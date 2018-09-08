/*
 * Copyright 2017 <copyright holder> <email>
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

#include "BBox.h"
#include <GL/glew.h>

BBox::BBox()
{

}

BBox::BBox(MVector3<float> boundMin, MVector3<float> boundMax)
{
    this->boundMin = boundMin;
    this->boundMax = boundMax;
}


BBox::BBox(const BBox& other)
{
    this->boundMin = other.boundMin;
    this->boundMax = other.boundMax;
}

BBox::~BBox()
{

}

bool BBox::Contains(BBox& other)
{
    return this->boundMin.GetX() <= other.boundMin.GetX() &&
           this->boundMin.GetY() <= other.boundMin.GetY() &&
           this->boundMin.GetZ() <= other.boundMin.GetZ() &&
           this->boundMax.GetX() >= other.boundMax.GetX() &&
           this->boundMax.GetY() >= other.boundMax.GetY() &&
           this->boundMax.GetZ() >= other.boundMax.GetZ();
}

bool BBox::Contains(MVector3<float>& vec)
{
    return  vec.GetX() >= this->boundMin.GetX() &&
            vec.GetY() >= this->boundMin.GetY() &&
            vec.GetZ() >= this->boundMin.GetZ() &&
            vec.GetX() <= this->boundMax.GetX() &&
            vec.GetY() <= this->boundMax.GetY() &&
            vec.GetZ() <= this->boundMax.GetZ();
}

bool BBox::Contains(float x, float y, float z)
{
    return  x >= this->boundMin.GetX() &&
            y >= this->boundMin.GetY() &&
            z >= this->boundMin.GetZ() &&
            x <= this->boundMax.GetZ() &&
            y <= this->boundMax.GetZ() &&
            z <= this->boundMax.GetZ();
}

bool BBox::Intersects(MVector3<float>& orig, MVector3<float>& dir)
{
    MVector3<float> ray = orig+dir;
    float tmin = (boundMin.GetX() - orig.GetX()) / dir.GetX();
    float tmax = (boundMax.GetX() - orig.GetX()) / dir.GetX();

    if (tmin > tmax) {
        float tmintmp = tmin;
        tmin = tmax;
        tmax = tmintmp;
    }

    float tymin = (boundMin.GetY() - orig.GetY()) / dir.GetY();
    float tymax = (boundMax.GetY() - orig.GetY()) / dir.GetY();

    if (tymin > tymax) {
        float tymintmp = tymin;
        tymin = tymax;
        tymax = tymintmp;
    }

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (boundMin.GetZ() - orig.GetZ()) / dir.GetZ();
    float tzmax = (boundMax.GetZ() - orig.GetZ()) / dir.GetZ();

    if (tzmin > tzmax) {
        float tzmintmp = tzmin;
        tzmin = tzmax;
        tzmax = tzmintmp;
    }

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}


BBox* BBox::OcTreeSubDivision()
{
    MVector3<float> half = this->boundMax - this->boundMin;
    half/=2;
    MVector3<float> center = this->boundMin + half;
    MVector3<float> o0min=this->boundMin;
    MVector3<float> o0max=center;
    MVector3<float> o1min(center.GetX(),o0min.GetY(), o0min.GetZ());
    MVector3<float> o1max(this->boundMax.GetX(),center.GetY(), center.GetZ());
    MVector3<float> o2min(o0min.GetX(),o0min.GetY(), center.GetZ());
    MVector3<float> o2max(center.GetX(),center.GetY(), this->boundMax.GetZ());
    MVector3<float> o3min(center.GetX(), o1min.GetY(), center.GetZ());
    MVector3<float> o3max(this->boundMax.GetX(),center.GetY(), this->boundMax.GetZ());
    MVector3<float> o4min(this->boundMin.GetX(), center.GetY(), this->boundMin.GetZ());
    MVector3<float> o4max(center.GetX(), this->boundMax.GetY(), center.GetZ());
    MVector3<float> o5min(center.GetX(), center.GetY(), this->boundMin.GetZ());
    MVector3<float> o5max(this->boundMax.GetX(), this->boundMax.GetY(), center.GetZ());
    MVector3<float> o6min(this->boundMin.GetX(), center.GetY(), center.GetZ());
    MVector3<float> o6max(center.GetX(), this->boundMax.GetY(), this->boundMax.GetZ());
    MVector3<float> o7min=center;
    MVector3<float> o7max=this->boundMax;
    BBox* octant= new BBox[8] { BBox(o0min, o0max), BBox(o1min, o1max), BBox(o2min, o2max), BBox(o3min, o3max),
                                BBox(o4min, o4max), BBox(o5min, o5max), BBox(o6min, o6max), BBox(o7min, o7max)
                              };
    return octant;
}

BBox BBox::GetBBoxFromTriangle(Triangle& triangle)
{
    BBox bbox;
    float xmin, ymin,zmin, xmax, ymax, zmax;
    xmin=triangle.v1.GetX();
    if(triangle.v2.GetX()< xmin) {
        xmin = triangle.v2.GetX();
    }
    if(triangle.v3.GetX()< xmin) {
        xmin = triangle.v3.GetX();
    }
    ymin=triangle.v1.GetY();
    if(triangle.v2.GetY()< ymin) {
        ymin = triangle.v2.GetY();
    }
    if(triangle.v3.GetY()< ymin) {
        ymin = triangle.v3.GetY();
    }
    zmin=triangle.v1.GetZ();
    if(triangle.v2.GetZ()< zmin) {
        zmin = triangle.v2.GetZ();
    }
    if(triangle.v3.GetZ()< zmin) {
        zmin = triangle.v3.GetZ();
    }
    bbox.boundMin.SetX(xmin);
    bbox.boundMin.SetY(ymin);
    bbox.boundMin.SetZ(zmin);
    xmax=triangle.v1.GetX();
    if(triangle.v2.GetX()> xmax) {
        xmax = triangle.v2.GetX();
    }
    ymax=triangle.v1.GetY();
    if(triangle.v2.GetY()> ymax) {
        ymax = triangle.v2.GetY();
    }
    zmax=triangle.v1.GetZ();
    if(triangle.v2.GetZ()> zmax) {
        zmax = triangle.v2.GetZ();
    }
    bbox.boundMax.SetX(xmax);
    bbox.boundMax.SetY(ymax);
    bbox.boundMax.SetZ(zmax);
    return bbox;
}

float BBox::GetWidth()
{
    return boundMax.GetX()-boundMin.GetX();
}

float BBox::GetHeight()
{
    return boundMax.GetY()-boundMin.GetY();
}

float BBox::GetDepth()
{
    return boundMax.GetZ()-boundMin.GetZ();
}

MVector3<float> BBox::GetCenter()
{
    MVector3<float> boxcenter = boundMin;
    boxcenter+=boundMax;
    boxcenter*=0.5f;
    return boxcenter;
}

MVector3<float> BBox::GetHalfSize()
{
    MVector3<float> halfSize;

    halfSize.SetX(fabs(boundMax.GetX() - boundMin.GetX()) * 0.5f);
    halfSize.SetY(fabs(boundMax.GetY() - boundMin.GetY()) * 0.5f);
    halfSize.SetZ(fabs(boundMax.GetZ() - boundMin.GetZ()) * 0.5f);

    return halfSize;
}

int BBox::ClassifyPlane(MPlane<float>& plane)
{
    int result=0;
    //inspect the normal and compute the minimun and maximun D values
    float mind, maxd;
    MVector3<float> normal = plane.GetNormal();
    if(normal.GetX() > 0.0f) {
        mind = normal.GetX()*boundMin.GetX();
        maxd = normal.GetX()*boundMax.GetX();
    } else {
        mind = normal.GetX()*boundMax.GetX();
        maxd = normal.GetX()*boundMin.GetX();
    }
    if(normal.GetY() > 0.0f) {
        mind += normal.GetY()*boundMin.GetY();
        maxd += normal.GetY()*boundMax.GetY();
    } else {
        mind += normal.GetY()*boundMax.GetY();
        maxd += normal.GetY()*boundMin.GetY();
    }
    if(normal.GetZ() > 0.0f) {
        mind += normal.GetZ()*boundMin.GetZ();
        maxd += normal.GetZ()*boundMax.GetZ();
    } else {
        mind += normal.GetZ()*boundMax.GetZ();
        maxd += normal.GetZ()*boundMin.GetZ();
    }
    //Check if completely on the front side of the plane
    float d = plane.GetDistance().magnitude();
    if(mind >= d) {
        result = 1;
    }
    if(maxd <= d) {
        result = -1;
    }
    return result;
}
