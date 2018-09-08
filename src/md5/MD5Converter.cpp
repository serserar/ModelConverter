/*
 * File:   MD5Converter.cpp
 * Author: serserar
 *
 * Created on February 21, 2016, 1:53 AM
 */

#include "MD5Converter.h"


MD5Converter::MD5Converter() {
}

MD5Converter::MD5Converter(const MD5Converter& orig) {
}

MD5Converter::~MD5Converter() {
}

md5model* MD5Converter::Convert(MDLModel& mdlmodel) {
    md5model* cmodel = new md5model();
    cmodel->setVersion(10);
    cmodel->setName("model.md5mesh");
    cmodel->setNumJoints(mdlmodel.GetSkeleton()->GetJointSize());
    std::vector<md5joint*> skeleton;
    buildMD5Skeleton(skeleton, *mdlmodel.GetSkeleton());
    cmodel->setSkeleton(skeleton);
    vector<md5mesh*> meshes;
    buildMD5MeshArray(meshes, mdlmodel.GetMDLBodyPartArray(), mdlmodel.GetBodyPartSize());
    cmodel->setNumMeshes(meshes.size());
    cmodel->setMeshes(meshes);
    vector<md5animation*> animations;
    buildMD5Animations(animations, mdlmodel.GetMDLAnimationArray(), mdlmodel.GetAnimationSize());
    cmodel->setAnimations(animations);
    return cmodel;
}

void MD5Converter::buildMD5Skeleton(vector<md5joint *>& skeleton, MDLSkeleton& mdlSkeleton)
{
    md5joint* mjoint = nullptr;
    MDLJoint* mdljoint = nullptr;
    md5joint* parentjoint = nullptr;
    MTransform<float>* transform = nullptr;
    MTransform<float>* rootTransform = nullptr;
    for(int i = 0; i < mdlSkeleton.GetJointSize(); i++) {
        mdljoint = mdlSkeleton.GetMDLJoint(i);
        mjoint = new md5joint(space2underscore(mdljoint->GetName()));
        mjoint->setParent(mdljoint->GetParent());
        MVector3<float>* translation = new MVector3<float>(mdljoint->GetTranslation().GetX(),
                mdljoint->GetTranslation().GetY(),
                mdljoint->GetTranslation().GetZ());
        MVector3<float> rot(mdljoint->GetRotation().GetX(),
                            mdljoint->GetRotation().GetY(),
                            mdljoint->GetRotation().GetZ());
        transform = getBindTransform(*translation, rot);
        mjoint->setInverseBindPose(transform);
        if(mjoint->getParent() != -1) {
            MTransform<float>* applyTransform  = new MTransform<float>(false);
            if (mjoint->getParent() == 0) {
                rootTransform->multiply(*transform, *applyTransform);
                mjoint->setInverseBindPose(applyTransform->invert(*new MTransform<float>(false)));
                mjoint->setGlobalTransform(applyTransform);
            } else {
                parentjoint = skeleton.at(mjoint->getParent());
                //std::cout << "parent joint : " << parentjoint->getName() << endl;
                //std::cout << "joint : " << mjoint->getName() << endl;
                MTransform<float>* parentTransform = parentjoint->getInverseBindPose()->invert(
                        *new MTransform<float>(false));
                parentTransform->multiply(*transform, *applyTransform);
                mjoint->setInverseBindPose(applyTransform->invert(*new MTransform<float>(false)));
                mjoint->setGlobalTransform(applyTransform);
                //cout << *mjoint->getInverseBindPose() << endl;
            }
            //delete applyTransform;
        } else { //root joint
            rootTransform = transform;
            mjoint->setGlobalTransform(rootTransform);
            mjoint->setInverseBindPose(rootTransform->invert(*new MTransform<float>(false)));
        }
        //mjoint->setPosition(mjoint->getInverseBindPose()->invert(*new MTransform<float>(false))->translation);
        mjoint->setPosition(new MVector3(mjoint->getGlobalTransform()->translation));
        MQuaternion<float>* q = new MQuaternion<float>();
        //q->FromRotationMatrix(*mjoint->getInverseBindPose()->invert(*new MTransform<float>(false))->matrix);
        q->FromRotationMatrix(mjoint->getGlobalTransform()->matrix);
        q->normalize();
        if(q->getW() > 0) {
            q->negate();
        }
        //q->FromAxisAngle(rot);
        mjoint->setRotation(q);
        cout << mjoint->getName() << endl;
        cout << *q << endl;
        cout << q->length() << endl;
        skeleton.push_back(mjoint);
    }
}

MTransform<float>* MD5Converter::getBindTransform(MVector3<float>& translation, MVector3<float>& rot)
{
    MTransform<float>* btransform = new MTransform<float>(false);
    btransform->translation.Set(translation);
    MMatrix3<float>* rMat = buildMatrix(rot);
    btransform->matrix.Set(*rMat);
    delete rMat;
    return btransform;
}


/**
* Method that creates rotation Matrix3f from Vector3f with axis rotation.
* @param rot : Vector3f with axis rotation.
* @return Matrix3f : builded rotation Matrix3f.
*/
MMatrix3<float>* MD5Converter::buildMatrix(MVector3<float>& rot) {
    MMatrix3<float> m1;
    MMatrix3<float> m2;
    MMatrix3<float> m3;
    MVector3<float> unitx(1.0f, 0.0f, 0.0f);
    MVector3<float> unity(0.0f, 1.0f, 0.0f);
    MVector3<float> unitz(0.0f, 0.0f, 1.0f);
    m1.fromAngleAxis(rot.GetX(), unitx);
    m2.fromAngleAxis(rot.GetY(), unity);
    m3.fromAngleAxis(rot.GetZ(), unitz);
    MMatrix3<float>* result = m3 **(m2 * m1);
    return result;
}


void MD5Converter::buildMD5MeshArray(vector<md5mesh*>& meshList, MDLBodyParts* mdlbodyparts, int size)
{
    md5mesh* mesh = nullptr;
    for(int i = 0; i < size; i++) {
        int submodels = mdlbodyparts[i].GetSize();
        if(submodels > 0) {
            MDLSubModel* subModelsArray = mdlbodyparts[i].GetMDLSubModelArray();
            for(int j = 0; j < submodels; j++) {
                int meshes = subModelsArray[j].GetSize();
                if(meshes > 0) {
                    MDLMesh* meshArray = subModelsArray[j].getMDLMeshArray();
                    for(int m = 0; m <meshes; m++) {
                        mesh = new md5mesh();
                        int nvertex = meshArray[m].GetSize();
                        if(nvertex > 0) {
                            for(int v = 0; v < nvertex; v++) {
                                buildMD5Vertex(mesh->vertexList,
                                               mesh->weightList,
                                               *meshArray[m].getMDLVertex(v));
                            }
                            int ntriangles = meshArray[m].GetTriangleListSize();//recover set of triangles
                            int triangleIndex = 0;
                            for(int t = 0; t < ntriangles; t++) {
                                buildMD5Triangles(mesh->triangleList, *meshArray[m].GetTriangle(t), triangleIndex);
                            }
                            mesh->numverts = mesh->vertexList.size();
                            mesh->numtris = mesh->triangleList.size();
                            mesh->numweights = mesh->weightList.size();
                            meshList.push_back(mesh);
                        }
                    }
                }
            }
        }
    }
}

void MD5Converter::buildMD5Vertex(vector<md5vertex*>& vertexList, vector<md5weight*>& weightList,
                                  vertexinfo_s& mdlvertex)
{
    md5weight* weight = new md5weight();
    weight->weightIndex = weightList.size();
    weight->bias = 1.0;
    weight->joint = mdlvertex.bone;
    weight->pos = new MVector3<float>(mdlvertex.vertex.x, mdlvertex.vertex.y, mdlvertex.vertex.z);
    weightList.push_back(weight);
    md5vertex* vertex = new md5vertex();
    vertex->verIndex = mdlvertex.index;
    vertex->startWeight = weight->weightIndex;
    vertex->countWeight = 1;
    vertex->uv = new double[2];
    vertex->uv[0] = mdlvertex.ucoord;
    vertex->uv[1] = mdlvertex.vcoord;
    vertexList.push_back(vertex);
}

void MD5Converter::buildMD5Triangles(vector<md5triangle*>& triangleList, Triangles<vertexinfo_s*>& triangles,
                                     int& triangleIndex)
{
    int degenerates = 0;
    if(triangles.type == triangles.TRIANGLE_STRIP) {
        md5triangle* mtriangle = nullptr;
        for (int v= 0; v < triangles.vertexList.size()-2; v++) {
            mtriangle = new md5triangle();
            mtriangle->triIndex = triangleIndex;
            if (v & 1) {
                mtriangle->vertIndex[0]= triangles.vertexList.at(v+1)->index;
                mtriangle->vertIndex[1]= triangles.vertexList.at(v)->index;
                mtriangle->vertIndex[2]= triangles.vertexList.at(v+2)->index;

            } else {
                mtriangle->vertIndex[0]= triangles.vertexList.at(v)->index;
                mtriangle->vertIndex[1]= triangles.vertexList.at(v+1)->index;
                mtriangle->vertIndex[2]= triangles.vertexList.at(v+2)->index;
            }
            if(mtriangle->vertIndex[0] ==  mtriangle->vertIndex[1] || mtriangle->vertIndex[0] ==  mtriangle->vertIndex[2] ||mtriangle->vertIndex[1] ==  mtriangle->vertIndex[2]) {
                degenerates++;
            }
            triangleList.push_back(mtriangle);
            triangleIndex++;
        }
        //TriangleUtil<vertexinfo_s*,md5triangle* >::toTriangles(triangles,triangleList);
    } else if(triangles.type == triangles.TRIANGLE_FAN) {
        md5triangle* mtriangle = nullptr;
        for (int v= 0; v < triangles.vertexList.size()-2; v++) {
            mtriangle = new md5triangle();
            mtriangle->triIndex = triangleIndex;
            mtriangle->vertIndex[0]= triangles.vertexList.at(0)->index;
            mtriangle->vertIndex[1]= triangles.vertexList.at(v+1)->index;
            mtriangle->vertIndex[2]= triangles.vertexList.at(v+2)->index;
            if(mtriangle->vertIndex[0] ==  mtriangle->vertIndex[1] || mtriangle->vertIndex[0] ==  mtriangle->vertIndex[2] ||mtriangle->vertIndex[1] ==  mtriangle->vertIndex[2]) {
                degenerates++;
            }
            triangleList.push_back(mtriangle);
            triangleIndex++;
        }
    }
}

void MD5Converter::buildMD5Animations(vector<md5animation *>& animationList,  MDLAnimation* animations, int size)
{
    md5animation* md5anim = nullptr;
    for(int i = 0; i < size; i++) {
        md5anim = new md5animation();
        md5anim->setAnimationName(animations[i].GetName());
        md5anim->setFrameRate(animations[i].Getfps());
        md5anim->setNumFrames(animations[i].GetFrameSize());
        vector<md5joint*> joints;
        MDLSkeleton& skeleton = *animations[i].GetSkeleton(0);
        buildMD5Skeleton(joints, skeleton);
        std::vector<md5animjoint* >jointList;
        md5anim->setJoints(jointList);
        for(int j = 0; j < animations[i].GetFrameSize(); j++) {
            if(j == 0) {
                md5anim->setBaseFrame(buildMD5BaseFrame(joints));
            }
            //set frames
            md5animframe frame;
        }
        animationList.push_back(md5anim);
    }
}

md5animbaseframe* MD5Converter::buildMD5BaseFrame(vector<md5joint*>& joints)
{
    md5animbaseframe* md5BaseAnimation = new md5animbaseframe();
    vector<md5animjointlocation*> jointLocations;
    int jointsize = joints.size();
    for(int i = 0; i < jointsize; i++) {
        jointLocations.push_back(buildmd5animjointlocation(*joints.at(i)));
    }
    md5BaseAnimation->setJointLocations(jointLocations);
    return md5BaseAnimation;
}

md5animjointlocation * MD5Converter::buildmd5animjointlocation(md5joint& joint)
{
    md5animjointlocation * md5animjoint = new md5animjointlocation();
    md5animjoint->setJointIndex(0);
    MVector3<float>* t = new MVector3<float>(*joint.getPosition());
    md5animjoint->setPosition(t);
    MQuaternion<float>* q = new MQuaternion<float>(*joint.getRotation());
    md5animjoint->setRotation(q);
    md5animjoint->setJointIndex(joint.getParent());
    return md5animjoint;
}



string MD5Converter::space2underscore(string text) {
    for(string::iterator it = text.begin(); it != text.end(); ++it) {
        if(*it == ' ') {
            *it = '_';
        }
    }
    return text;
}

