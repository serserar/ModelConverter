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

#ifndef RAY_H
#define RAY_H
#include "../math/MVector3.h"
/**
 * @todo write docs
 */
class Ray
{
public:
    /**
     * Default constructor
     */
    Ray();
    Ray(MVector3<float> origin, MVector3<float> direction);

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Ray(const Ray& other);

    /**
     * Destructor
     */
    ~Ray()=default;

    bool operator== (const Ray &rhs) const;

    MVector3<float> GetOrigin();
    void SetOrigin(MVector3<float> origin);
    MVector3<float> GetDirection();
    void SetDirection(MVector3<float> direction);
private:
    MVector3<float> origin;
    MVector3<float> direction;
};

#endif // RAY_H
