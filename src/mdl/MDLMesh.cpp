/* 
 * File:   MDLMesh.cpp
 * Author: serserar
 * 
 * Created on February 20, 2016, 9:53 PM
 */

#include "MDLMesh.h"

MDLMesh::MDLMesh() {
    this->texture = nullptr;
}

MDLMesh::MDLMesh(const MDLMesh& orig) {
    this->texture = new MDLTexture(*orig.texture);
}

MDLMesh::~MDLMesh() {
    for(auto iter = vertexList.begin(); iter != vertexList.end();++iter){
        delete *iter;
    }
}

void MDLMesh::addMDLVertex(vertexinfo_s* vertex) {
    vertexList.push_back(vertex);
}

vertexinfo_s* MDLMesh::getMDLVertex(int index) {
    vertexinfo_s* vertex = nullptr;
    if (vertexList.size() > index)
        vertex = vertexList.at(index);
    return vertex;
}

vertexinfo_s * MDLMesh::getMDLVertexArray()
{
    vertexinfo_s * vertexArray = nullptr;
    if(vertexList.size() > 0){
        vertexArray = new vertexinfo_s [vertexList.size()];
        for(int i = 0; i < vertexList.size();i++){
            vertexArray[i]=*vertexList.at(i);
        }        
    }
    return vertexArray;
}

int MDLMesh::GetSize()
{
    return vertexList.size();
}

void MDLMesh::Fill(vector<vertexinfo_s *>& vertexArray, int size) {
    vertexArray.swap(vertexList);
}

MDLTexture* MDLMesh::GetTexture() {
    return this->texture;
}

void MDLMesh::SetTexture(MDLTexture& texture) {
    this->texture = &texture;
}


int MDLMesh::GetNumTriangles()
{
    return this->numtriangles;
}

void MDLMesh::SetNumTriangles(int numtriangles)
{
    this->numtriangles = numtriangles;
}

 void MDLMesh::AddTriangles(Triangles<vertexinfo_s*> * triangles)
{
    triangleList.push_back(triangles);
}
Triangles<vertexinfo_s *> * MDLMesh::GetTriangle(int index)
{
    Triangles<vertexinfo_s *> * triangle = nullptr;
    if(index < triangleList.size()){
        triangle = triangleList.at(index);
    }
    return triangle;
}

int MDLMesh::GetTriangleListSize()
{
    return triangleList.size();
}
