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

#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include "Animation.h"

class AnimationManager
{
public:
    AnimationManager();
    AnimationManager(const AnimationManager& other);
    ~AnimationManager();
    void addAnimation(Animation* animation);
    void update(double dt);
    void SetAnimation(string animationName);
    AnimationFrame* GetFrame();
    bool needsloadFrame;
private:
    map<string, Animation*> animationMap;
    Animation* currentAnimation;
    double last_time;
    double max_time;
    int currentnFrame;
    int maxFrame;
};

#endif // ANIMATIONMANAGER_H
