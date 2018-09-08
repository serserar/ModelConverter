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

#ifndef MESH_H
#define MESH_H
#include <vector>
#include <map>
#include "Triangles.h"
#include "BBox.h"
#include "../math/MPlane.h"
#include "../math/MTransform.h"

using namespace std;

class Mesh
{
public:
    Mesh();
    Mesh(const Mesh& mesh);
    ~Mesh();
    enum indexMode {Triangles, TriangleStrip, TriangleFan, Quads, QuadStrip, Lines, LineStrip, LineLoop, Points};
    int GetVertexSize();
    int GetSectionCount();//return primitive sections
    void GetTrianglesIndex(vector<Triangle>& triangleIndexList);
    int GetPrimitiveCount(int section);
    void UpdatePrimitiveCounts();
    void UpdateTriangleList();
    void ConvertToTriangles(vector<Triangle>& triangleList);
    void ConvertToTriangles();
    void GetPrimitiveIndices(int primitiveIndex, int section, vector<int>& storeIndex);
    int GetVertexIndex(int primitiveIndex, int point, int section);
    Triangle GetTriangleFromPrimitive(Mesh::indexMode mode, vector<int> vertexIndices);
    static int GetPrimitiveCount(Mesh::indexMode indexMode, int size);
    static int GetPrimitiveSize(Mesh::indexMode indexMode);
    void computeBBox();
    string GetTextureName();
    void SetTextureName(string textureName);
    bool intersect(MVector3<float>& orig, MVector3<float>& dir, MVector3<float>& intersectionPoint);
    bool RayIntersectsTriangle(MVector3<float>& rayOrigin, MVector3<float>& rayDest, Triangle& triangle, MVector3<float>& intersectionPoint);
    void AppendMesh(Mesh& mesh);
    virtual void ApplyTransform(MTransform<float>& transform);
    virtual void ApplyTransforms();
    /** Buffer data holding buffers and number of coordinates per vertex */
    vector<float> vertexCoords;
    vector<float> normalCoords;
    vector<float> colorCoords;
    vector<float> fogCoords;
    vector<float> tangentCoords;
    vector<vector<float>> textureCoords;

    /** Interleaved data (for VBO id use). */
    vector<float> interleaved;

    /** Index data. */
    vector<int> indexBuffer;//vertex index
    vector<int> indexLenghts;//primitive indexmode lenghts (vertex lenghts of each primitive)
    vector<indexMode> indexModeBuffer;//primitive (index mode) buffer
    vector<int> triangleIndexList;
    vector<int> primitiveCounts;
    map<int,vector<int>> indexSections;//map with primitive index per section
    BBox bbox;
    vector<Triangle> triangleList;
protected :
    int valuesPerVertex;
    string textureName;
    bool dirty;
    MTransform<float> worldTransform;
    MTransform<float> localTransform;
};

#endif // MESH_H
