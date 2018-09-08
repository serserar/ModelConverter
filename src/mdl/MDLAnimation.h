/* 
 * File:   MDLAnimation.h
 * Author: serserar
 *
 * Created on February 21, 2016, 2:12 AM
 */

#ifndef MDLANIMATION_H
#define	MDLANIMATION_H
#include <string>
#include <vector>
#include "MDLSkeleton.h"
using namespace std;

class MDLAnimation {
public:
    MDLAnimation();
    MDLAnimation(const MDLAnimation& orig);
    virtual ~MDLAnimation();
    string GetName();
    void SetName(string name);
    void AddSkeleton(MDLSkeleton* skeleton);
    MDLSkeleton* GetSkeleton(int index);
    void FillSkeletons(MDLSkeleton* skeletonArray, int size);
    MDLSkeleton* GetSkeletonArray();
    int GetFrameSize();
    float Getfps();
    void Setfps(float fps);
private:
    string name;
    int frames;
    float fps;
    vector<MDLSkeleton*> skeletonList;
};

#endif	/* MDLANIMATION_H */

