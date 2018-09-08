/* 
 * File:   MDLSkeleton.cpp
 * Author: serserar
 * 
 * Created on March 6, 2016, 2:18 PM
 */

#include "MDLSkeleton.h"

MDLSkeleton::MDLSkeleton() {
}

MDLSkeleton::MDLSkeleton(const MDLSkeleton& orig) {
}

MDLSkeleton::~MDLSkeleton() {
}

void MDLSkeleton::AddMDLJoint(MDLJoint* joint) {
    joints.push_back(joint);
}

MDLJoint* MDLSkeleton::GetMDLJoint(int index) {
    MDLJoint* joint = nullptr;
    if (joints.size() > index) {
        joint = joints.at(index);
    }
    return joint;
}

void MDLSkeleton::FillJoints(MDLJoint* jointsArray, int size) {
    for(int i = 0; i < size; i++){
        joints.push_back(&jointsArray[i]);
    }
    //joints.assign(size, jointsArray);
}

MDLJoint* MDLSkeleton::GetJointArray() {
    return joints[0];
}

int MDLSkeleton::GetJointSize() {
    return joints.size();
}
