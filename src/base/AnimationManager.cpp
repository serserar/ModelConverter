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

#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
 this->last_time = 0.0;
 this->max_time = 1.0;
 this->currentnFrame = 0;
 this->maxFrame = 0;
 this->needsloadFrame = false;
}

AnimationManager::AnimationManager(const AnimationManager& other)
{

}

AnimationManager::~AnimationManager()
{

}

void AnimationManager::update(double dt)
{
      // Animate only if there is an animation...
  if (currentAnimation)
    {
    last_time += dt;

      // Move to next frame?
       if (last_time >= max_time)
 	{
// 	  _nextFrame++;
      this->last_time = 0.0f;
// 
// 	  unsigned int maxFrame = currentAnimation->maxFrame ();
// 
 	  if (this->currentnFrame >= maxFrame-1){
 	     this->currentnFrame = 0;
      }else{
          this->currentnFrame++;
          this->needsloadFrame=true;
      }
// 
// 	  if (_nextFrame > maxFrame)
// 	    _nextFrame = 0;
 	}
    }
}

void AnimationManager::addAnimation(Animation* animation)
{
    this->animationMap.insert( std::pair<string,Animation*>(animation->GetName(),animation) );
}


void AnimationManager::SetAnimation(string animationName)
{
    auto it = this->animationMap.find(animationName);
    if (it != animationMap.end()){
        currentAnimation = it->second;
        this->max_time =  1.0 / static_cast<double>(currentAnimation->GetFrameRate());
        this->last_time = 0.0;
        this->currentnFrame = 0;
        this->maxFrame = currentAnimation->GetFrameSize();
    }
}

AnimationFrame * AnimationManager::GetFrame()
{
    AnimationFrame * currentFrame = nullptr;
    if(this->currentAnimation){
        currentFrame = currentAnimation->GetAnimationFrame(currentnFrame);
    }else{
        currentFrame = currentAnimation->GetAnimationFrame(currentnFrame);
    }
    return currentFrame;
}

