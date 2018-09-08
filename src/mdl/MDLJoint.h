/* 
 * File:   MDLJoint.h
 * Author: serserar
 *
 * Created on February 21, 2016, 2:13 AM
 */

#ifndef MDLJOINT_H
#define	MDLJOINT_H
#include <string>
#include "../math/MVector3.h"
#include "../math/mmatrix3.h"

using namespace std;

class MDLJoint {
public:
    MDLJoint();
    MDLJoint(const MDLJoint& orig);
    virtual ~MDLJoint();
    string GetName();
    void SetName(string name);
    int GetParent();
    void SetParent(int parent);
    int GetId();
    void SetId(int id);
    void SetTranslation(float x, float y, float z);
    MVector3<float> GetTranslation();
    void SetRotation(float x, float y, float z);
    MVector3<float> GetRotation();
private:
    string name;
    int parent;
    int id;
    MVector3<float> trans;
    MVector3<float> rot;
};

#endif	/* MDLJOINT_H */

