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

#ifndef SHOOTEVENT_H
#define SHOOTEVENT_H
#include "../event/Event.h"
/**
 * @todo write docs
 */
class ShootEvent : Event
{
public:
    /**
     * Default constructor
     */
    ShootEvent();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    ShootEvent(const ShootEvent& other);

    /**
     * Destructor
     */
    ~ShootEvent();
    
    

};

#endif // SHOOTEVENT_H
