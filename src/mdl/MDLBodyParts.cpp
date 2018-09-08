/* 
 * File:   MDLBodyParts.cpp
 * Author: serserar
 * 
 * Created on February 21, 2016, 2:11 AM
 */

#include "MDLBodyParts.h"

MDLBodyParts::MDLBodyParts() {
}

MDLBodyParts::MDLBodyParts(const MDLBodyParts& orig) {
}

MDLBodyParts::~MDLBodyParts() {
}

void MDLBodyParts::AddMDLSubModel(MDLSubModel* subModel) {
    this->subModelList.push_back(subModel);
}

MDLSubModel* MDLBodyParts::GetMDLSubModel(int index) {
    MDLSubModel* submodel = nullptr;
    if(subModelList.size() > index){
        submodel = subModelList.at(index);
    }
    return submodel;
}

MDLSubModel* MDLBodyParts::GetMDLSubModelArray()
{
    return subModelList[0];
}


void MDLBodyParts::Fill(MDLSubModel* modelsArray, int size) {
    for(int i = 0; i < size; i++){
        subModelList.push_back(&modelsArray[i]);
    }
}

string MDLBodyParts::GetName() {
    return this->name;
}

void MDLBodyParts::SetName(string name) {
    this->name = name;
}

int MDLBodyParts::GetSize()
{
    return this->subModelList.size();
}
