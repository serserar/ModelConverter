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

#include "VoxelizerTool.h"
#define VOXELIZER_IMPLEMENTATION
#include "../ext/voxelizer.h"

VoxelizerTool::VoxelizerTool()
{

}

VoxelizerTool::VoxelizerTool ( const VoxelizerTool& other )
{

}

VoxelizerTool::~VoxelizerTool()
{

}


Mesh * VoxelizerTool::Voxelize ( Mesh& mesh, float precision, BBox& voxelSize, bool autoSize, vector<BBox>& voxels )
{
    Mesh* voxelMesh = new Mesh();
    float vwidth = 1.0f;
    float vheight = 1.0f;
    float vdepth = 1.0f;
    if ( autoSize ) {
        MVector3<float> min;
        MVector3<float> max ( vwidth, vheight, vdepth );
        BBox autoVoxel ( min, max );
        voxelSize = autoVoxel;
    } else {
        vwidth = voxelSize.boundMax.GetX()-voxelSize.boundMin.GetX();
        vheight = voxelSize.boundMax.GetY()-voxelSize.boundMin.GetY();
        vdepth = voxelSize.boundMax.GetZ()-voxelSize.boundMin.GetZ();
    }
    int triangleIndex=0;
    for ( auto triangle : mesh.triangleList ) {
        BBox tbbox = BBox::GetBBoxFromTriangle ( triangle );
        for ( float x = tbbox.boundMin.GetX(); x <= tbbox.boundMax.GetX(); x += vwidth ) {
            for ( float y = tbbox.boundMin.GetY(); y <= tbbox.boundMax.GetY(); y += vheight ) {
                for ( float z = tbbox.boundMin.GetZ(); z <= tbbox.boundMax.GetZ(); z += vdepth ) {
                    MVector3<float> bmin ( x-vwidth, y-vheight, z-vdepth );
                    MVector3<float> bmax ( x+vwidth, y+vheight, z+vdepth );
                    BBox voxel ( bmin, bmax );
                    MVector3<float> center = voxel.GetCenter();
                    MVector3<float> halfSize = voxel.GetHalfSize();
                    // precision factor reduces the artifact
                    halfSize += precision;
                    if ( checkIntersection ( triangle, voxel ) ) {
                        //add voxel
                        //std::cout <<"Intersection : " << triangleIndex << std::endl;
                        voxels.push_back ( voxel );
                    }
                }
            }
        }
        //std::cout <<"Index : " << triangleIndex << std::endl;
        triangleIndex++;
    }
    //mesh.vertexCoords.clear();
//    for(auto voxel : voxels){
    //vertex 1
//         mesh.vertexCoords.push_back(voxel.boundMin.GetX());
//         mesh.vertexCoords.push_back(voxel.boundMin.GetY());
//         mesh.vertexCoords.push_back(voxel.boundMin.GetZ());
//         //vertex 2
//         mesh.vertexCoords.push_back(voxel.boundMax.GetX());
//         mesh.vertexCoords.push_back(voxel.boundMax.GetY());
//         mesh.vertexCoords.push_back(voxel.boundMax.GetZ());
//      boundPoint3 = Vector3(boundPoint1.x, boundPoint1.y, boundPoint2.z);
//      boundPoint4 = Vector3(boundPoint1.x, boundPoint2.y, boundPoint1.z);
//      boundPoint5 = Vector3(boundPoint2.x, boundPoint1.y, boundPoint1.z);
//      boundPoint6 = Vector3(boundPoint1.x, boundPoint2.y, boundPoint2.z);
//      boundPoint7 = Vector3(boundPoint2.x, boundPoint1.y, boundPoint2.z);
//      boundPoint8 = Vector3(boundPoint2.x, boundPoint2.y, boundPoint1.z);
//    }
    //delete grid
    return voxelMesh;
}

/*
 mesh.bbox;
    //make a grid
    float width = mesh.bbox.boundMax.GetX()-mesh.bbox.boundMin.GetX();
    float height = mesh.bbox.boundMax.GetY()-mesh.bbox.boundMin.GetY();
    float depth = mesh.bbox.boundMax.GetZ()-mesh.bbox.boundMin.GetZ();
    float vwidth = 0.5f;
    float vheight = 0.5f;
    float vdepth = 0.5f;
    if(autoSize) {
        MVector3<float> min;
        MVector3<float> max(vwidth, vheight, vdepth);
        BBox autoVoxel(min, max);
        voxelSize = autoVoxel;
    } else {
        vwidth = voxelSize.boundMax.GetX()-voxelSize.boundMin.GetX();
        vheight = voxelSize.boundMax.GetY()-voxelSize.boundMin.GetY();
        vdepth = voxelSize.boundMax.GetZ()-voxelSize.boundMin.GetZ();
    }
    int gridWidth = ceil(width/vwidth);
    int gridHeight = ceil(height/vheight);
    int gridDepth = ceil(depth/vdepth);
    BBox*** grid = new BBox**[gridWidth];
    for(int i = 0; i < gridWidth; i++) {
        grid[i]= new BBox*[gridHeight];
        for(int j = 0; j < gridHeight; j++) {
            grid[i][j]=new BBox[gridDepth];
        }
    }
    //loop all mesh triangles
    //check if a voxel intersects with triangle
    float bboxminx=0.0f;
    float bboxminy=0.0f;
    float bboxminz=0.0f;
    float bboxmaxx=vwidth;
    float bboxmaxy=vheight;
    float bboxmaxz=vdepth;
    BBox checkbbox;
    for(auto triangle : mesh.triangleList) {
        for(int i = 0; i < gridWidth; i++) {
            for(int j = 0; j < gridHeight; j++) {
                for(int z = 0; z < gridDepth; z++) {
                    grid[i][j][z].boundMin.SetX(bboxminx);
                    grid[i][j][z].boundMin.SetY(bboxminy);
                    grid[i][j][z].boundMin.SetZ(bboxminz);
                    grid[i][j][z].boundMax.SetX(bboxmaxx);
                    grid[i][j][z].boundMax.SetY(bboxmaxy);
                    grid[i][j][z].boundMax.SetZ(bboxmaxz);
                    if(!checkIntersection(*triangle, grid[i][j][z])) {
                        grid[i][j][z].boundMin.SetX(0.0f);
                        grid[i][j][z].boundMin.SetY(0.0f);
                        grid[i][j][z].boundMin.SetZ(0.0f);
                        grid[i][j][z].boundMax.SetX(0.0f);
                        grid[i][j][z].boundMax.SetY(0.0f);
                        grid[i][j][z].boundMax.SetZ(0.0f);
                    }
                    bboxminz +=vdepth;
                    bboxmaxz +=vdepth;
                }
                bboxminy +=vheight;
                bboxmaxy +=vheight;
            }
            bboxminx +=vwidth;
            bboxmaxx +=vwidth;
        }
    }
 */
bool VoxelizerTool::checkIntersection ( Triangle& triangle, BBox& voxel )
{
    bool intersects = false;
    MVector3<float> vertex0 = triangle.v1;
    MVector3<float> vertex1 = triangle.v2;
    MVector3<float> vertex2 = triangle.v3;
    MVector3<float> edge1, edge2, h, s, q;
//     float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    MVector3<float> normal = edge1.CrossProduct ( edge2 );
    normal.normalize();
    MPlane<float> plane ( normal,vertex0 );
    intersects = voxel.ClassifyPlane ( plane ) ==0;
    if ( intersects ) { //intersects with the plane


    }
    return intersects;
}


Mesh * VoxelizerTool::VoxelixeExt ( Mesh& mesh, int meshIndex, float precision, BBox& voxelSize, bool autoSize, vector<BBox>& voxels )
{

    float vwidth = 0.25f;
    float vheight = 0.25f;
    float vdepth = 0.25f;
    if ( autoSize ) {
        MVector3<float> min;
        MVector3<float> max ( vwidth, vheight, vdepth );
        BBox autoVoxel ( min, max );
        voxelSize = autoVoxel;
    } else {
        vwidth = voxelSize.boundMax.GetX()-voxelSize.boundMin.GetX();
        vheight = voxelSize.boundMax.GetY()-voxelSize.boundMin.GetY();
        vdepth = voxelSize.boundMax.GetZ()-voxelSize.boundMin.GetZ();
    }
    int indexLenght = 0;
    vector<Triangle> triangleList;
    mesh.ConvertToTriangles(triangleList);
    vx_mesh_t* mesh_t;
    //mesh_t = vx_mesh_alloc ( mesh.vertexCoords.size(), triangleList.size()*3);
    mesh_t = vx_mesh_alloc ( triangleList.size()*9, triangleList.size()*3);
    //copy indexBuffer
    for ( auto triangle : triangleList) {
        mesh_t->indices[indexLenght] = triangle.vindex1;
        mesh_t->indices[indexLenght+1] = triangle.vindex2;
        mesh_t->indices[indexLenght+2] = triangle.vindex3;
        if(triangle.vindex1 ==  triangle.vindex2 || triangle.vindex1 ==  triangle.vindex3 ||triangle.vindex2 ==  triangle.vindex3) {
            std::cout << "Degenerate "  << std::endl;
        }
        mesh_t->vertices[indexLenght].x = triangle.v1.GetX();
        mesh_t->vertices[indexLenght].y = triangle.v1.GetY();
        mesh_t->vertices[indexLenght].z = triangle.v1.GetZ();
        mesh_t->vertices[indexLenght+1].x = triangle.v2.GetX();
        mesh_t->vertices[indexLenght+1].y = triangle.v2.GetY();
        mesh_t->vertices[indexLenght+1].z = triangle.v2.GetZ();
        mesh_t->vertices[indexLenght+2].x = triangle.v3.GetX();
        mesh_t->vertices[indexLenght+2].y = triangle.v3.GetY();
        mesh_t->vertices[indexLenght+2].z = triangle.v3.GetZ();
        indexLenght+=3;
    }

//     for ( int v =0; v < mesh.vertexCoords.size()/3; v++) {
//         mesh_t->vertices[v].x = mesh.vertexCoords[v*3];
//         mesh_t->vertices[v].y = mesh.vertexCoords[v*3+1];
//         mesh_t->vertices[v].z = mesh.vertexCoords[v*3+2];
//     }

//OK
//     mesh_t = vx_mesh_alloc ( mesh.vertexCoords.size(), mesh.indexBuffer.size());
//     //copy indexBuffer
//     for ( size_t f = 0; f < mesh.indexBuffer.size(); f++ ) {
//         mesh_t->indices[f] = mesh.indexBuffer[f];
//     }
//     for ( int v =0; v < mesh.vertexCoords.size()/3; v++) {
//         mesh_t->vertices[v].x = mesh.vertexCoords[v*3];
//         mesh_t->vertices[v].y = mesh.vertexCoords[v*3+1];
//         mesh_t->vertices[v].z = mesh.vertexCoords[v*3+2];
//     }
//
    std::cout << "indexLenght " << indexLenght << std::endl;
    //vx_mesh_t* result = vx_voxelize ( mesh_t, vwidth, vheight, vdepth, precision );
    vx_mesh_t* result = mesh_t;
    string destName = "mesh_voxelized_res_";
    std::stringstream destFilePath;
    destFilePath << destName<< meshIndex << ".obj" ;
    std::ofstream file(destFilePath.str());
    printf ( "Number of vertices: %ld\n", result->nvertices );
    printf ( "Number of indices: %ld\n", result->nindices );
    size_t voffset = 0;
    size_t noffset = 0;
    if ( file.is_open() ) {
        file << "\n";
        file << "o " << meshIndex << "\n";

        for ( int j = 0; j < result->nvertices; ++j ) {
            file << "v " << result->vertices[j].x << " "
                 << result->vertices[j].y << " "
                 << result->vertices[j].z << "\n";
        }

        for ( int j = 0; j < result->nnormals; ++j ) {
            file << "vn " << result->normals[j].x << " "
                 << result->normals[j].y << " "
                 << result->normals[j].z << "\n";
        }

        size_t max = 0;

        for ( int j = 0; j < result->nindices; j += 3 ) {
            size_t i0 = voffset + result->indices[j+0] + 1;
            size_t i1 = voffset + result->indices[j+1] + 1;
            size_t i2 = voffset + result->indices[j+2] + 1;

            max = i0 > max ? i0 : max;
            max = i1 > max ? i1 : max;
            max = i2 > max ? i2 : max;

            file << "f ";

            file << i0 << "//" << result->normalindices[j+0] + noffset + 1 << " ";
            file << i1 << "//" << result->normalindices[j+1] + noffset + 1 << " ";
            file << i2 << "//" << result->normalindices[j+2] + noffset + 1 << "\n";
        }

        voffset += max;
        noffset += 6;
    }

    vx_mesh_free ( result );
    //vx_mesh_free ( mesh_t );
}


void VoxelizerTool::WriteOBJModel(Mesh& mesh, string destFilePath)
{

    int indexLenght = 0;
    vector<Triangle> triangleList;
    mesh.ConvertToTriangles(triangleList);
    vx_mesh_t* mesh_t;
    //mesh_t = vx_mesh_alloc ( mesh.vertexCoords.size(), triangleList.size()*3);
    mesh_t = vx_mesh_alloc ( triangleList.size()*9, triangleList.size()*3);
    //copy indexBuffer
    for ( auto triangle : triangleList) {
        mesh_t->indices[indexLenght] = triangle.vindex1;
        mesh_t->indices[indexLenght+1] = triangle.vindex2;
        mesh_t->indices[indexLenght+2] = triangle.vindex3;
        if(triangle.vindex1 ==  triangle.vindex2 || triangle.vindex1 ==  triangle.vindex3 ||triangle.vindex2 ==  triangle.vindex3) {
            std::cout << "Degenerate "  << std::endl;
        }
        mesh_t->vertices[indexLenght].x = triangle.v1.GetX();
        mesh_t->vertices[indexLenght].y = triangle.v1.GetY();
        mesh_t->vertices[indexLenght].z = triangle.v1.GetZ();
        mesh_t->vertices[indexLenght+1].x = triangle.v2.GetX();
        mesh_t->vertices[indexLenght+1].y = triangle.v2.GetY();
        mesh_t->vertices[indexLenght+1].z = triangle.v2.GetZ();
        mesh_t->vertices[indexLenght+2].x = triangle.v3.GetX();
        mesh_t->vertices[indexLenght+2].y = triangle.v3.GetY();
        mesh_t->vertices[indexLenght+2].z = triangle.v3.GetZ();
        indexLenght+=3;
    }
    std::cout << "indexLenght " << indexLenght << std::endl;
    //vx_mesh_t* result = vx_voxelize ( mesh_t, vwidth, vheight, vdepth, precision );
    vx_mesh_t* result = mesh_t;
    std::ofstream file(destFilePath);
    printf ( "Number of vertices: %ld\n", result->nvertices );
    printf ( "Number of indices: %ld\n", result->nindices );
    size_t voffset = 0;
    size_t noffset = 0;
    if ( file.is_open() ) {
        file << "\n";
        file << "o " << destFilePath << "\n";

        for ( int j = 0; j < result->nvertices; ++j ) {
            file << "v " << result->vertices[j].x << " "
                 << result->vertices[j].y << " "
                 << result->vertices[j].z << "\n";
        }

        for ( int j = 0; j < result->nnormals; ++j ) {
            file << "vn " << result->normals[j].x << " "
                 << result->normals[j].y << " "
                 << result->normals[j].z << "\n";
        }

        size_t max = 0;

        for ( int j = 0; j < result->nindices; j += 3 ) {
            size_t i0 = voffset + result->indices[j+0] + 1;
            size_t i1 = voffset + result->indices[j+1] + 1;
            size_t i2 = voffset + result->indices[j+2] + 1;

            max = i0 > max ? i0 : max;
            max = i1 > max ? i1 : max;
            max = i2 > max ? i2 : max;

            file << "f ";

            file << i0 << "//" << result->normalindices[j+0] + noffset + 1 << " ";
            file << i1 << "//" << result->normalindices[j+1] + noffset + 1 << " ";
            file << i2 << "//" << result->normalindices[j+2] + noffset + 1 << "\n";
        }

        voffset += max;
        noffset += 6;
    }

    vx_mesh_free ( result );
}
