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

#include "InputManager.h"
using namespace std;

InputManager::InputManager()
{

}

InputManager::InputManager(const InputManager& other)
{

}

InputManager::~InputManager()
{

}

void InputManager::fireEvent(const std::string& eventName)
{
    Event* event = nullptr;
    auto it = eventMap.find(eventName);
    if(it != eventMap.end()){
        event = it->second;
        EventManager::GetInstance()->SendEvent(*event);
    }
    
}


Event* InputManager::GetEvent(const std::string& eventName)
{
    return eventMap[eventName];
}

void InputManager::registerEvent(Event* event)
{
     if (eventMap.count(event->GetEventName()) > 1)
    {
        std::cout << "There is no action named " + event->GetEventName() << std::endl;
        return;
    }
    eventMap[event->GetEventName()] = event;
}

