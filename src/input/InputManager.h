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

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "../event/Event.h"
#include "../event/EventManager.h"
#include <iostream>
#include <map>
/**
 * @todo write docs
 */
class InputManager
{
public:
    /**
     * Default constructor
     */
    InputManager();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    InputManager(const InputManager& other);

    /**
     * Destructor
     */
    ~InputManager();
    void registerEvent(Event* event);
    void fireEvent(const std::string& eventName);
    Event* GetEvent(const std::string& eventName);
private:
    std::map<std::string, Event*> eventMap;
};

#endif // INPUTMANAGER_H
