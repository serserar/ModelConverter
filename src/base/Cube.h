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

#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"

/**
 * @todo write docs
 */
class Cube :  public Mesh
{
public:
    /**
     * Default constructor
     */
    Cube();
    
    /**
     * Default constructor
     */
    Cube(float width, float height, float depth, MVector3<float> center);

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Cube(const Cube& other);

    /**
     * Destructor
     */
    ~Cube();
    
    void initMeshData();
    virtual void ApplyTransform(MTransform<float>& transform);
    virtual void ApplyTransforms();
private:
    float width;
    float height;
    float depth;
    MVector3<float> center;
};

#endif // CUBE_H
