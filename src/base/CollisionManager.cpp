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

#include "CollisionManager.h"

using namespace std;

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}


bool CollisionManager::RayIntersectsTriangle(MVector3<float>& rayOrigin, MVector3<float>& rayDest, Triangle& triangle, MVector3<float>& intersectionPoint)
{
    MVector3<float> vertex0 = triangle.v1;
    MVector3<float> vertex1 = triangle.v2;
    MVector3<float> vertex2 = triangle.v3;
    MVector3<float> edge1, edge2, h, s, q;
//     float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    MVector3<float> normal = edge1.CrossProduct(edge2);
    normal.normalize();
    MPlane<float> plane(normal,vertex0);
    bool intersects = plane.IntersectsRay(rayOrigin, rayDest, intersectionPoint);
    if(intersects) {
        //check barycentric coords
        MVector3<float> bcoords = MeshUtils::GetBaryCentricCoords(triangle, intersectionPoint);
//         // Compute vectors
//         MVector3<float> v2 = intersectionPoint - vertex0;
//         // Compute dot products
//         float dot00 = edge2.dotProduct(edge2);
//         float dot01 = edge2.dotProduct(edge1);
//         float dot02 = edge2.dotProduct(v2);
//         float dot11 = edge1.dotProduct(edge1);
//         float dot12 = edge1.dotProduct(v2);
//
//         // Compute barycentric coordinates
//         float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
//         double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
//         double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

// Check if point is in triangle
        //intersects = (u >= 0) && (v >= 0) && (u + v < 1);
        float u = bcoords.GetX();
        float v = bcoords.GetY();
        float w = bcoords.GetZ();
        intersects = (u >= 0) && (v >= 0) && (u + v <= 1) && (u + v + w == 1);
        if(intersects) {
            MVector3<float> check1 = edge1 * u;
            MVector3<float> check2 = edge2 * v;
            MVector3<float> res = vertex0 + check1 + check2;
            //vertex0 + ((edge1 * u) + (edge2 * v));
            cout << "u : " << u << " v : " << v << " w : " << w << endl;
        }
    }
    return intersects;
}


bool CollisionManager::RayIntersectsMesh(MVector3<float>& rayOrigin, MVector3<float>& rayDest, Mesh& mesh, MVector3<float>& intersectionPoint)
{
    return mesh.intersect(rayOrigin, rayDest, intersectionPoint);
}
