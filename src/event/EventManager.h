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

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <map>
#include "EventListener.h"

/**
 * @todo write docs
 */
class EventManager
{
public:
    
    static EventManager* GetInstance();
    /**
     * Destructor
     */
    ~EventManager();
    void RegisterEventListener(EventType eventType, EventListener* eventListener);
    void SendEvent(Event& event);
private:
    /**
     * Default constructor
     */
    EventManager();
    static EventManager* instance;
    std::map<EventType, EventListener*> listenerMap;
};

#endif // EVENTMANAGER_H
