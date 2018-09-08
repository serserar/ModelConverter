/* 
 * File:   MDLModel.cpp
 * Author: serserar
 * 
 * Created on February 21, 2016, 2:05 AM
 */

#include "MDLModel.h"

MDLModel::MDLModel() {
    this->skeleton = nullptr;
}

MDLModel::MDLModel(const MDLModel& orig) {
}

MDLModel::~MDLModel() {
    delete skeleton;
}

string MDLModel::GetName() {
    return this->name;
}

void MDLModel::SetName(string name) {
    this->name = name;
}

MDLSkeleton* MDLModel::GetSkeleton() {
    return this->skeleton;
}

void MDLModel::SetSkeleton(MDLSkeleton* nskeleton) {
    if(this->skeleton)delete this->skeleton;
    this->skeleton = nskeleton;
}

void MDLModel::AddMDLBodyPart(MDLBodyParts* bodyPart) {
    bodyParts.push_back(bodyPart);
}

MDLBodyParts* MDLModel::GetMDLBodyPart(int index) {
    MDLBodyParts* bodyPart = nullptr;
    if (bodyParts.size() > index) {
        bodyPart = bodyParts.at(index);
    }
    return bodyPart;
}

MDLBodyParts * MDLModel::GetMDLBodyPartArray()
{
    return bodyParts[0];
}

int MDLModel::GetBodyPartSize()
{
    return bodyParts.size();
}


void MDLModel::FillBodyParts(MDLBodyParts* bodyPartsArray, int size) {
    for(int i = 0; i < size; i++){
        bodyParts.push_back(&bodyPartsArray[i]);
    }
    //bodyParts.assign(size, bodyPartsArray);
}

void MDLModel::AddMDLAnimation(MDLAnimation* animation) {
    animations.push_back(animation);
}

MDLAnimation* MDLModel::GetMDLAnimation(int index) {
    MDLAnimation* animation = nullptr;
    if (index < animations.size()) {
        animation = animations.at(index);
    }
    return animation;
}

MDLAnimation * MDLModel::GetMDLAnimationArray()
{
    return animations[0];
}

int MDLModel::GetAnimationSize()
{
    return animations.size();
}

void MDLModel::FillAnimation(MDLAnimation* animationsArray, int size) {
    for(int i = 0; i < size; i++){
        animations.push_back(&animationsArray[i]);
    }
}
