/* 
 * File:   MDLJoint.cpp
 * Author: serserar
 * 
 * Created on February 21, 2016, 2:13 AM
 */

#include "MDLJoint.h"

MDLJoint::MDLJoint() {
}

MDLJoint::MDLJoint(const MDLJoint& orig) {
}

MDLJoint::~MDLJoint() {
}

void MDLJoint::SetName(string name) {
    this->name = name;
}

string MDLJoint::GetName() {
    return this->name;
}

int MDLJoint::GetParent()
{
    return this->parent;
}

void MDLJoint::SetParent(int parent)
{
    this->parent = parent;
}

int MDLJoint::GetId()
{
    return this->id;
}

void MDLJoint::SetId(int id)
{
    this->id = id;
}


MVector3<float> MDLJoint::GetTranslation() {
    return this->trans;
}

void MDLJoint::SetTranslation(float x, float y, float z) {
    this->trans.set(x, y, z);
}

MVector3<float> MDLJoint::GetRotation() {
    return this->rot;
}

void MDLJoint::SetRotation(float x, float y, float z) {
    this->rot.set(x, y, z);
}



