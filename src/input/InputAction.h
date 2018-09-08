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

#ifndef ENTITYACTION_H
#define ENTITYACTION_H

#include "../event/Action.h"
#include <iostream>
/**
 * @todo write docs
 */
class InputAction :  public Action
{
public:
    /**
     * Default constructor
     */
    InputAction();

    /**
     * Destructor
     */
    ~InputAction();

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual bool IsFinalized();

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual bool CanInterrupt();

    /**
     * @todo write docs
     *
     * @param dt TODO
     * @return TODO
     */
    virtual bool OnUpdate(float dt);

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual std::string GetName();

    /**
     * @todo write docs
     *
     * @param  TODO
     * @return TODO
     */
    virtual void SetName(std::string actionName);

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual void Execute();
    
    
protected:
    bool running;
    bool finalized;
    std::string actionName;
};

#endif // JUMPACTION_H
