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

#ifndef ACTION_H
#define ACTION_H
#include <string>
/**
 * @todo write docs
 */
class Action{
public:
    virtual ~Action(){};
    virtual void Execute()=0;
    virtual void SetName(std::string actionName)=0;
    virtual std::string GetName()=0;
    virtual bool OnUpdate(float dt)=0;
    virtual bool CanInterrupt()=0;
    virtual bool IsFinalized()=0;
};

#endif // ACTION_H
