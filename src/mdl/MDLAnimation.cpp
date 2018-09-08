/* 
 * File:   MDLAnimation.cpp
 * Author: serserar
 * 
 * Created on February 21, 2016, 2:12 AM
 */

#include "MDLAnimation.h"

MDLAnimation::MDLAnimation() {
}

MDLAnimation::MDLAnimation(const MDLAnimation& orig) {
}

MDLAnimation::~MDLAnimation() {
    for(auto it = skeletonList.begin(); it != skeletonList.end(); ++it){
        delete *it;
    }
}

string MDLAnimation::GetName() {
    return this->name;
}

void MDLAnimation::SetName(string name) {
    this->name = name;
}


void MDLAnimation::AddSkeleton(MDLSkeleton* skeleton) {
    this->skeletonList.push_back(skeleton);
}

MDLSkeleton* MDLAnimation::GetSkeleton(int index) {
    MDLSkeleton* skeleton = nullptr;
    if (skeletonList.size() > index) {
        skeleton = skeletonList.at(index);
    }
    return skeleton;
}

void MDLAnimation::FillSkeletons(MDLSkeleton* skeletonArray, int size) {
    for(int i = 0; i < size; i++){
        skeletonList.push_back(&skeletonArray[i]);
    }
    //skeletonList.assign(size, skeletonArray);
}

MDLSkeleton* MDLAnimation::GetSkeletonArray() {
    return skeletonList[0];
}


int MDLAnimation::GetFrameSize() {
    return skeletonList.size();
}

float MDLAnimation::Getfps()
{
    return this->fps;
}

void MDLAnimation::Setfps(float fps)
{
    this->fps = fps;
}
