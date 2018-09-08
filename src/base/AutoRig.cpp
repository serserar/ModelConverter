/*
 * Copyright 2018 <copyright holder> <email>
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
 */

#include "AutoRig.h"
#include <algorithm>
using namespace std;

Cluster::Cluster()
{
}

Cluster::Cluster(Joint& joint)
{
    this->box.boundMin.SetX(joint.GetPosition()->GetX());
    this->box.boundMin.SetY(joint.GetPosition()->GetY());
    this->box.boundMin.SetZ(joint.GetPosition()->GetZ());
    this->box.boundMax.SetX(joint.GetPosition()->GetX());
    this->box.boundMax.SetY(joint.GetPosition()->GetY());
    this->box.boundMax.SetZ(joint.GetPosition()->GetZ());
    this->name = joint.GetName();
    this->center = *joint.GetPosition();
}

void Cluster::AddVertex(MVector3<float>& vertex)
{
    cout << "Joint : " << name << endl;
    cout << "Center : " << center << endl;
    cout << "Vertex : " << vertex << endl;
    cout << "Actual : " << box << endl;
    if(vertex.GetX() > box.boundMax.GetX()) {
        box.boundMax.SetX(vertex.GetX());
    }
    if(vertex.GetY() > box.boundMax.GetY()) {
        box.boundMax.SetY(vertex.GetY());
    }
    if(vertex.GetZ() > box.boundMax.GetZ()) {
        box.boundMax.SetZ(vertex.GetZ());
    }
    if(vertex.GetX() < box.boundMin.GetX()) {
        box.boundMin.SetX(vertex.GetX());
    }
    if(vertex.GetY() < box.boundMin.GetY()) {
        box.boundMin.SetY(vertex.GetY());
    }
    if(vertex.GetZ() < box.boundMin.GetZ()) {
        box.boundMin.SetZ(vertex.GetZ());
    }
    cout << "Updated : " << box << endl;
}

bool Cluster::CheckInside(MVector3<float>& vertex)
{
    return box.Contains(vertex);
}


AutoRig::AutoRig()
{

}

AutoRig::AutoRig(const AutoRig& other)
{

}

AutoRig::~AutoRig()
{

}

SkinnedMesh* AutoRig::AutoRigMesh(Mesh& mesh, int meshIndex, Skeleton& skeleton)
{
    return CheckBoneHeat(mesh, meshIndex, skeleton);
    //return CheckCluster(mesh, skeleton);
    //return CheckGraphCluster(mesh, meshIndex, skeleton);
    //return NearestNeighbour(mesh, skeleton);
}


void AutoRig::PrintBoneCluster(SkinnedMesh& mesh, Skeleton& skeleton, std::ostream& output)
{
//     map<int,Joint*> boneTable;
//     Joint* joint;
//     //init bone lookup table
//     for(int i = 0; i < skeleton.GetJointSize(); i++) {
//         joint = skeleton.GetJoint(i);
//         boneTable[joint->GetIndex()]=joint;
//     }
    map<int,vector<int>> boneVertexTable;
    for(int i = 0; i < mesh.jointIndices.size(); i++) {
        boneVertexTable[mesh.jointIndices.at(i)].push_back(i);
    }
    for (auto it=boneVertexTable.begin(); it!=boneVertexTable.end(); ++it) {
        output  << it->first << "( " <<  skeleton.GetJoint(it->first)->GetName() << " ) => { "  ;
        for(auto itvec = it->second.begin(); itvec!=it->second.end(); ++itvec) {
            output  << *itvec << " , ";
        }
        output  << " }" << std::endl;
    }
}

void AutoRig::BuildClusters(SkinnedMesh& mesh, Skeleton& skeleton)
{
    //build clusters
    for(int j = 0; j < skeleton.GetJointSize(); j++) {
        Cluster cluster(*skeleton.GetJoint(j));
        boneClusterTable[skeleton.GetJoint(j)->GetIndex()]=cluster;
    }
    int index = 0;
    MVector3<float> vertex;
    for(int i = 0; i < mesh.jointIndices.size(); i++) {
        index = i*3;
        vertex.SetX(mesh.vertexCoords.at(index));
        vertex.SetY(mesh.vertexCoords.at(index+1));
        vertex.SetZ(mesh.vertexCoords.at(index+2));

        if(index == 1335) {//[X=6.21056, Y=2.14991, Z=0.03787]
            boneClusterTable[mesh.jointIndices.at(i)].AddVertex(vertex);;
        } else {
            boneClusterTable[mesh.jointIndices.at(i)].AddVertex(vertex);;
        }
    }
    for (auto it=boneClusterTable.begin(); it!=boneClusterTable.end(); ++it) {
        cout << it->second.name << " " << it->second.box  << " " << it->second.center << endl;
    }
}

SkinnedMesh* AutoRig::NearestNeighbour(Mesh& mesh, Skeleton& skeleton)
{
    SkinnedMesh* skinnedMesh = nullptr;
    map<int,Joint*> boneTable;
    Joint* joint;
    //init bone lookup table
    for(int i = 0; i < skeleton.GetJointSize(); i++) {
        joint = skeleton.GetJoint(i);
        boneTable[joint->GetIndex()]=joint;
    }
    skinnedMesh = new SkinnedMesh(mesh);
    //for each vertex
    for(int v = 0; v < mesh.vertexCoords.size(); v+=3) {
        //compute nearest bone
        int jointIndex=-1;
        MVector3<float> vertex(mesh.vertexCoords.at(v), mesh.vertexCoords.at(v+1), mesh.vertexCoords.at(v+2));
        Joint* joint;
        float distance = numeric_limits<float>::infinity();
        for(int j = 0; j < skeleton.GetJointSize(); j++) {
            joint = skeleton.GetJoint(j);
            if(joint->GetParent()==-1) {
                continue;
            }
            MVector3<float> disVec = vertex- *joint->GetPosition();
            float ndistance = disVec.magnitude();
            if(ndistance < distance) {
                distance=ndistance;
                jointIndex=joint->GetIndex();
            }
        }
        skinnedMesh->jointIndices.push_back(jointIndex);//add vertex joint index
        skinnedMesh->weightsPerVertex = 1;
        skinnedMesh->weights.push_back(1.0);
        skinnedMesh->indexBuffer.push_back(v);//vertex Index
    }
    return skinnedMesh;
}

SkinnedMesh * AutoRig::CheckCluster(Mesh& mesh, Skeleton& skeleton)
{
    SkinnedMesh* skinnedMesh = nullptr;
    skinnedMesh = new SkinnedMesh(mesh);
    //for each vertex
    for(int v = 0; v < mesh.vertexCoords.size(); v+=3) {
        //compute nearest bone
        int jointIndex=-1;
        if(v == 1335) {//[X=6.21056, Y=2.14991, Z=0.03787]
            cout << 1335 << endl;
        }
        MVector3<float> vertex(mesh.vertexCoords.at(v), mesh.vertexCoords.at(v+1), mesh.vertexCoords.at(v+2));
        for (auto it=boneClusterTable.begin(); it!=boneClusterTable.end(); ++it) {
            if(it->second.CheckInside(vertex)) {
//                 if(jointIndex != -1) {
//                     MVector3<float> disVecOld = vertex- boneClusterTable.at(jointIndex).center;
//                     float oldDistance = disVecOld.magnitude();
//                     MVector3<float> disVec = vertex- it->second.center;
//                     float ndistance = disVec.magnitude();
//                     if(ndistance < oldDistance) {
//                         jointIndex=it->first;
//                     }
//                 } else {
                jointIndex=it->first;
                break;
//                 }
            }
        }
        if(jointIndex == -1) {
            cout << vertex << endl;
        }
        skinnedMesh->jointIndices.push_back(jointIndex);//add vertex joint index
        skinnedMesh->weightsPerVertex = 1;
        skinnedMesh->weights.push_back(1.0);
        skinnedMesh->indexBuffer.push_back(v);//vertex Index
    }
    return skinnedMesh;
}

SkinnedMesh * AutoRig::CheckBoneHeat(Mesh& mesh, int meshIndex, Skeleton& skeleton)
{
    SkinnedMesh* skinnedMesh = skinnedMesh = new SkinnedMesh(mesh);
    VoxelizerTool voxelizer;
    BBox size;
    std::vector<BBox> voxelList;
    Mesh* voxelMesh = voxelizer.VoxelixeExt(mesh, meshIndex, 0.0001f, size, true,voxelList);
    if(voxelMesh) {

    }
    return skinnedMesh;
}

SkinnedMesh * AutoRig::CheckGraphCluster(Mesh& mesh, int meshIndex, Skeleton& skeleton)
{
    SkinnedMesh* skinnedMesh = skinnedMesh = new SkinnedMesh(mesh);
    int triangleIndex=0;
    map<int,std::vector<int>> vertexMap;
    MVector3<float> v01;
    MVector3<float> v02;
    MVector3<float> v03;
    for ( auto triangle : mesh.triangleList ) {
        if(triangle.vindex1 == 0) {
            v01=triangle.v1;
            v02=triangle.v2;
            v03=triangle.v3;
            std::cout << triangle.v1 << endl;
            std::cout << triangle.v2 << endl;
            std::cout << triangle.v3 << endl;
        }
        if(triangle.v1==v01 ) {
            std::cout << triangle.primitiveIndex << endl;
            std::cout << triangle.v1 << endl;
            std::cout << triangle.v2 << endl;
            std::cout << triangle.v3 << endl;
        }
        if(triangle.v2==v01 ) {
            std::cout << triangle.primitiveIndex << endl;
            std::cout << triangle.v1 << endl;
            std::cout << triangle.v2 << endl;
            std::cout << triangle.v3 << endl;
        }
        if(triangle.v3==v01 ) {
            std::cout << triangle.primitiveIndex << endl;
            std::cout << triangle.v1 << endl;
            std::cout << triangle.v2 << endl;
            std::cout << triangle.v3 << endl;
        }
//         if(triangle->v1==v02 ){
//             std::cout << triangle->primitiveIndex << endl;
//             std::cout << triangle->v1 << endl;
//             std::cout << triangle->v2 << endl;
//             std::cout << triangle->v3 << endl;
//         }
//         if(triangle->v2==v02 ){
//             std::cout << triangle->primitiveIndex << endl;
//             std::cout << triangle->v1 << endl;
//             std::cout << triangle->v2 << endl;
//             std::cout << triangle->v3 << endl;
//         }
//         if(triangle->v3==v02 ){
//             std::cout << triangle->primitiveIndex << endl;
//             std::cout << triangle->v1 << endl;
//             std::cout << triangle->v2 << endl;
//             std::cout << triangle->v3 << endl;
//         }
//         if(triangle->v1==v03){
//             std::cout << triangle->primitiveIndex << endl;
//             std::cout << triangle->v1 << endl;
//             std::cout << triangle->v2 << endl;
//             std::cout << triangle->v3 << endl;
//         }
//         if(triangle->v2==v03){
//             std::cout << triangle->primitiveIndex << endl;
//             std::cout << triangle->v1 << endl;
//             std::cout << triangle->v2 << endl;
//             std::cout << triangle->v3 << endl;
//         }
//         if(triangle->v3==v03){
//             std::cout << triangle->primitiveIndex << endl;
//             std::cout << triangle->v1 << endl;
//             std::cout << triangle->v2 << endl;
//             std::cout << triangle->v3 << endl;
//         }
        vertexMap[triangle.vindex1].push_back(triangle.primitiveIndex);
        vertexMap[triangle.vindex2].push_back(triangle.primitiveIndex);
        vertexMap[triangle.vindex3].push_back(triangle.primitiveIndex);
    }
    map<int,std::vector<int>> neighbourMap;
    for ( auto triangle : mesh.triangleList ) {
        vector<int> primitiveIndexList = vertexMap[triangle.vindex1];
        for(int primitiveIntex : primitiveIndexList) {
            if(std::find(neighbourMap[triangle.primitiveIndex].begin(), neighbourMap[triangle.primitiveIndex].end(), primitiveIntex) == neighbourMap[triangle.primitiveIndex].end()) {
                if(triangle.primitiveIndex !=primitiveIntex) {
                    neighbourMap[triangle.primitiveIndex].push_back(primitiveIntex);
                }
            }
        }
        primitiveIndexList = vertexMap[triangle.vindex2];
        for(int primitiveIntex : primitiveIndexList) {
            if(std::find(neighbourMap[triangle.primitiveIndex].begin(), neighbourMap[triangle.primitiveIndex].end(), primitiveIntex) == neighbourMap[triangle.primitiveIndex].end()) {
                if(triangle.primitiveIndex !=primitiveIntex) {
                    neighbourMap[triangle.primitiveIndex].push_back(primitiveIntex);
                }
            }
        }
        primitiveIndexList = vertexMap[triangle.vindex3];
        for(int primitiveIntex : primitiveIndexList) {
            if(std::find(neighbourMap[triangle.primitiveIndex].begin(), neighbourMap[triangle.primitiveIndex].end(), primitiveIntex) == neighbourMap[triangle.primitiveIndex].end()) {
                if(triangle.primitiveIndex !=primitiveIntex) {
                    neighbourMap[triangle.primitiveIndex].push_back(primitiveIntex);
                }
            }
        }
    }
    return skinnedMesh;
}

