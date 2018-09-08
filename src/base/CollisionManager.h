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

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "../math/MVector3.h"
#include "Triangle.h"
#include "../math/MPlane.h"
#include "MeshUtils.h"

/**
 * @todo write docs
 */
class CollisionManager
{
public:
    /**
     * Default constructor
     */
    CollisionManager();

    /**
     * Destructor
     */
    ~CollisionManager();

    static bool RayIntersectsTriangle(MVector3<float>& rayOrigin, MVector3<float>& rayDest, Triangle& triangle, MVector3<float>& intersectionPoint);
    static bool RayIntersectsMesh(MVector3<float>& rayOrigin, MVector3<float>& rayDest, Mesh& mesh, MVector3<float>& intersectionPoint);
};

#endif // COLLISIONMANAGER_H
