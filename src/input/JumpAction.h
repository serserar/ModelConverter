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

#ifndef JUMPACTION_H
#define JUMPACTION_H

#include "InputAction.h"

/**
 * @todo write docs
 */
class JumpAction :  public InputAction
{
public:
    /**
     * Default constructor
     */
    JumpAction();

    /**
     * Destructor
     */
    ~JumpAction();

    /**
     * @todo write docs
     *
     * @return TODO
     */
    bool IsFinalized() override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    bool CanInterrupt() override;

    /**
     * @todo write docs
     *
     * @param dt TODO
     * @return TODO
     */
    bool OnUpdate(float dt) override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    std::string GetName() override;

    /**
     * @todo write docs
     *
     * @param actionName TODO
     * @return TODO
     */
    void SetName(std::string actionName) override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    void Execute() override;

};

#endif // JUMPACTION_H
