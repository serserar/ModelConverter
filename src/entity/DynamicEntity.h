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

#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H
#include "Entity.h"

/**
 * @todo write docs
 */
class DynamicEntity : public Entity
{
public:
    /**
     * Default constructor
     */
    DynamicEntity();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    DynamicEntity(const DynamicEntity& other);

    /**
     * Destructor
     */
    ~DynamicEntity();
    
    void OnUpdate(double dt) override;
    
protected:
    
    

};

#endif // DYNAMICENTITY_H
