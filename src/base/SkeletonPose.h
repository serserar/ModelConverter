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

#ifndef SKELETONPOSE_H
#define SKELETONPOSE_H
#include "Skeleton.h"
#include "../math/mmatrix4.h"
#include <vector>

using namespace std;

template <class Real>
class SkeletonPose
{
public:
    SkeletonPose(Skeleton& skeleton);
    SkeletonPose(SkeletonPose& skeletonPose);
    ~SkeletonPose();
    Skeleton skeleton;
    vector<MTransform<Real>*> localtransforms;//Local transforms for the joints of the associated skeleton
    vector<MTransform<Real>*> globaltransforms;//Global transforms for the joints of the associated skeleton
    vector<MMatrix4<Real>*> matrixpalette;//global space transforms for each of the skeleton's joints
    void SetBindPose();
private:
    void initialize();
};

template <class Real>
SkeletonPose<Real>::SkeletonPose(Skeleton& skeleton)
{
    this->skeleton = skeleton;
    initialize();
}
/** Update our local joint transforms so that they reflect the skeleton in **/
template <class Real>
void SkeletonPose<Real>::SetBindPose()
{
    localtransforms.clear();
    globaltransforms.clear();
    localtransforms.resize(skeleton.joints.size());
    globaltransforms.resize(skeleton.joints.size());
    Joint* joint = nullptr;
    for(int i = 0; i < skeleton.joints.size();i++){
        joint = skeleton.joints.at(i);
        localtransforms[i] = joint->GetLocalTransform();
        globaltransforms[i] = joint->GetGlobalTransform();
        matrixpalette[i] = globaltransforms[i]->ToMatrix4x4(*matrixpalette.at(i));
    }
}


template<class Real> 
void SkeletonPose<Real>::initialize()
{
    for(int i = 0; i < skeleton.joints.size();i++){
        matrixpalette.push_back(new MMatrix4<Real>());
    }
}

template<class Real> 
SkeletonPose<Real>::~SkeletonPose()
{
    for(auto mpalette : matrixpalette){
        delete mpalette;
    }
}



#endif // SKELETONPOSE_H
