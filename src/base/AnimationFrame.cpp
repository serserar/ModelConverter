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

#include "AnimationFrame.h"

AnimationFrame::AnimationFrame()
{
  this->skeleton = nullptr;
  this->skeletonPose = nullptr;
}

AnimationFrame::AnimationFrame(const AnimationFrame& other)
{
  this->skeleton = new Skeleton(*other.skeleton);
  this->skeletonPose = new SkeletonPose<float>(*skeleton);
}

AnimationFrame::~AnimationFrame()
{
    delete skeleton;
    delete skeletonPose;
}

void AnimationFrame::SetFrameNumber(int nframe)
{
    this->nframe = nframe;
}

int AnimationFrame::GetFrameNumber()
{
    return this->nframe;
}

void AnimationFrame::SetSkeleton(Skeleton* skeleton)
{
    if(this->skeleton){
        delete this->skeleton;
    }
    this->skeleton = skeleton;
    if(this->skeletonPose){
        delete this->skeletonPose;
    }
    this->skeletonPose = new SkeletonPose<float>(*this->skeleton);
}

Skeleton* AnimationFrame::GetSkeleton()
{
    return this->skeleton;
}

SkeletonPose<float> * AnimationFrame::GetSkeletonPose()
{
    return this->skeletonPose;
}
