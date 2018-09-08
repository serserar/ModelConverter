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

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <map>
#include <iostream>
#include "Entity.h"
#include "../event/EventListener.h"
/**
 * @todo write docs
 */
class EntityManager : public EventListener
{
public:
    static EntityManager* GetInstance();
    void OnEventReceived(Event& event)override;
    Entity* GetEntity(size_t id);
    void RegisterEntity(Entity* entity);
    void DestroyEntity(size_t id);
    /**
     * Destructor
     */
    ~EntityManager();
private :
    /**
     * Default constructor
     */
    EntityManager();
    
    static EntityManager* instance;
    std::map<size_t, Entity*> entityMap;
};

#endif // ENTITYMANAGER_H
