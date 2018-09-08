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
 */

#include "MeshUtils.h"

MeshUtils::MeshUtils()
{

}

MeshUtils::MeshUtils ( const MeshUtils& other )
{

}

MeshUtils::~MeshUtils()
{

}


BBox* MeshUtils::buildBBox ( Mesh& mesh )
{
    BBox* bbox = new BBox();
    //iterate over all vertex in the mesh
    //take minx, miny, minz, maxx, maxy and maxz
    float x,y,z = 0.0f;
    MVector3<float> min,max;
    for ( int i = 0; i < mesh.vertexCoords.size(); i+=3 ) {
        x=mesh.vertexCoords.at ( i );
        y=mesh.vertexCoords.at ( i+1 );
        z=mesh.vertexCoords.at ( i+2 );
        if ( x < bbox->boundMin.GetX() ) bbox->boundMin.SetX ( x );
        if ( y < bbox->boundMin.GetY() ) bbox->boundMin.SetY ( y );
        if ( z < bbox->boundMin.GetZ() ) bbox->boundMin.SetZ ( z );
        if ( x > bbox->boundMax.GetX() ) bbox->boundMax.SetX ( x );
        if ( y > bbox->boundMax.GetY() ) bbox->boundMax.SetY ( y );
        if ( z > bbox->boundMax.GetZ() ) bbox->boundMax.SetZ ( z );
    }

    return bbox;
}

MVector3<float> MeshUtils::GetBaryCentricCoords ( Triangle& triangle, MVector3<float>& pointInside )
{
    MVector3<float> bcoords;
    MVector3<float> vertex0 = triangle.v1;
    MVector3<float> vertex1 = triangle.v2;
    MVector3<float> vertex2 = triangle.v3;
    MVector3<float> edge1, edge2;
//     float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    // Compute vectors
    MVector3<float> v2 = pointInside - vertex0;
    // Compute dot products
    float dot00 = edge2.dotProduct ( edge2 );
    float dot01 = edge2.dotProduct ( edge1 );
    float dot02 = edge2.dotProduct ( v2 );
    float dot11 = edge1.dotProduct ( edge1 );
    float dot12 = edge1.dotProduct ( v2 );

    // Compute barycentric coordinates
    float invDenom = 1 / ( dot00 * dot11 - dot01 * dot01 );
    float u = ( dot11 * dot02 - dot01 * dot12 ) * invDenom;
    float v = ( dot00 * dot12 - dot01 * dot02 ) * invDenom;
    float w = 1 - u - v;
    bcoords.SetX ( u );
    bcoords.SetY ( v );
    bcoords.SetZ ( w );
    return bcoords;
}

Mesh * MeshUtils::buildMeshFromSkeleton ( Skeleton& skeleton, float size )
{
    Mesh* skeletonMesh = new Mesh();
    for ( auto joint : skeleton.joints ) {
        Cube cube(5*size, 5*size, 5*size, *joint->GetPosition());
        skeletonMesh->AppendMesh(cube);
    }



    // Draw each bone
    for ( auto joint : skeleton.joints ) {
        if ( joint->GetParent() != -1 ) {
            
            MVector3<float> bone ( joint->GetPosition()->GetX(),
                                   joint->GetPosition()->GetY(),
                                   joint->GetPosition()->GetZ() );
            MVector3<float> parentBone ( skeleton.joints[joint->GetParent()]->GetPosition()->GetX(),
                                         skeleton.joints[joint->GetParent()]->GetPosition()->GetY(),
                                         skeleton.joints[joint->GetParent()]->GetPosition()->GetZ() );
            MVector3<float> pointFront;
            MVector3<float> pointBack;
            if(bone.GetZ() >= parentBone.GetZ()){
                pointFront = bone;
                pointBack = parentBone;
                std::cout << "pointFront = " << joint->GetName() << endl;
                std::cout << "pointBack = " <<  skeleton.joints[joint->GetParent()]->GetName() << endl;
            }else{
                pointFront = parentBone;
                pointBack = bone;
                std::cout << "pointFront = " <<  skeleton.joints[joint->GetParent()]->GetName() << endl;
                std::cout << "pointBack = " << joint->GetName() << endl;
            }
            RectangularPrism rectangularPrism(pointFront, pointBack, size);
            skeletonMesh->AppendMesh(rectangularPrism);
        }
    }
    return skeletonMesh;
}
