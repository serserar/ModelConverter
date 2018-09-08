/* 
 * File:   MDLBodyParts.h
 * Author: serserar
 *
 * Created on February 21, 2016, 2:11 AM
 */

#ifndef MDLBODYPARTS_H
#define	MDLBODYPARTS_H
#include <string>
#include <vector>
#include "MDLSubModel.h"

using namespace std;

class MDLBodyParts {
public:
    MDLBodyParts();
    MDLBodyParts(const MDLBodyParts& orig);
    virtual ~MDLBodyParts();
    void AddMDLSubModel(MDLSubModel* subModel);
    MDLSubModel* GetMDLSubModel(int index);
    MDLSubModel* GetMDLSubModelArray();
    void Fill(MDLSubModel* modelsArray, int size);
    void SetName(string name);
    string GetName();
    int GetSize();
private:
    string name;
    vector<MDLSubModel*> subModelList;
};

#endif	/* MDLBODYPARTS_H */

