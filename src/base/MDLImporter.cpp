/* 
 * File:   MD5Converter.cpp
 * Author: serserar
 * 
 * Created on February 21, 2016, 1:53 AM
 */

#include "MDLImporter.h"


MDLImporter::MDLImporter() {
}

MDLImporter::~MDLImporter() {
}

AnimatedModel* MDLImporter::Convert(MDLModel& mdlmodel) {
    AnimatedModel* model = new AnimatedModel();
    model->SetVersion(10);
    model->SetName("model.md5mesh");
    model->SetNumJoints(mdlmodel.GetSkeleton()->GetJointSize());
    Skeleton* skeleton = new Skeleton();
    buildModelSkeleton(*skeleton, *mdlmodel.GetSkeleton());
    model->SetSkeleton(skeleton);
    vector<SkinnedMesh*> meshes;
    buildModelMeshArray(meshes, mdlmodel.GetMDLBodyPartArray(), mdlmodel.GetBodyPartSize());
    model->SetNumMeshes(meshes.size());
    SkeletonPose<float>* pose = new SkeletonPose<float>(*skeleton);
    pose->SetBindPose();
    for(int i = 0;i < meshes.size(); i++){
        meshes[i]->UpdatePrimitiveCounts();
        meshes[i]->UpdateTriangleList();
        model->AddMesh(meshes[i]);
    }
    vector<Animation*> animations;
    for(int i = 0; i < mdlmodel.GetAnimationSize(); i++){
        model->AddAnimation(buildAnimation(*mdlmodel.GetMDLAnimation(i)));
    }
    model->updatePose(*pose);
    return model;
}

void MDLImporter::buildModelSkeleton(Skeleton& skeleton, MDLSkeleton& mdlSkeleton)
{
    Joint* mjoint = nullptr;
    MDLJoint* mdljoint = nullptr;
    Joint* parentjoint = nullptr;
    MTransform<float>* transform = nullptr;
    MTransform<float>* rootTransform = nullptr;
    for(int i = 0; i < mdlSkeleton.GetJointSize();i++){
        mdljoint = mdlSkeleton.GetMDLJoint(i);
        mjoint = new Joint(space2underscore(mdljoint->GetName()));
        mjoint->SetParent(mdljoint->GetParent());
        mjoint->SetIndex(mdljoint->GetId());
        MVector3<float>* translation = new MVector3<float>(mdljoint->GetTranslation().GetX(),
                                                            mdljoint->GetTranslation().GetY(),
                                                            mdljoint->GetTranslation().GetZ());
        MVector3<float> rot(mdljoint->GetRotation().GetX(),
                            mdljoint->GetRotation().GetY(),
                            mdljoint->GetRotation().GetZ());
        transform = getBindTransform(*translation, rot);
        mjoint->SetLocalTransform(transform);
        if(mjoint->GetParent() != -1){
            MTransform<float>* applyTransform  = new MTransform<float>(false);
            if (mjoint->GetParent() == 0) {
                rootTransform->multiply(*transform, *applyTransform);
                mjoint->SetInverseBindPose(applyTransform->invert(*new MTransform<float>(false)));
                mjoint->SetGlobalTransform(applyTransform);
            } else {
                parentjoint = skeleton.joints.at(mjoint->GetParent());
                //std::cout << "parent joint : " << parentjoint->getName() << endl;
                //std::cout << "joint : " << mjoint->getName() << endl;
                MTransform<float>* parentTransform = parentjoint->GetInverseBindPose()->invert(
                    *new MTransform<float>(false));
                parentTransform->multiply(*transform, *applyTransform);
                mjoint->SetInverseBindPose(applyTransform->invert(*new MTransform<float>(false)));
                mjoint->SetGlobalTransform(applyTransform);
                //cout << *mjoint->getInverseBindPose() << endl;
            }
            //delete applyTransform;
        }else{//root joint
            //transform from left handed to right handed
//             MVector3<float> axisrotation(0,0,Math<float>::PI/2);
//             MVector3<float> trans(0,0,19.5);
//             MTransform<float>* changeAxis = MTransform<float>::GetInstance(trans, axisrotation);
//             rootTransform = transform->multiply(*changeAxis, *transform);
            skeleton.parentJoint = mjoint;
            rootTransform = transform;
            mjoint->SetGlobalTransform(rootTransform);
            mjoint->SetInverseBindPose(rootTransform->invert(*new MTransform<float>(false)));
        }
        //mjoint->setPosition(mjoint->getInverseBindPose()->invert(*new MTransform<float>(false))->translation);  
        mjoint->SetPosition(new MVector3<float>(mjoint->GetGlobalTransform()->translation));  
        MQuaternion<float>* q = new MQuaternion<float>();
        //q->FromRotationMatrix(*mjoint->getInverseBindPose()->invert(*new MTransform<float>(false))->matrix);
        q->FromRotationMatrix(mjoint->GetGlobalTransform()->matrix);
        q->normalize();
        if(q->getW() > 0){
            q->negate();
        }
        mjoint->SetRotation(q);
        //cout << mjoint->GetName() << endl;
        //cout << *q << endl;
        //cout << q->length() << endl;
        skeleton.joints.push_back(mjoint);
    }
}

MTransform<float>* MDLImporter::getBindTransform(MVector3<float>& translation, MVector3<float>& rot)
{
    MTransform<float>* btransform = new MTransform<float>(false);
    btransform->translation.Set(translation);
    MMatrix3<float> rMat ;
    rMat = MMatrix3<float>::GetInstance(rot);
    btransform->matrix.Set(rMat);
    return btransform;
}


void MDLImporter::buildModelMeshArray(vector<SkinnedMesh*>& meshList, MDLBodyParts* mdlbodyparts, int size)
{
    SkinnedMesh* mesh = nullptr;
    for(int i = 0; i < size; i++){
        int submodels = mdlbodyparts[i].GetSize();
        if(submodels > 0){
            MDLSubModel* subModelsArray = mdlbodyparts[i].GetMDLSubModelArray();
            for(int j = 0; j < submodels; j++){
                int meshes = subModelsArray[j].GetSize();
                if(meshes > 0){
                    MDLMesh* meshArray = subModelsArray[j].getMDLMeshArray();
                    for(int m = 0; m <meshes; m++){
                        mesh = new SkinnedMesh();
                        int nvertex = meshArray[m].GetSize();
                        if(nvertex > 0){
                            vector<float> uv;
                            mesh->textureCoords.push_back(uv);
                            buildMesh(*mesh, meshArray[m].getMDLVertexArray(), nvertex);
                            
                            if(meshArray[m].GetTexture()){
                                mesh->SetTextureName(meshArray[m].GetTexture()->GetTextureName());
                            }
                            mesh->SetBindPoseMesh(new Mesh(*mesh));
                            meshList.push_back(mesh);
                        }
                    }
                }
            }
        }
    }
}

void MDLImporter::buildMesh(SkinnedMesh& mesh, vertexinfo_s* mdlverteArray, int size)
{
    int section = 0;
    for (int i = 0; i < size; i++){
        mesh.jointIndices.push_back(mdlverteArray[i].bone);//add vertex joint index
        mesh.weightsPerVertex = 1;
        mesh.weights.push_back(1.0);
        if (mdlverteArray[i].triangleTypeIndex == 0) {//starts new section
            if (mdlverteArray[i].triangletype == 0) {
                mesh.indexModeBuffer.push_back(Mesh::TriangleStrip);
            } else if (mdlverteArray[i].triangletype == 1) {
                mesh.indexModeBuffer.push_back(Mesh::TriangleFan);
            }
            if (i != 0) {
                mesh.indexLenghts.push_back(mdlverteArray[i-1].triangleTypeIndex + 1);
                section++;//increments new section
            }
        }
        mesh.indexBuffer.push_back(i);//vertex Index
        mesh.indexSections[section].push_back(i);
        mesh.vertexCoords.push_back(mdlverteArray[i].vertex.x);
        mesh.vertexCoords.push_back(mdlverteArray[i].vertex.y);
        mesh.vertexCoords.push_back(mdlverteArray[i].vertex.z);
        mesh.normalCoords.push_back(mdlverteArray[i].normal.x);
        mesh.normalCoords.push_back(mdlverteArray[i].normal.y);
        mesh.normalCoords.push_back(mdlverteArray[i].normal.z);
        mesh.textureCoords.at(0).push_back(mdlverteArray[i].ucoord);
        mesh.textureCoords.at(0).push_back(mdlverteArray[i].vcoord);
    }
    mesh.indexLenghts.push_back(mdlverteArray[size-1].triangleTypeIndex + 1);//last triangle.
}

Animation* MDLImporter::buildAnimation(MDLAnimation& animation)
{
    Animation* anim = new Animation();
    anim->SetName(animation.GetName());
    anim->SetFrameRate(animation.Getfps());
    anim->SetFrameSize(animation.GetFrameSize());
    for(int j = 0; j < animation.GetFrameSize();j++){
        anim->addAnimationFrame(buildAnimationFrame(*animation.GetSkeleton(j),j));
    }
    return anim;
}

AnimationFrame * MDLImporter::buildAnimationFrame(MDLSkeleton& mdlskeleton, int nframe)
{
    AnimationFrame* frame = new AnimationFrame();
    Skeleton* skeleton = new Skeleton();
    buildModelSkeleton(*skeleton, mdlskeleton);
    frame->SetFrameNumber(nframe);
    frame->SetSkeleton(skeleton);
    return frame;
}


// md5animbaseframe* MDLImporter::buildMD5BaseFrame(vector<md5joint*>& joints)
// {
//     md5animbaseframe* md5BaseAnimation = new md5animbaseframe();
//     vector<md5animjointlocation*> jointLocations;
//     int jointsize = joints.size();
//     for(int i = 0; i < jointsize; i++){
//         jointLocations.push_back(buildmd5animjointlocation(*joints.at(i)));
//     }
//     md5BaseAnimation->setJointLocations(jointLocations);
//     return md5BaseAnimation;
// }
// 
// md5animjointlocation * MDLImporter::buildmd5animjointlocation(md5joint& joint)
// {
//     md5animjointlocation * md5animjoint = new md5animjointlocation();
//     md5animjoint->setJointIndex(0);
//     MVector3<float>* t = new MVector3<float>(*joint.getPosition());
//     md5animjoint->setPosition(t);
//     MQuaternion<float>* q = new MQuaternion<float>(*joint.getRotation());
//     md5animjoint->setRotation(q);
//     md5animjoint->setJointIndex(joint.getParent());
//     return md5animjoint;
// }



string MDLImporter::space2underscore(string text) {
    for(string::iterator it = text.begin(); it != text.end(); ++it) {
        if(*it == ' ') {
            *it = '_';
        }
    }
    return text;
}

