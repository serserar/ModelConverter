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

#include "EntityAction.h"
using namespace std;

EntityAction::EntityAction()
{
    this->running = false;
    this->finalized = false;

}

EntityAction::EntityAction(const EntityAction& other)
{

}

EntityAction::~EntityAction()
{

}

bool EntityAction::IsFinalized()
{

}

bool EntityAction::CanInterrupt()
{

}

bool EntityAction::OnUpdate(float dt)
{
//check jumping /play animation
}

std::string EntityAction::GetName()
{
    return this->actionName;
}

void EntityAction::SetName(std::string actionName)
{
    this->actionName = actionName;
}

void EntityAction::Execute()
{
//can jump  ?
//change entity status
    // this->dynamicEntity->
//play animation
    cout << "Jumping"<< endl;
}
