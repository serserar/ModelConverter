/* 
 * File:   MDLConverter.h
 * Author: serserar
 *
 * Created on February 21, 2016, 1:53 AM
 */

#ifndef MDLIMPORTER_H
#define	MDLIMPORTER_H

#include "Model.h"
#include "../mdl/MDLModel.h"

class MDLImporter {
public:
    MDLImporter();
    virtual ~MDLImporter();
    AnimatedModel* Convert(MDLModel& mdlmodel);
    void buildModelSkeleton(Skeleton& skeleton, MDLSkeleton& mdlSkeleton);
    void buildModelMeshArray(vector<SkinnedMesh*>& meshList, MDLBodyParts* mdlbodyparts, int size);
    void buildMesh(SkinnedMesh& mesh, vertexinfo_s* mdlverteArray, int size);
    Animation* buildAnimation(MDLAnimation& animation);
    AnimationFrame* buildAnimationFrame(MDLSkeleton& mdlskeleton, int nframe);
//     md5animbaseframe* buildMD5BaseFrame(vector<md5joint*>& joints);
//     md5animjointlocation* buildmd5animjointlocation(md5joint& joint);
    MTransform<float>* getBindTransform(MVector3<float>& translation, MVector3<float>& rot);
    string space2underscore(string text);
private:

};

#endif	/* MDLIMPORTER_H */

