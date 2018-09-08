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

#ifndef ENTITYSTATUS_H
#define ENTITYSTATUS_H
#include "EntityShape.h"
/**
 * @todo write docs
 */
class EntityStatus
{
public:
    /**
     * Default constructor
     */
    EntityStatus();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    EntityStatus(const EntityStatus& other);

    /**
     * Destructor
     */
    ~EntityStatus();
    
    EntityShape* GetShape();
    
protected:
    std::string statusName;
    EntityShape* shape;
    MVector3<float> position;
};

#endif // ENTITYSTATUS_H
