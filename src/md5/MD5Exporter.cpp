/*
 * Copyright 2017 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "MD5Exporter.h"

MD5Exporter::MD5Exporter()
{

}

MD5Exporter::MD5Exporter(const MD5Exporter& other)
{

}

MD5Exporter::~MD5Exporter()
{

}

md5model* MD5Exporter::Convert(AnimatedModel& model, Options& options) {
    md5model* cmodel = new md5model();
    cmodel->setVersion(10);
    cmodel->setName("model.md5mesh");
    cmodel->setNumJoints(model.GetSkeleton()->GetJointSize());
    std::vector<md5joint*> skeleton;
    buildMD5Skeleton(skeleton, *model.GetSkeleton());
    cmodel->setSkeleton(skeleton);
    vector<md5mesh*> meshes;
    for(auto it = model.GetBeginMeshIterator(); it != model.GetEndMeshIterator();++it){
        meshes.push_back(buildMD5Mesh(**it, options.GetMaterialPath()));
    }
    cmodel->setNumMeshes(meshes.size());
    cmodel->setMeshes(meshes);
    //if(model.GetAnimationSize() > 0){
    if(false){
        vector<md5animation*> animations;
        buildMD5Animations(animations, model.GetAnimationArray(), model.GetAnimationSize());
        cmodel->setAnimations(animations);
    }
    return cmodel;
}

void MD5Exporter::buildMD5Skeleton(vector<md5joint *>& skeleton, Skeleton& mskeleton)
{
    md5joint* mjoint = nullptr;
    Joint* joint = nullptr;
    md5joint* parentjoint = nullptr;
    MTransform<float>* transform = nullptr;
    MTransform<float>* rootTransform = nullptr;
    for(int i = 0; i < mskeleton.GetJointSize();i++){
        joint = mskeleton.GetJoint(i);
        mjoint = new md5joint(space2underscore(joint->GetName()));
        mjoint->setParent(joint->GetParent());
        MVector3<float>* translation = new MVector3<float>(joint->GetPosition()->GetX(),
                                                            joint->GetPosition()->GetY(),
                                                            joint->GetPosition()->GetZ());
        mjoint->setPosition(translation);  
        MQuaternion<float>* q = new MQuaternion<float>(*joint->GetRotation());
        q->normalize();
        if(q->getW() > 0){
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

MTransform<float>* MD5Exporter::getBindTransform(MVector3<float>& translation, MVector3<float>& rot)
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
MMatrix3<float>* MD5Exporter::buildMatrix(MVector3<float>& rot) {
        MMatrix3<float> m1;
        MMatrix3<float> m2;
        MMatrix3<float> m3;
        MVector3<float> unitx(1.0f, 0.0f, 0.0f);
        MVector3<float> unity(0.0f, 1.0f, 0.0f);
        MVector3<float> unitz(0.0f, 0.0f, 1.0f);
        m1.fromAngleAxis(rot.GetX(), unitx);
        m2.fromAngleAxis(rot.GetY(), unity);
        m3.fromAngleAxis(rot.GetZ(), unitz);
        MMatrix3<float>* result = m3 * *(m2 * m1);
        return result;
    }


md5mesh* MD5Exporter::buildMD5Mesh(SkinnedMesh& mesh, string materialPath)
{
    md5mesh* mmesh = new md5mesh();
    buildMD5Vertex(mmesh->vertexList, mmesh->weightList, mesh);
    buildMD5Triangles(mmesh->triangleList, mesh);
    mmesh->numverts = mmesh->vertexList.size();
    mmesh->numtris = mmesh->triangleList.size();
    mmesh->numweights = mmesh->weightList.size();
    mmesh->shader = materialPath + mesh.GetTextureName();
    return mmesh;                          
}

void MD5Exporter::buildMD5Vertex(vector<md5vertex*>& vertexList, vector<md5weight*>& weightList, SkinnedMesh& mesh)
{
    int uvIndex = 0; 
    int vertexIndex = 0;
    for(int i = 0; i < mesh.vertexCoords.size(); i+=3){
        md5weight* weight = new md5weight();
        weight->weightIndex = weightList.size();
        weight->bias = 1.0;
        weight->joint = mesh.jointIndices.at(vertexIndex);
        weight->pos = new MVector3<float>(mesh.vertexCoords.at(i), mesh.vertexCoords.at(i+1), mesh.vertexCoords.at(i+2));
        weightList.push_back(weight);
        md5vertex* vertex = new md5vertex();
        vertex->verIndex = vertexIndex;
        vertex->startWeight = weight->weightIndex;
        vertex->countWeight = 1;
        vertex->uv = new double[2];
        vertex->uv[0] = mesh.textureCoords.at(0).at(uvIndex);
        vertex->uv[1] = mesh.textureCoords.at(0).at(uvIndex+1);
        uvIndex +=2;
        vertexIndex ++;
        vertexList.push_back(vertex);
    }
}

void MD5Exporter::buildMD5Triangles(vector<md5triangle*>& triangleList,  SkinnedMesh& mesh)
{
    //recover triangles from mesh
    mesh.UpdatePrimitiveCounts();
    vector<Triangle> triangles;
    mesh.GetTrianglesIndex(triangles);
    md5triangle* mtriangle = nullptr;
    int triangleIndex = 0;
    for(int i = 0;i < triangles.size();i++){
        mtriangle = new md5triangle();
        mtriangle->triIndex = triangleIndex;
        mtriangle->vertIndex[0]= triangles[i].vindex1;
        mtriangle->vertIndex[1]= triangles[i].vindex2;
        mtriangle->vertIndex[2]= triangles[i].vindex3;
        triangleList.push_back(mtriangle);
        triangleIndex++;
    }    
}

void MD5Exporter::buildMD5Animations(vector<md5animation *>& animationList,  Animation* animations, int size)
{
    md5animation* md5anim = nullptr;
    for(int i = 0; i < size; i++){
        md5anim = new md5animation();
        md5anim->setAnimationName(animations[i].GetName());
        md5anim->setFrameRate(animations[i].GetFrameRate());
        md5anim->setNumFrames(animations[i].GetFrameSize());
        vector<md5joint*> joints;
        buildMD5Skeleton(joints, *animations[i].GetAnimationFrame(0)->GetSkeleton());
        std::vector<md5animjoint* >jointList;
        md5anim->setJoints(jointList);
        for(int j = 0; j < animations[i].GetFrameSize();j++){
            if(j == 0){
                md5anim->setBaseFrame(buildMD5BaseFrame(joints));    
            }
            //set frames
            md5animframe frame;
        }
        animationList.push_back(md5anim);
    }
}

md5animbaseframe* MD5Exporter::buildMD5BaseFrame(vector<md5joint*>& joints)
{
    md5animbaseframe* md5BaseAnimation = new md5animbaseframe();
    vector<md5animjointlocation*> jointLocations;
    int jointsize = joints.size();
    for(int i = 0; i < jointsize; i++){
        jointLocations.push_back(buildmd5animjointlocation(*joints.at(i)));
    }
    md5BaseAnimation->setJointLocations(jointLocations);
    return md5BaseAnimation;
}

md5animjointlocation * MD5Exporter::buildmd5animjointlocation(md5joint& joint)
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



string MD5Exporter::space2underscore(string text) {
    for(string::iterator it = text.begin(); it != text.end(); ++it) {
        if(*it == ' ') {
            *it = '_';
        }
    }
    return text;
}

