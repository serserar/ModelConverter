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

#include "EventManager.h"

EventManager* EventManager::instance=nullptr;

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

EventManager* EventManager::GetInstance()
{
    if(!instance) {
        instance = new EventManager();
    }
    return instance;
}

void EventManager::RegisterEventListener(EventType eventType, EventListener* eventListener)
{
    listenerMap[eventType] = eventListener;
}

void EventManager::SendEvent(Event& event)
{
    //event.GetType
    //Action to execute
    auto it = listenerMap.find(event.GetReceiverType());
    if(it != listenerMap.end()){
        it->second->OnEventReceived(event);
    }
}

