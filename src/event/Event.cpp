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

#include "Event.h"
using namespace std;

Event::Event(EventType senderType, EventType receiverType, std::string eventName, std::string actionName, size_t entityId)
{
    this->senderType = senderType;
    this->receiverType = receiverType;
    this->eventName = eventName;
    this->actionName = actionName;
    this->entityId = entityId;
}

Event::~Event() { }

void Event::addListener(IEventCallback* action)
{
    auto position = find(actions.begin(), actions.end(), action);
    if (position != actions.end())
    {
        cout <<"Action existed in delegate list." <<endl;
        return;
    }

    actions.push_back(action);
}

void Event::removeListener(IEventCallback* action)
{
    auto position = find(actions.begin(), actions.end(), action);
    if (position == actions.end())
    {
        return;
    }

    actions.erase(position);
}

void Event::fire()
{
    for (IEventCallback* action : actions)
    {
        (*action)();
    }
}

std::string Event::GetEventName()
{
    return this->eventName;
}

EventType Event::GetSenderType()
{
    return this->senderType;
}


EventType Event::GetReceiverType()
{
    return this->receiverType;
}

std::string Event::GetActionName()
{
    return actionName;
}

size_t Event::GetEntityId()
{
    return entityId;
}
