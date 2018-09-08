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

#include "JumpAction.h"

JumpAction::JumpAction()
{

}

JumpAction::JumpAction(const JumpAction& other)
{

}

JumpAction::~JumpAction()
{

}

JumpAction::JumpAction()
{

}

JumpAction::JumpAction(const EntityAction& other)
{

}

bool JumpAction::IsFinalized()
{

}

bool JumpAction::CanInterrupt()
{

}

bool JumpAction::OnUpdate(float dt)
{

}

std::string JumpAction::GetName()
{

}

void JumpAction::SetName(std::string actionName)
{

}

void JumpAction::Execute()
{   
    this->dynamicEntity->SetStatus("jump");
}

