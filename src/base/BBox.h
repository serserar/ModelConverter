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

#ifndef BBOX_H
#define BBOX_H
#include "Triangle.h"
#include "../math/MVector3.h"
#include "../math/MPlane.h"

class BBox
{
public:
    BBox();
    BBox(MVector3<float> boundMin, MVector3<float> boundMax);
    BBox(const BBox& other);
    ~BBox();
    MVector3<float> boundMin;
    MVector3<float> boundMax;
    bool Contains(BBox& other);
    bool Contains(MVector3<float>& vec);
    bool Contains(float x, float y, float z);
    bool Intersects(MVector3<float>& orig, MVector3<float>& dir);
    BBox* OcTreeSubDivision();
    static BBox GetBBoxFromTriangle(Triangle& triangle);
    float GetWidth();
    float GetHeight();
    float GetDepth();
    MVector3<float> GetCenter();
    MVector3<float> GetHalfSize();
    int ClassifyPlane(MPlane<float>& plane);
private:
inline friend std::ostream& operator <<(std::ostream& o, const BBox& box) {
        o << "[bmin=" << box.boundMin << "]" << "[bmax=" << box.boundMax << "]";
        return o;
    }    
};

#endif // BBOX_H
