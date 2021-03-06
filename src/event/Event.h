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

#ifndef EVENT_H
#define EVENT_H
#include "EventCallback.h"
#include "EventTypes.h"
#include <iostream>    
#include <algorithm>
#include <vector>
#include <string>
/**
 * @todo write docs
 */
class Event
{
public:
    Event(EventType senderType, 
          EventType receiverType, 
          std::string eventName, 
          std::string actionName, 
          size_t entityId
         );
    ~Event();
    EventType GetSenderType();
    EventType GetReceiverType();
    void addListener(IEventCallback* action);
    void removeListener(IEventCallback* action);
    void fire();
    std::string GetEventName();
    std::string GetActionName();
    size_t GetEntityId();
protected:
    EventType senderType;
    EventType receiverType;
    std::string eventName;
    std::string actionName;
    size_t entityId;
    std::vector<IEventCallback*> actions;
};

#endif // EVENT_H
