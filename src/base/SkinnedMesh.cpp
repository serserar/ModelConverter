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

#include "SkinnedMesh.h"

SkinnedMesh::SkinnedMesh()
{
    this->bindPoseMesh = nullptr;
    this->currentPose = nullptr;
}

SkinnedMesh::SkinnedMesh(Mesh& mesh)
{
    this->bindPoseMesh = nullptr;
    this->currentPose = nullptr;
    /** copy Buffer data holding buffers and number of coordinates per vertex */
    this->vertexCoords = mesh.vertexCoords;
    this->normalCoords = mesh.normalCoords;
    this->colorCoords = mesh.colorCoords;
    this->fogCoords = mesh.fogCoords;
    this->tangentCoords = mesh.tangentCoords;
    this->textureCoords = mesh.textureCoords;

    /** Interleaved data (for VBO id use). */
    this->interleaved = mesh.interleaved;

    /** Index data. */
    this->indexBuffer = mesh.indexBuffer;//vertex index
    this->indexLenghts = mesh.indexLenghts;//primitive indexmode lenghts (vertex lenghts of each primitive)
    this->indexModeBuffer = mesh.indexModeBuffer;//primitive (index mode) buffer
    this->triangleIndexList = mesh.triangleIndexList;
    this->primitiveCounts = mesh.primitiveCounts;
    this->indexSections=mesh.indexSections;//map with primitive index per section
    this->bbox = mesh.bbox;
    for(auto triangle:mesh.triangleList){
        this->triangleList.push_back(triangle);
    }
}

void SkinnedMesh::updatePose(SkeletonPose<float>& pose)
{
    this->currentPose = &pose;
    applyPose();//apply currentpose
    UpdateTriangleList();
}


void SkinnedMesh::applyPose()
{
    if(currentPose) {
        this->vertexCoords.clear();
        this->normalCoords.clear();
        vector<float>& poseVerts = this->vertexCoords;
        vector<float>& poseNorms = this->normalCoords;
        vector<float>& bindPoseVerts = bindPoseMesh->vertexCoords;
        vector<float>& bindPoseNorms = bindPoseMesh->normalCoords;
        double bindVX, bindVY, bindVZ;
        double bindNX = 0, bindNY = 0, bindNZ = 0;
        double vSumX, vSumY, vSumZ;
        double nSumX = 0, nSumY = 0, nSumZ = 0;
        double tempX, tempY, tempZ;
        float weight;
        int normIndex = 0;
        int jointIndex;
        MMatrix4<float> jntMat;
        int vertexSize = bindPoseVerts.size()/3;
        for(int v = 0; v < vertexSize; v++) {
            // zero out our sum var
            vSumX = 0;
            vSumY = 0;
            vSumZ = 0;
            // Grab the bind pose vertex Vbp from _bindPoseData
            bindVX = bindPoseVerts.at(v*3);
            bindVY = bindPoseVerts.at(v*3+1);
            bindVZ = bindPoseVerts.at(v*3+2);
            if(!bindPoseNorms.empty()) {
                // zero out our sum var
                nSumX = 0;
                nSumY = 0;
                nSumZ = 0;

                // recover norms from bind pose
                bindNX = bindPoseNorms.at(normIndex);
                normIndex++;
                bindNY = bindPoseNorms.at(normIndex);
                normIndex++;
                bindNZ = bindPoseNorms.at(normIndex);
                normIndex++;
            }
            for(int w = 0; w < weightsPerVertex; w++) {
                int index = v * weightsPerVertex + w;//index joint of the weight
                if (weights.at(index) == 0) {
                    continue;
                }
                jointIndex = jointIndices[index];
                jntMat = *currentPose->matrixpalette.at(jointIndex);
                weight = weights.at(index);
                // Multiply our vertex by the matrix palette entry
                tempX = jntMat.getM00() * bindVX + jntMat.getM01() * bindVY + jntMat.getM02() * bindVZ
                        + jntMat.getM03();
                tempY = jntMat.getM10() * bindVX + jntMat.getM11() * bindVY + jntMat.getM12() * bindVZ
                        + jntMat.getM13();
                tempZ = jntMat.getM20() * bindVX + jntMat.getM21() * bindVY + jntMat.getM22() * bindVZ
                        + jntMat.getM23();

                // Sum, weighted.
                vSumX += tempX * weight;
                vSumY += tempY * weight;
                vSumZ += tempZ * weight;
                if (!bindPoseNorms.empty()) {
                    // Multiply our normal by the matrix palette entry
                    tempX = jntMat.getM00() * bindNX + jntMat.getM01() * bindNY + jntMat.getM02() * bindNZ;
                    tempY = jntMat.getM10() * bindNX + jntMat.getM11() * bindNY + jntMat.getM12() * bindNZ;
                    tempZ = jntMat.getM20() * bindNX + jntMat.getM21() * bindNY + jntMat.getM22() * bindNZ;

                    // Sum, weighted.
                    nSumX += tempX * weight;
                    nSumY += tempY * weight;
                    nSumZ += tempZ * weight;
                }
            }

            // Store sum into _meshData
            poseVerts.push_back(vSumX);
            poseVerts.push_back(vSumY);
            poseVerts.push_back(vSumZ);

            if (!bindPoseNorms.empty()) {
                poseNorms.push_back(nSumX);
                poseNorms.push_back(nSumY);
                poseNorms.push_back(nSumZ);
            }
        }
    }
}

void SkinnedMesh::SetBindPoseMesh(Mesh* bindPoseMesh)
{
    if(this->bindPoseMesh) {
        delete this->bindPoseMesh;
    }
    this->bindPoseMesh = bindPoseMesh;
}

Mesh * SkinnedMesh::GetBindPoseMesh()
{
    return this->bindPoseMesh;
}


void SkinnedMesh::ApplyTransform(MTransform<float>& transform)
{
    Mesh::ApplyTransform(transform);
}

void SkinnedMesh::ApplyTransforms()
{
    Mesh::ApplyTransforms();
}



