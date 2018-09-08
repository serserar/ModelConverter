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

#include "Ray.h"

Ray::Ray()
{

}

Ray::Ray(MVector3<float> origin, MVector3<float> direction)
{
    this->direction=direction;
    this->origin=origin;
}

Ray::Ray(const Ray& other)
{
    this->direction=other.direction;
    this->origin=other.origin;
}


bool Ray::operator==(const Ray& rhs) const
{
    return origin == rhs.origin && direction == rhs.direction;
}

MVector3<float> Ray::GetOrigin()
{
    return this->origin;
}

void Ray::SetOrigin(MVector3<float> origin)
{
    this->origin = origin;
}


MVector3<float> Ray::GetDirection() 
{
    return this->direction;
}

void Ray::SetDirection(MVector3<float> direction)
{
    this->direction=direction;
}
