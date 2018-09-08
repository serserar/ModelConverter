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

#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(const Animation& other)
{
    this->name=other.name;
    this->nframes=other.nframes;
    this->fps=other.fps;
    for(auto animationFrame : other.frames){
        frames.push_back(new AnimationFrame(*animationFrame));
    }
}

Animation::~Animation()
{
    for(auto animationFrame : frames){
        delete animationFrame;
    }
}

Animation& Animation::operator=(const Animation& other)
{
    //delete current animations
    for(auto animationFrame : frames){
        delete animationFrame;
    }
    frames.clear();
    this->name=other.name;
    this->nframes=other.nframes;
    this->fps=other.fps;
    for(auto animationFrame : other.frames){
        frames.push_back(new AnimationFrame(*animationFrame));
    }
    return *this;
}

string Animation::GetName()
{
    return this->name;
}

void Animation::SetName(string name)
{
    this->name = name;
}

float Animation::GetFrameRate()
{
    return this->fps;
}

void Animation::SetFrameRate(float fps)
{
    this->fps = fps;
}

int Animation::GetFrameSize()
{
    return this->nframes;
}

void Animation::SetFrameSize(int nframes)
{
    this->nframes = nframes;
}

void Animation::addAnimationFrame(AnimationFrame* animationFrame)
{
    this->frames.push_back(animationFrame);
}

AnimationFrame * Animation::GetAnimationFrame(int frame)
{
    AnimationFrame * animFrame = nullptr;
    if(frame < frames.size()){
        animFrame = frames.at(frame);
    }
    return animFrame;
}
