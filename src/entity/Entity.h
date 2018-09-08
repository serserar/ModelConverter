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

#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>    
#include <vector>
#include "EntityStatus.h"
#include "../util/Fsm.h"
#include "../base/Model.h"
/**
 * @todo write docs
 */
class Entity
{
public:
    /**
     * Default constructor
     */
    Entity();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Entity(const Entity& other);

    /**
     * Destructor
     */
    ~Entity();
    
    void RegisterAction(Action* action);
    
    
    virtual void OnUpdate(double dt);
    
    void OnActionEvent(Event& event);
    size_t GetId();
    EntityStatus* GetStatus();
protected:
    EntityStatus* status;
    Fsm fsm;
    size_t id;
    Model* model;
};

#endif // ENTITY_H
