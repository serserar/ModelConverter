/* 
 * File:   MDLSkeleton.h
 * Author: serserar
 *
 * Created on March 6, 2016, 2:18 PM
 */

#ifndef MDLSKELETON_H
#define	MDLSKELETON_H
#include <vector>
#include "MDLJoint.h"
using namespace std;

class MDLSkeleton {
public:
    MDLSkeleton();
    MDLSkeleton(const MDLSkeleton& orig);
    virtual ~MDLSkeleton();
    void AddMDLJoint(MDLJoint* joint);
    MDLJoint* GetMDLJoint(int index);
    void FillJoints(MDLJoint* jointsArray, int size);
    MDLJoint* GetJointArray();
    int GetJointSize();
private:
    vector<MDLJoint*> joints;
};

#endif	/* MDLSKELETON_H */

