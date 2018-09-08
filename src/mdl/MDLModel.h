/* 
 * File:   MDLModel.h
 * Author: serserar
 *
 * Created on February 21, 2016, 2:05 AM
 */

#ifndef MDLMODEL_H
#define	MDLMODEL_H
#include <vector>
#include "MDLBodyParts.h"
#include "MDLAnimation.h"
#include "MDLSkeleton.h"

using namespace std;

class MDLModel {
public:
    MDLModel();
    MDLModel(const MDLModel& orig);
    virtual ~MDLModel();
    void SetName(string name);
    string GetName();
    void SetSkeleton(MDLSkeleton* nskeleton);
    MDLSkeleton* GetSkeleton();
    void AddMDLBodyPart(MDLBodyParts* bodyPart);
    MDLBodyParts* GetMDLBodyPart(int index);
    MDLBodyParts* GetMDLBodyPartArray();
    int GetBodyPartSize();
    void FillBodyParts(MDLBodyParts* bodyPartsArray, int size);
    void AddMDLAnimation(MDLAnimation* animation);
    MDLAnimation* GetMDLAnimation(int index);
    MDLAnimation* GetMDLAnimationArray();
    int GetAnimationSize();
    void FillAnimation(MDLAnimation* animationsArray, int size);
private:
    string name;
    MDLSkeleton* skeleton;
    vector<MDLBodyParts*> bodyParts;
    vector<MDLAnimation*> animations;
};

#endif	/* MDLMODEL_H */

