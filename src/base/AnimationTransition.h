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

#ifndef ANIMATIONTRANSITION_H
#define ANIMATIONTRANSITION_H

#include "../util/Fsm.h"

/**
 * @todo write docs
 */
class AnimationTransition :  Transition
{
public:
    /**
     * Default constructor
     */
    AnimationTransition();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    AnimationTransition(const AnimationTransition& other);

    /**
     * Destructor
     */
    ~AnimationTransition();

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual State* GetState() ;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual bool checkTriggered();
private:
    State* state;
};

#endif // ANIMATIONTRANSITION_H
