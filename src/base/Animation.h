/*
 * Copyright 2017 <copyright holder> <email>
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
 * 
 */

#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <string>
#include <map>
#include "AnimationFrame.h"

using namespace std;
class Animation
{
public:
    Animation();
    Animation(const Animation& other);
    ~Animation();
    Animation& operator=(const Animation& other);
    string GetName();
    void SetName(string name);
    float GetFrameRate();
    void SetFrameRate(float fps);
    int GetFrameSize();
    void SetFrameSize(int nframes);
    void addAnimationFrame(AnimationFrame* animationFrame);
    AnimationFrame* GetAnimationFrame(int frame);
private:
    string name;
    int nframes;
    float fps;
    vector<AnimationFrame*> frames;
};

#endif // ANIMATION_H
