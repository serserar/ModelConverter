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

#include "Mesh.h"

Mesh::Mesh()
{
    this->dirty = false;
}

Mesh::Mesh(const Mesh& mesh)
{
    this->vertexCoords = mesh.vertexCoords;
    this->normalCoords = mesh.normalCoords;
    this->colorCoords = mesh.colorCoords;
    this->fogCoords = mesh.fogCoords;
    this->tangentCoords = mesh.tangentCoords;
    this->textureCoords = mesh.textureCoords;
    this->interleaved = mesh.interleaved;
    this->indexBuffer = mesh.indexBuffer;
    this->indexModeBuffer = mesh.indexModeBuffer;
    this->indexLenghts = mesh.indexLenghts; 
    this->triangleIndexList = mesh.triangleIndexList;
    this->primitiveCounts = mesh.primitiveCounts;
    this->indexSections = mesh.indexSections;
    this->bbox = mesh.bbox;
    this->triangleList= mesh.triangleList;
    this->dirty = mesh.dirty;
    this->valuesPerVertex = 3;
}


Mesh::~Mesh()
{

}

int Mesh::GetPrimitiveCount(int section)
{
    return primitiveCounts.at(section);
}

int Mesh::GetSectionCount()
{
    return this->indexLenghts.size();
}

/* calculate number of primitives for a size of vertex */
int Mesh::GetPrimitiveCount(Mesh::indexMode indexMode, int size)
{
    int count = 0;
    switch (indexMode) {
    case Triangles:
        count = size / 3;
        break;
    case TriangleFan:
    case TriangleStrip:
        count = size - 2;
        break;
    case Quads:
        count = size / 4;
        break;
    case QuadStrip:
        count = size / 2 - 1;
        break;
    case Lines:
        count = size / 2;
        break;
    case LineStrip:
        count = size - 1;
        break;
    case LineLoop:
        count = size;
        break;
    case Points:
        count = size;
        break;
    }
    return count;
}

int Mesh::GetPrimitiveSize(Mesh::indexMode indexMode)
{
    int size = 0;
    switch (indexMode) {
    case Triangles:
    case TriangleFan:
    case TriangleStrip:
        size = 3;
        break;
    case Quads:
    case QuadStrip:
        size = 4;
        break;
    case Lines:
    case LineStrip:
    case LineLoop:
        size = 2;
        break;
    case Points:
        size = 1;
        break;
    }
    return size;
}

void Mesh::GetTrianglesIndex(vector<Triangle>& triangles)
{
    if(triangleList.empty()) {
        UpdateTriangleList();
    }
    for(auto triangle : triangleList) {
        triangles.push_back(triangle);
    }
}

int Mesh::GetVertexSize()
{
    return vertexCoords.size() / valuesPerVertex;
}

/* update primitives for each section */
void Mesh::UpdatePrimitiveCounts()
{
    primitiveCounts.clear();
    int maxSection = indexLenghts.size();
    for (int i = 0; i < maxSection; i++) {
        int size = indexLenghts.at(i);
        int count = GetPrimitiveCount(indexModeBuffer.at(i), size);
        primitiveCounts.push_back(count);
    }
}

void Mesh::UpdateTriangleList()
{

    triangleList.clear();
    ConvertToTriangles(triangleList);
//     for (int section = 0; section < GetSectionCount(); section++) {
//         int primitives = GetPrimitiveCount(section);
//         vector<int> vertex;
//         for (int primitive = 0; primitive < primitives; primitive++) {//for each primitive recover index and transform to triangles
//             GetPrimitiveIndices(primitive, section, vertex);
//             Triangle triangle(vertex[0], vertex[1], vertex[2]);
//             triangle.primitiveIndex=triangleList.size();
//             triangle.v1=MVector3<float>(vertexCoords.at(vertex[0]), vertexCoords.at(vertex[0]+1), vertexCoords.at(vertex[0]+2));
//             triangle.v2=MVector3<float>(vertexCoords.at(vertex[1]), vertexCoords.at(vertex[1]+1), vertexCoords.at(vertex[1]+2));
//             triangle.v3=MVector3<float>(vertexCoords.at(vertex[2]), vertexCoords.at(vertex[2]+1), vertexCoords.at(vertex[2]+2));
//             triangleList.push_back(triangle);
//             vertex.clear();
//         }
//     }
}

void Mesh::ConvertToTriangles(vector<Triangle>& triangles)
{
    bool ccw = true;
    int degenerates = 0;
    int triangleIndex = 0;
    for (int section = 0; section < GetSectionCount(); section++) {
        //int primitives = GetPrimitiveCount(section);
        auto indexMode = indexModeBuffer.at(section);
        //vector<int> temp;
        vector<MVector3<float>> vertexList;
        vector<int> indexList = indexSections[section];


//         for (int primitive = 0; primitive < primitives; primitive++) {//for each primitive recover index and transform to triangles
//             GetPrimitiveIndices(primitive, section, temp);
//             MVector3<float> v1 = MVector3<float>(vertexCoords.at(temp[0]), vertexCoords.at(temp[0]+1), vertexCoords.at(temp[0]+2));
//             vertexList.push_back(v1);
//             indexList.push_back(temp[0]);
//             MVector3<float> v2 = MVector3<float>(vertexCoords.at(temp[1]), vertexCoords.at(temp[1]+1), vertexCoords.at(temp[1]+2));
//             vertexList.push_back(v2);
//             indexList.push_back(temp[1]);
//             MVector3<float> v3 = MVector3<float>(vertexCoords.at(temp[2]), vertexCoords.at(temp[2]+1), vertexCoords.at(temp[2]+2));
//             vertexList.push_back(v3);
//             indexList.push_back(temp[2]);
//             temp.clear();
//         }

        if(indexMode == Mesh::TriangleStrip) {
            for (int index= 0; index < indexList.size()-2; index++) {
                Triangle triangle;
                if (index & 1) {
                    triangle.vindex1 = indexList.at(index+1);
                    triangle.vindex2 = indexList.at(index);
                    triangle.vindex3 = indexList.at(index+2);
                    triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                    triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                    triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));

                } else {
                    triangle.vindex1 = indexList.at(index);
                    triangle.vindex2 = indexList.at(index+1);
                    triangle.vindex3 = indexList.at(index+2);
                    triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                    triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                    triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));
                }
                triangle.vindex1 = triangleIndex;
                triangle.vindex2 = triangleIndex+1;
                triangle.vindex3 = triangleIndex+2;
                triangles.push_back(triangle);
                triangleIndex+=3;
            }
        } else if(indexMode == Mesh::TriangleFan) {
            for (int index= 0; index < indexList.size()-2; index++) {
                Triangle triangle;
                triangle.vindex1 = indexList.at(0);
                triangle.vindex2 = indexList.at(index+1);
                triangle.vindex3 = indexList.at(index+2);
                triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));
                triangle.vindex1 = triangleIndex;
                triangle.vindex2 = triangleIndex+1;
                triangle.vindex3 = triangleIndex+2;
                triangles.push_back(triangle);
                triangleIndex+=3;
            }
        } else if(indexMode == Mesh::Triangles) {
            for (int index= 0; index < indexList.size(); index+=3) {
                Triangle triangle;
                triangle.vindex1 = indexList.at(index);
                triangle.vindex2 = indexList.at(index+1);
                triangle.vindex3 = indexList.at(index+2);
                triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));
                triangle.vindex1 = triangleIndex;
                triangle.vindex2 = triangleIndex+1;
                triangle.vindex3 = triangleIndex+2;
                triangles.push_back(triangle);
                triangleIndex+=3;
            }
        }
    }
    cout << "Total triangles : " << triangles.size() << endl;
    cout << "Total degenerates : " << degenerates << endl;
}

void Mesh::ConvertToTriangles()
{
    for (int section = 0; section < GetSectionCount(); section++) {
        vector<Triangle> triangles;
        //int primitives = GetPrimitiveCount(section);
        auto indexMode = indexModeBuffer.at(section);
        //vector<int> temp;
        vector<MVector3<float>> vertexList;
        vector<int> indexList = indexSections[section];


//         for (int primitive = 0; primitive < primitives; primitive++) {//for each primitive recover index and transform to triangles
//             GetPrimitiveIndices(primitive, section, temp);
//             MVector3<float> v1 = MVector3<float>(vertexCoords.at(temp[0]), vertexCoords.at(temp[0]+1), vertexCoords.at(temp[0]+2));
//             vertexList.push_back(v1);
//             indexList.push_back(temp[0]);
//             MVector3<float> v2 = MVector3<float>(vertexCoords.at(temp[1]), vertexCoords.at(temp[1]+1), vertexCoords.at(temp[1]+2));
//             vertexList.push_back(v2);
//             indexList.push_back(temp[1]);
//             MVector3<float> v3 = MVector3<float>(vertexCoords.at(temp[2]), vertexCoords.at(temp[2]+1), vertexCoords.at(temp[2]+2));
//             vertexList.push_back(v3);
//             indexList.push_back(temp[2]);
//             temp.clear();
//         }


        if(indexMode == Mesh::TriangleStrip) {
            for (int index= 0; index < indexList.size()-2; index++) {
                Triangle triangle;
                if (index & 1) {
                    triangle.vindex1 = indexList.at(index+1);
                    triangle.vindex2 = indexList.at(index);
                    triangle.vindex3 = indexList.at(index+2);
                    triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                    triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                    triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));

                } else {
                    triangle.vindex1 = indexList.at(index);
                    triangle.vindex2 = indexList.at(index+1);
                    triangle.vindex3 = indexList.at(index+2);
                    triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                    triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                    triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));
                }
                triangles.push_back(triangle);
            }
        } else if(indexMode == Mesh::TriangleFan) {
            for (int index= 0; index < indexList.size()-2; index++) {
                Triangle triangle;
                triangle.vindex1 = indexList.at(0);
                triangle.vindex2 = indexList.at(index+1);
                triangle.vindex3 = indexList.at(index+2);
                triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));
                triangles.push_back(triangle);
            }
        } else if(indexMode == Mesh::Triangles) {
            for (int index= 0; index < indexList.size(); index+=3) {
                Triangle triangle;
                triangle.vindex1 = indexList.at(index);
                triangle.vindex2 = indexList.at(index+1);
                triangle.vindex3 = indexList.at(index+2);
                triangle.v1 = MVector3<float>(vertexCoords.at(triangle.vindex1*3), vertexCoords.at(triangle.vindex1*3+1), vertexCoords.at(triangle.vindex1*3+2));
                triangle.v2 = MVector3<float>(vertexCoords.at(triangle.vindex2*3), vertexCoords.at(triangle.vindex2*3+1), vertexCoords.at(triangle.vindex2*3+2));
                triangle.v3 = MVector3<float>(vertexCoords.at(triangle.vindex3*3), vertexCoords.at(triangle.vindex3*3+1), vertexCoords.at(triangle.vindex3*3+2));
                triangles.push_back(triangle);
            }
        }
        //loop over section triangles
        indexModeBuffer[section]=Mesh::Triangles;
        for(auto triangle:triangles) {
        }
    }
}


void Mesh::GetPrimitiveIndices(int primitiveIndex, int section, vector<int>& storeIndex)
{
    int count = GetPrimitiveCount(section);
    if (primitiveIndex >= count || primitiveIndex < 0) {

    }

    auto mode = indexModeBuffer[section];
    int rSize = GetPrimitiveSize(mode);

    for (int i = 0; i < rSize; i++) {
        storeIndex.push_back(GetVertexIndex(primitiveIndex, i, section));
    }

}


int Mesh::GetVertexIndex(int primitiveIndex, int point, int section)
{
    int index = 0;
    switch(indexModeBuffer[section]) {
    case Triangles:
        index += (primitiveIndex * 3) + point;
        break;
    case TriangleStrip:
        // XXX: we need to flip point 0 and 1 on odd primitiveIndex values
        if (point < 2 && primitiveIndex % 2 == 1) {
            index += primitiveIndex + (point == 0 ? 1 : 0);
        } else {
            index += primitiveIndex + point;
        }
        break;
    case TriangleFan:
        if (point == 0) {
            index += 0;
        } else {
            index += primitiveIndex + point;
        }
        break;
    case Quads:
        index += (primitiveIndex * 4) + point;
        break;
    case QuadStrip:
        index += (primitiveIndex * 2) + point;
        break;
    case Points:
        index += primitiveIndex;
        break;
    case Lines:
        index += (primitiveIndex * 2) + point;
        break;
    case LineStrip:
    case LineLoop:
        index += primitiveIndex + point;
        break;
    default:
        return -1;

    }
    return indexSections[section][index];
}

void Mesh::computeBBox()
{
    //iterate over all vertex in the mesh
    //take minx, miny, minz, maxx, maxy and maxz
    float x,y,z = 0.0f;
    bbox.boundMin.SetX(x);
    bbox.boundMin.SetY(y);
    bbox.boundMin.SetZ(z);
    bbox.boundMax.SetX(x);
    bbox.boundMax.SetY(y);
    bbox.boundMax.SetZ(z);
    for(int i = 0; i < vertexCoords.size(); i+=3) {
        x=vertexCoords.at(i);
        y=vertexCoords.at(i+1);
        z=vertexCoords.at(i+2);
        if ( x < bbox.boundMin.GetX() ) bbox.boundMin.SetX(x);
        if ( y < bbox.boundMin.GetY() ) bbox.boundMin.SetY(y);
        if ( z < bbox.boundMin.GetZ() ) bbox.boundMin.SetZ(z);
        if ( x > bbox.boundMax.GetX() ) bbox.boundMax.SetX(x);
        if ( y > bbox.boundMax.GetY() ) bbox.boundMax.SetY(y);
        if ( z > bbox.boundMax.GetZ() ) bbox.boundMax.SetZ(z);
    }
}

string Mesh::GetTextureName()
{
    return this->textureName;
}

void Mesh::SetTextureName(string textureName)
{
    this->textureName = textureName;
}

bool Mesh::intersect(MVector3<float>& rayOrigin, MVector3<float>& rayDest, MVector3<float>& intersectionPoint)
{

    //bool intersect = bbox.Intersects(rayOrigin, rayDest);
    bool intersect = false;
    bool tmpIntersect = false;
    //if(intersect) {
    MVector3<float> testIntersectionPoint;
    for(auto triangle : triangleList) {
        tmpIntersect = RayIntersectsTriangle(rayOrigin, rayDest, triangle, testIntersectionPoint);
        if(tmpIntersect && testIntersectionPoint.GetZ() > intersectionPoint.GetZ()) {
            intersectionPoint = testIntersectionPoint;
            intersect = true;
        }
    }
    //}
    return intersect;
}

bool Mesh::RayIntersectsTriangle(MVector3<float>& rayOrigin, MVector3<float>& rayDest, Triangle& triangle, MVector3<float>& intersectionPoint)
{
    MVector3<float> vertex0 = triangle.v1;
    MVector3<float> vertex1 = triangle.v2;
    MVector3<float> vertex2 = triangle.v3;
    MVector3<float> edge1, edge2, h, s, q;
//     float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    MVector3<float> normal = edge1.CrossProduct(edge2);
    normal.normalize();
    MPlane<float> plane(normal,vertex0);
    bool intersects = plane.IntersectsRay(rayOrigin, rayDest, intersectionPoint);
    if(intersects) {
//check barycentric coords

        // Compute vectors
        MVector3<float> v2 = intersectionPoint - vertex0;
        // Compute dot products
        float dot00 = edge2.dotProduct(edge2);
        float dot01 = edge2.dotProduct(edge1);
        float dot02 = edge2.dotProduct(v2);
        float dot11 = edge1.dotProduct(edge1);
        float dot12 = edge1.dotProduct(v2);

        // Compute barycentric coordinates
        float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
        float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

// Check if point is in triangle
        intersects = (u >= 0) && (v >= 0) && (u + v < 1);
//         if(intersects) {
//             cout << "u : " << u << " v : " << v;
//         }
    }

//     rayDest.CrossProduct(edge2, h);
//     a = edge1.dotProduct(h);
//     if (a > - Math<float>::EPSILON && a < Math<float>::EPSILON)
//         return false;
//     f = 1/a;
//     s = rayOrigin - vertex0;
//     u = f * (s.dotProduct(h));
//     if (u < 0.0 || u > 1.0)
//         return false;
//     s.CrossProduct(edge1, q);
//     v = f * rayDest.dotProduct(q);
//     if (v < 0.0 || u + v > 1.0)
//         return false;
//     // At this stage we can compute t to find out where the intersection point is on the line.
//     float t = f * edge2.dotProduct(q);
//     if (t > Math<float>::EPSILON) // ray intersection
//     {
//         intersectionPoint = rayOrigin + rayDest;
//         intersectionPoint*=t;
//         return true;
//     }
//     else // This means that there is a line intersection but not a ray intersection.
//         return false;

    return intersects;
}

void Mesh::AppendMesh(Mesh& mesh)
{
    //add vertex
    int indexOffset = vertexCoords.size()/3;
    for(auto vertex : mesh.vertexCoords) {
        vertexCoords.push_back(vertex);
    }
    //add index
    for(auto index : mesh.indexBuffer) {
        indexBuffer.push_back(indexOffset + index);
    }
    //add section
    int sectionIndex = indexLenghts.size();
    for (int section = 0; section < mesh.GetSectionCount(); section++) {
        //add primitive
        auto indexMode = mesh.indexModeBuffer.at(section);
        indexModeBuffer.push_back(indexMode);
        vector<int> indexList = mesh.indexSections[section];
        for(auto index : indexList) {
            indexSections[sectionIndex].push_back(indexOffset + index);
        }
        sectionIndex ++;
    }
    for(int indexLenght : mesh.indexLenghts) {
        indexLenghts.push_back(indexLenght);
    }
    UpdatePrimitiveCounts();
    UpdateTriangleList();

}

void Mesh::ApplyTransform(MTransform<float>& transform)
{
    this->localTransform.multiply(transform, localTransform);
    this->dirty = true;
}

void Mesh::ApplyTransforms()
{
    if(dirty) {
        int nvertex= vertexCoords.size();
        //int vertexSize = nvertex/3;
        for(int v = 0; v < nvertex; v+=3) {
            MVector3<float> vertex(vertexCoords[v],vertexCoords[v+1],vertexCoords[v+2]);
            vertex = localTransform.ApplyForward(vertex);
            vertexCoords[v]=vertex.GetX();
            vertexCoords[v+1]=vertex.GetY();
            vertexCoords[v+2]=vertex.GetZ();
        }
        UpdatePrimitiveCounts();
        UpdateTriangleList();
        computeBBox();
        this->localTransform.SetIdentity();
        dirty = false;
    }
}

