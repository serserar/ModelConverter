/* 
 * File:   MDLMesh.h
 * Author: serserar
 *
 * Created on February 20, 2016, 9:53 PM
 */

#ifndef MDLMESH_H
#define	MDLMESH_H
#include <iostream>
#include "mdlspecs.h"
#include "MDLTexture.h"
#include "../util/Triangles.h"
#include <vector>
using namespace std;

class MDLMesh {
public:
    MDLMesh();
    MDLMesh(const MDLMesh& orig);
    virtual ~MDLMesh();
    void addMDLVertex(vertexinfo_s* vertex);
    vertexinfo_s* getMDLVertex(int index);
    vertexinfo_s* getMDLVertexArray();
    int GetSize();
    void Fill(vector<vertexinfo_s *>& vertexArray, int size);
    MDLTexture* GetTexture();
    void SetTexture(MDLTexture& texture);
    int GetNumTriangles();
    void SetNumTriangles(int numtriangles);
    void AddTriangles(Triangles<vertexinfo_s*> * triangles);
    Triangles<vertexinfo_s*>* GetTriangle(int index);
    int GetTriangleListSize();
private:
    vector<vertexinfo_s *> vertexList;
    vector<Triangles<vertexinfo_s*>*> triangleList;
    MDLTexture* texture;
    int numtriangles;
};

#endif	/* MDLMESH_H */

