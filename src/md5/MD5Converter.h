/* 
 * File:   MD5Converter.h
 * Author: serserar
 *
 * Created on February 21, 2016, 1:53 AM
 */

#ifndef MD5CONVERTER_H
#define	MD5CONVERTER_H
#include "md5model.h"
#include "../mdl/MDLModel.h"
#include "../util/TriangleUtil.h"

class MD5Converter {
public:
    MD5Converter();
    MD5Converter(const MD5Converter& orig);
    virtual ~MD5Converter();
    md5model* Convert(MDLModel& mdlmodel);
    void buildMD5Skeleton(std::vector<md5joint*>& skeleton, MDLSkeleton& mdlSkeleton);
    void buildMD5MeshArray(vector<md5mesh*>& meshList, MDLBodyParts* mdlbodyparts, int size);
    void buildMD5Vertex(vector<md5vertex*>& vertexList, vector<md5weight*>&weightList, vertexinfo_s& mdlvertex);
    void buildMD5Triangles(vector<md5triangle*>& triangleList, Triangles<vertexinfo_s*>& triangles, int& triangleIndex);
    void buildMD5Animations(vector<md5animation*>& animationList, MDLAnimation* animations, int size);
    md5animbaseframe* buildMD5BaseFrame(vector<md5joint*>& joints);
    md5animjointlocation* buildmd5animjointlocation(md5joint& joint);
    MTransform<float>* getBindTransform(MVector3<float>& translation, MVector3<float>& rot);
    MMatrix3<float>* buildMatrix(MVector3<float>& rot);
    string space2underscore(string text);
private:

};

#endif	/* MD5CONVERTER_H */

