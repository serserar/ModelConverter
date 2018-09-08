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

#include "EntityManager.h"
using namespace std;

EntityManager* EntityManager::instance=nullptr;

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
    for(auto it = entityMap.begin(); it != entityMap.end(); it++) {
        delete it->second;
    }
}

EntityManager* EntityManager::GetInstance()
{
    if(!instance) {
        instance = new EntityManager();
    }
    return instance;
}

void EntityManager::OnEventReceived(Event& event)
{
    //check event type
    //this event needs an entity and action with params
    //search and recover entity on map
    //the entity is in running state and receives shoot state from inputmanager
    //execute transition/action
    if(event.GetReceiverType() == EventType::EV_ENTITY) {
        auto actionName = event.GetActionName();
        auto entity = GetEntity(event.GetEntityId());
        if(entity) {
            cout << actionName << endl;
            //entity->
        }
    }
}

Entity* EntityManager::GetEntity(size_t id)
{
    Entity* entity = nullptr;
    auto it = entityMap.find(id);
    if(it != entityMap.end()) {
        entity = it->second;
    }
    return entity;
}

void EntityManager::RegisterEntity(Entity* entity)
{
    entityMap[entity->GetId()]=entity;
}


void EntityManager::DestroyEntity(size_t id)
{
    auto it = entityMap.find(id);
    if(it != entityMap.end()) {
        delete it->second;
        entityMap.erase(id);
    }
}


