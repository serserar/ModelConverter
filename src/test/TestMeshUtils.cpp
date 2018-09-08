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

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../base/Skeleton.h"
#include "../base/Joint.h"
#include "../base/MeshUtils.h"
#include "../base/VoxelizerTool.h"
#include "../base/Cube.h"
#include "../mdl/MDLReader.h"
#include "../base/MDLImporter.h"
#include "../base/Camera.h"
#include "../base/Ray.h"
#include "../util/ImageUtils.h"
#include "../image/PPMReader.h"

using namespace std;

TEST_CASE ( "Test Resize to Camera Frustum" )
{

    MVector3<float> ccenter;
    Cube cube ( 100.0f, 100.0f, 100.0f, ccenter );
    float width=160;
    float height=120;
    MVector3<float> eye ( 0.0f,0.0f, 26.0f );
    MVector3<float> up ( 0.0f,1.0f,0.0f );
    MVector3<float> center ( 0.0f,0.0f, -1.0f );
    Camera cam ( width, height, eye, up, center, 1.0f, 100.0f, 57.82f, 45.0f );
    float bwidth = cube.bbox.GetWidth();
    float bheight = cube.bbox.GetHeight();
    float bdepth = cube.bbox.GetDepth();
    //scale
    //get camera max
    BBox modelBox = cube.bbox;
    float cubeSize = 16;
    float camMax = cam.GetWidthZ (cam.GetNormalizedZ(cubeSize) );
    float camMay = cam.GetHeightZ (cam.GetNormalizedZ(cubeSize) );
    float rwidth = cam.GetWidthZ (cam.GetNormalizedZ(cubeSize/2) );
    float rheight = cam.GetHeightZ (cam.GetNormalizedZ(cubeSize/2) );
    BBox boxToResize;
    float nWidth = camMax;
    float nHeight  = camMay;
    float nDepth = 0;
    if(camMax > camMay) {
        nWidth = camMay;
        nHeight = camMay;
        nDepth = camMay;
    } else {
        nWidth = camMax;
        nHeight = camMax;
        nDepth = camMax;
    }
    float scaleWidth = cubeSize / bwidth;
    float scaleHeight = cubeSize  / bheight;
    float scaleDepth = cubeSize  / bdepth;
    MVector3<float> scale(scaleWidth, scaleHeight , scaleDepth);

    MTransform<float> scaleTransform;
    scaleTransform.SetScale ( scale );

    cube.ApplyTransform ( scaleTransform );
    cube.ApplyTransforms();
    float new_width = cube.bbox.GetWidth();
    float new_height = cube.bbox.GetHeight();
    float new_depth = cube.bbox.GetDepth();
    Image* img_resized = ImageUtils::Snapshot ( cam, cube );
    PPMReader writer;
    writer.writePGM5 ( "cube_resized.ppm",*img_resized );
    delete img_resized;
    SECTION ( "Check Resize to box" ) {
        INFO ( "Check Resize to box" );
        REQUIRE ( bwidth==new_width);
        REQUIRE ( bheight==new_height );
        REQUIRE ( bdepth==new_depth );
    }

}

TEST_CASE ( "Test Resize to box" )
{

    MVector3<float> ccenter;
    Cube cube ( 5.0f, 5.0f, 5.0f, ccenter );
    Cube cubeToResize ( 1.0f, 1.0f, 1.0f, ccenter );
    BBox resize = cube.bbox;
    BBox toResize = cubeToResize.bbox;
    float scaleWidth = toResize.GetWidth() /resize.GetWidth();
    float scaleHeight = toResize.GetHeight() /resize.GetHeight();
    float scaleDepth = toResize.GetDepth() /resize.GetDepth();
    MVector3<float> scaleVector ( scaleWidth, scaleHeight, scaleDepth );
    MTransform<float> transform;
    transform.SetScale ( scaleVector );
    cube.ApplyTransform ( transform );
    cube.ApplyTransforms();
    float nwidth = cube.bbox.GetWidth();
    float nheight = cube.bbox.GetHeight();
    float ndepth = cube.bbox.GetDepth();
    SECTION ( "Check Resize to box" ) {
        INFO ( "Check Resize to box" );
        REQUIRE ( nwidth==toResize.GetWidth() );
        REQUIRE ( nheight==toResize.GetHeight() );
        REQUIRE ( ndepth==toResize.GetDepth() );
    }

}

TEST_CASE ( "Test SkeletonMesh Animated with rotation" )
{

    MDLReader mreader;
    MDLModel* mdlmodel =  mreader.readModel ( "../samples/eightball.mdl" );
    MDLImporter mdlImporter;
    VoxelizerTool voxelizer;
    //transform from left handed to right handed
    MVector3<float> axisrotation ( -Math<float>::PI/2,Math<float>::PI/2,0 );
    MTransform<float> rotationTransform;
    rotationTransform.SetRotation ( axisrotation );
    AnimatedModel* model = mdlImporter.Convert ( *mdlmodel );
    auto animit = model->GetBeginAnimationIterator();
    auto animendIt = model->GetEndAnimationIterator();
    while ( animit!=animendIt ) {
        Animation anim = **animit;
        string destName = "mesh_voxelized_animated_rotated_res_";
        int meshIndex = 0;
        int frameSize = anim.GetFrameSize();
        model->setAnimation ( anim.GetName() );
        model->OnUpdate ( 1 );
        auto it = model->GetBeginMeshIterator();
        auto endIt = model->GetEndMeshIterator();
        Mesh modelMesh;
        while ( it!=endIt ) {
            std::stringstream destFilePath;
            destFilePath << destName << anim.GetName() << meshIndex << ".obj";
            modelMesh = **it;
            modelMesh.ApplyTransform ( rotationTransform );
            modelMesh.ApplyTransforms();
            voxelizer.WriteOBJModel ( modelMesh, destFilePath.str() );
            meshIndex++;
            ++it;
        }
        Skeleton* skeleton = model->GetSkeleton();
        float size = 0.2f;
        Mesh* mesh = MeshUtils::buildMeshFromSkeleton ( *skeleton, size );
        mesh->ApplyTransform ( rotationTransform );
        mesh->ApplyTransforms();
        voxelizer.WriteOBJModel ( *mesh, "skeletonModel_animated_rotated.obj" );
        delete mesh;
        animit++;
    }
    SECTION ( "Check SkeletonMesh" ) {
        INFO ( "Check SkeletonMesh" );
        REQUIRE ( 1==1 );
    }


}


TEST_CASE ( "Test SkeletonMesh with rotation" )
{

    MDLReader mreader;
    MDLModel* mdlmodel =  mreader.readModel ( "../samples/eightball.mdl" );
    MDLImporter mdlImporter;
    VoxelizerTool voxelizer;
    //transform from left handed to right handed
    MVector3<float> axisrotation ( -Math<float>::PI/2,Math<float>::PI/2,0 );
    MTransform<float> rotationTransform;
    rotationTransform.SetRotation ( axisrotation );
    AnimatedModel* model = mdlImporter.Convert ( *mdlmodel );
    string destName = "mesh_voxelized_rotated_res_";
    int meshIndex = 0;
    auto it = model->GetBeginMeshIterator();
    auto endIt = model->GetEndMeshIterator();
    Mesh modelMesh;
    while ( it!=endIt ) {
        std::stringstream destFilePath;
        destFilePath << destName<< meshIndex << ".obj";
        modelMesh = **it;
        modelMesh.ApplyTransform ( rotationTransform );
        modelMesh.ApplyTransforms();
        voxelizer.WriteOBJModel ( modelMesh, destFilePath.str() );
        meshIndex++;
        ++it;
    }
    Skeleton* skeleton = model->GetSkeleton();
    float size = 0.2f;
    Mesh* mesh = MeshUtils::buildMeshFromSkeleton ( *skeleton, size );
    mesh->ApplyTransform ( rotationTransform );
    mesh->ApplyTransforms();
    voxelizer.WriteOBJModel ( *mesh, "skeletonModel_rotated.obj" );
    delete mesh;
    SECTION ( "Check SkeletonMesh" ) {
        INFO ( "Check SkeletonMesh" );
        REQUIRE ( 1==1 );
    }


}

TEST_CASE ( "Test mesh intersection" )
{
    MVector3<float> ccenter;
    Cube cube ( 5.0f, 5.0f, 5.0f, ccenter );
    MTransform<float> transform;
    transform.SetScale ( 10.0f );
    Ray ray;
    MVector3<float> rorigin ( 0.0f, 0.0f, 20.0f );
    MVector3<float> rdirection ( 0.0f, 0.0f, -1.0f );
    MVector3<float>intersectionPoint ( 0.0f, 0.0f, -100000.0f );
    if ( cube.intersect ( rorigin, rdirection, intersectionPoint ) ) {
        cout << intersectionPoint << endl;
    }
    MVector3<float> result ( 0.0f, 0.0f, 2.5f );
    SECTION ( "Check mesh scale" ) {
        INFO ( "Check mesh scale" );
        REQUIRE ( intersectionPoint==result );
    }
}

TEST_CASE ( "Test mesh intersection scaled" )
{
    MVector3<float> ccenter;
    Cube cube ( 5.0f, 5.0f, 5.0f, ccenter );
    MTransform<float> transform;
    transform.SetScale ( 10.0f );
    cube.ApplyTransform ( transform );
    cube.ApplyTransforms();
    Ray ray;
    MVector3<float> rorigin ( 0.0f, 0.0f, 30.0f );
    MVector3<float> rdirection ( 0.0f, 0.0f, -1.0f );
    MVector3<float>intersectionPoint ( 0.0f, 0.0f, -100000.0f );
    if ( cube.intersect ( rorigin, rdirection, intersectionPoint ) ) {
        cout << intersectionPoint << endl;
    }
    MVector3<float> result ( 0.0f, 0.0f, 25.0f );
    SECTION ( "Check mesh scale" ) {
        INFO ( "Check mesh scale" );
        REQUIRE ( intersectionPoint==result );
    }
}

TEST_CASE ( "Test mesh rotation" )
{
    PPMReader writer;
    VoxelizerTool voxelizer;
    MVector3<float> ccenter;
    Cube cube ( 5.0f, 5.0f, 5.0f, ccenter );
    float width=160;
    float height=120;
    MVector3<float> eye ( 0.0f,0.0f, 26.0f );
    MVector3<float> up ( 0.0f,1.0f,0.0f );
    MVector3<float> center ( 0.0f,0.0f, -1.0f );
    Camera cam ( width, height, eye, up, center, 1.0f, 100.0f, 57.82f, 45.0f );
    //transform from left handed to right handed
    MVector3<float> axisrotation ( Math<float>::PI/4,0,0 );
    MTransform<float> rotationTransform;
    rotationTransform.SetRotation ( axisrotation );
    cube.ApplyTransform ( rotationTransform );
    cube.ApplyTransforms();
    voxelizer.WriteOBJModel ( cube, "cube_rotated.obj" );
    Image* img_rotated = ImageUtils::Snapshot ( cam, cube );
    writer.writePGM5 ( "cube_rotated.ppm",*img_rotated );
    delete img_rotated;
    SECTION ( "Check mesh scale" ) {
        INFO ( "Check mesh scale" );
        REQUIRE ( 1==1 );
    }
}

TEST_CASE ( "Test mesh scale" )
{
    PPMReader writer;
    VoxelizerTool voxelizer;
    MVector3<float> ccenter;
    Cube cube ( 10.0f, 10.0f, 10.0f, ccenter );
    float width=160;
    float height=120;
    MVector3<float> eye ( 0.0f,0.0f, 26.0f );
    MVector3<float> up ( 0.0f,1.0f,0.0f );
    MVector3<float> center ( 0.0f,0.0f, -1.0f );
    Camera cam ( width, height, eye, up, center, 1.0f, 100.0f, 57.82f, 45.0f );
    Image* img = ImageUtils::Snapshot ( cam, cube );
    writer.writePGM5 ( "cube.ppm",*img );
    delete img;
    voxelizer.WriteOBJModel ( cube, "cube.obj" );
    MTransform<float> transform;
    transform.SetScale ( 10.0f );
    cube.ApplyTransform ( transform );
    cube.ApplyTransforms();
    voxelizer.WriteOBJModel ( cube, "cube_scaled.obj" );
    Image* img_scaled = ImageUtils::Snapshot ( cam, cube );
    writer.writePGM5 ( "cube_scaled.ppm",*img_scaled );
    delete img_scaled;
    SECTION ( "Check mesh scale" ) {
        INFO ( "Check mesh scale" );
        REQUIRE ( 1==1 );
    }
}

TEST_CASE ( "Test MeshUtils" )
{

    Skeleton skeleton;
    //root joint
    Joint* root = new Joint ( "root" );
    root->SetParent ( -1 );
    root->SetIndex ( 0 );
    root->SetPosition ( new MVector3<float> ( 0,0,3 ) );
    skeleton.parentJoint=root;
    skeleton.joints.push_back ( root );
    //pelvis joint
    Joint* pelvisJoint = new Joint();
    pelvisJoint->SetName ( "pelvis" );
    pelvisJoint->SetParent ( 0 );
    pelvisJoint->SetIndex ( 1 );
    pelvisJoint->SetPosition ( new MVector3<float> ( 0,-5,3 ) );
    skeleton.joints.push_back ( pelvisJoint );
    //leftLeg1Joint
    Joint* leftLeg1Joint = new Joint();
    leftLeg1Joint->SetName ( "leftleg1" );
    leftLeg1Joint->SetParent ( 1 );
    leftLeg1Joint->SetIndex ( 2 );
    leftLeg1Joint->SetPosition ( new MVector3<float> ( -3,-6,3 ) );
    skeleton.joints.push_back ( leftLeg1Joint );
    //leftLeg2Joint
    Joint* leftLeg2Joint = new Joint();
    leftLeg2Joint->SetName ( "leftleg2" );
    leftLeg2Joint->SetParent ( 2 );
    leftLeg2Joint->SetIndex ( 3 );
    leftLeg2Joint->SetPosition ( new MVector3<float> ( -3,-10,3 ) );
    skeleton.joints.push_back ( leftLeg2Joint );
    //leftLeg3Joint
    Joint* leftLeg3Joint = new Joint();
    leftLeg3Joint->SetName ( "leftleg3" );
    leftLeg3Joint->SetParent ( 3 );
    leftLeg3Joint->SetIndex ( 4 );
    leftLeg3Joint->SetPosition ( new MVector3<float> ( -3,-15,3 ) );
    skeleton.joints.push_back ( leftLeg3Joint );
    //leftfoot
    Joint* leftfootJoint = new Joint();
    leftfootJoint->SetName ( "leftfoot" );
    leftfootJoint->SetParent ( 4 );
    leftfootJoint->SetIndex ( 5 );
    leftfootJoint->SetPosition ( new MVector3<float> ( -6,-16,6 ) );
    skeleton.joints.push_back ( leftfootJoint );

    //rightLeg1Joint
    Joint* rightLeg1Joint = new Joint();
    rightLeg1Joint->SetName ( "rightleg1" );
    rightLeg1Joint->SetParent ( 1 );
    rightLeg1Joint->SetIndex ( 6 );
    rightLeg1Joint->SetPosition ( new MVector3<float> ( 3,-6,3 ) );
    skeleton.joints.push_back ( rightLeg1Joint );
    //rightLeg2Joint
    Joint* rightLeg2Joint = new Joint();
    rightLeg2Joint->SetName ( "rightleg2" );
    rightLeg2Joint->SetParent ( 6 );
    rightLeg2Joint->SetIndex ( 7 );
    rightLeg2Joint->SetPosition ( new MVector3<float> ( 3,-10,3 ) );
    skeleton.joints.push_back ( rightLeg2Joint );
    //rightLeg3Joint
    Joint* rightLeg3Joint = new Joint();
    rightLeg3Joint->SetName ( "rightleg3" );
    rightLeg3Joint->SetParent ( 7 );
    rightLeg3Joint->SetIndex ( 8 );
    rightLeg3Joint->SetPosition ( new MVector3<float> ( 3,-15,3 ) );
    skeleton.joints.push_back ( rightLeg3Joint );
    //rightfoot
    Joint* rightfootJoint = new Joint();
    rightfootJoint->SetName ( "rightfoot" );
    rightfootJoint->SetParent ( 8 );
    rightfootJoint->SetIndex ( 9 );
    rightfootJoint->SetPosition ( new MVector3<float> ( 6,-16, 6 ) );
    skeleton.joints.push_back ( rightfootJoint );

    //neckJoint
    Joint* neckJoint = new Joint();
    neckJoint->SetName ( "neck" );
    neckJoint->SetParent ( 0 );
    neckJoint->SetIndex ( 10 );
    neckJoint->SetPosition ( new MVector3<float> ( 0,5,3 ) );
    skeleton.joints.push_back ( neckJoint );

    //headJoint
    Joint* headJoint = new Joint();
    headJoint->SetName ( "head" );
    headJoint->SetParent ( 10 );
    headJoint->SetIndex ( 11 );
    headJoint->SetPosition ( new MVector3<float> ( 0,8,3 ) );
    skeleton.joints.push_back ( headJoint );

    //leftShoulderJoint
    Joint* leftShoulderJoint = new Joint();
    leftShoulderJoint->SetName ( "leftShoulder" );
    leftShoulderJoint->SetParent ( 10 );
    leftShoulderJoint->SetIndex ( 12 );
    leftShoulderJoint->SetPosition ( new MVector3<float> ( -3,4,3 ) );
    skeleton.joints.push_back ( leftShoulderJoint );

    //leftarm1Joint
    Joint* leftarm1Joint = new Joint();
    leftarm1Joint->SetName ( "leftarm1" );
    leftarm1Joint->SetParent ( 12 );
    leftarm1Joint->SetIndex ( 13 );
    leftarm1Joint->SetPosition ( new MVector3<float> ( -3,0,3 ) );
    skeleton.joints.push_back ( leftarm1Joint );

    //lefhandJoint
    Joint* lefhandJoint = new Joint();
    lefhandJoint->SetName ( "lefhand" );
    lefhandJoint->SetParent ( 13 );
    lefhandJoint->SetParent ( 13 );
    lefhandJoint->SetIndex ( 14 );
    lefhandJoint->SetPosition ( new MVector3<float> ( -3,-3,3 ) );
    skeleton.joints.push_back ( lefhandJoint );

    //rightShoulderJoint
    Joint* rightShoulderJoint = new Joint();
    rightShoulderJoint->SetName ( "rightShoulder" );
    rightShoulderJoint->SetParent ( 10 );
    rightShoulderJoint->SetIndex ( 15 );
    rightShoulderJoint->SetPosition ( new MVector3<float> ( 3,4,3 ) );
    skeleton.joints.push_back ( rightShoulderJoint );

    //righttarm1Joint
    Joint* righttarm1Joint = new Joint();
    righttarm1Joint->SetName ( "righttarm1" );
    righttarm1Joint->SetParent ( 15 );
    righttarm1Joint->SetIndex ( 16 );
    righttarm1Joint->SetPosition ( new MVector3<float> ( 3,0,3 ) );
    skeleton.joints.push_back ( righttarm1Joint );

    //righthandJoint
    Joint* righthandJoint = new Joint();
    righthandJoint->SetName ( "righthand" );
    righthandJoint->SetParent ( 16 );
    righthandJoint->SetIndex ( 17 );
    righthandJoint->SetPosition ( new MVector3<float> ( 3,-3,3 ) );
    skeleton.joints.push_back ( righthandJoint );
    float size = 0.2f;
    Mesh* mesh = MeshUtils::buildMeshFromSkeleton ( skeleton, size );
    SECTION ( "Check Ray intersection" ) {
        INFO ( "Check Ray intersection" );
        REQUIRE ( 1==1 );
    }


}


TEST_CASE ( "Test SkeletonMesh" )
{

    MDLReader mreader;
    MDLModel* mdlmodel =  mreader.readModel ( "../samples/eightball.mdl" );
    MDLImporter mdlImporter;
    VoxelizerTool voxelizer;
    AnimatedModel* model = mdlImporter.Convert ( *mdlmodel );
    string destName = "mesh_voxelized_res_";
    int meshIndex = 0;
    auto it = model->GetBeginMeshIterator();
    auto endIt = model->GetEndMeshIterator();
    while ( it!=endIt ) {
        std::stringstream destFilePath;
        destFilePath << destName<< meshIndex << ".obj";
        voxelizer.WriteOBJModel ( **it, destFilePath.str() );
        meshIndex++;
        ++it;
    }
    Skeleton* skeleton = model->GetSkeleton();
    float size = 0.2f;
    Mesh* mesh = MeshUtils::buildMeshFromSkeleton ( *skeleton, size );
    voxelizer.WriteOBJModel ( *mesh, "skeletonModel.obj" );

    SECTION ( "Check SkeletonMesh" ) {
        INFO ( "Check SkeletonMesh" );
        REQUIRE ( 1==1 );
    }


}


TEST_CASE ( "Test SkeletonSnapshot" )
{

    MDLReader mreader;
    MDLModel* mdlmodel =  mreader.readModel ( "../samples/eightball.mdl" );
    MDLImporter mdlImporter;
    AnimatedModel* model = mdlImporter.Convert ( *mdlmodel );
    Skeleton* skeleton = model->GetSkeleton();
    float size = 0.2f;
    Mesh* mesh = MeshUtils::buildMeshFromSkeleton ( *skeleton, size );

    VoxelizerTool voxelizer;
    float width=256;
    float height=256;
    MVector3<float> eye ( 0.0f,0.0f, 80.0f );
    MVector3<float> up ( 0.0f,1.0f,0.0f );
    MVector3<float> center ( 0.0f,0.0f, -1.0f );
    Camera cam ( width, height, eye, up, center, 0.1f, 100.0f, 57.82f, 45.0f );
    Image* img = ImageUtils::Snapshot ( cam, *mesh );
    PPMReader writer;
    writer.writePGM5 ( "skeleton.ppm",*img );
    delete img;

    SECTION ( "Check SkeletonSnapshot" ) {
        INFO ( "Check SkeletonSnapshot" );
        REQUIRE ( 1==1 );
    }


}

TEST_CASE ( "Test SkeletonSnapshot2" )
{

    MDLReader mreader;
    MDLModel* mdlmodel =  mreader.readModel ( "../samples/eightball.mdl" );
    MDLImporter mdlImporter;
    AnimatedModel* model = mdlImporter.Convert ( *mdlmodel );
    Skeleton* skeleton = model->GetSkeleton();
    float size = 0.2f;
    Mesh* mesh = MeshUtils::buildMeshFromSkeleton ( *skeleton, size );

    VoxelizerTool voxelizer;
    float width=256;
    float height=256;
    MVector3<float> eye ( 0.0f,-50.0f, 80.0f );
    MVector3<float> up ( 0.0f,1.0f,0.0f );
    MVector3<float> center ( 0.0f, 1.0f, 0.0f );
    Camera cam ( width, height, eye, up, center, 0.1f, 100.0f, 57.82f, 45.0f );
    Image* img = ImageUtils::Snapshot ( cam, *mesh, true );
    PPMReader writer;
    writer.writePGM5 ( "skeleton2.ppm",*img );
    delete img;

    SECTION ( "Check SkeletonSnapshot" ) {
        INFO ( "Check SkeletonSnapshot" );
        REQUIRE ( 1==1 );
    }


}



// TEST_CASE( "Test Snapshot" ) {
//
//     MDLReader mreader;
//     MDLModel* mdlmodel =  mreader.readModel("../samples/eightball.mdl");
//     MDLImporter mdlImporter;
//     AnimatedModel* model = mdlImporter.Convert(*mdlmodel);
//     Skeleton* skeleton = model->GetSkeleton();
//     Mesh* mesh = MeshUtils::buildMeshFromSkeleton(*skeleton);
//
//     VoxelizerTool voxelizer;
//     BBox size;
//     std::vector<BBox> voxelList;
//     float width=256;
//     float height=256;
//     MVector3<float> eye ( 0.0f,0.0f, 100.0f );
//     MVector3<float> up ( 0.0f,1.0f,0.0f );
//     MVector3<float> center ( 0.0f,0.0f, -1.0f );
//     Camera cam( width, height, eye, up, center, 0.5f, 6.0f, 57.82f, 45.0f );
//     std::vector<Ray> rayList;
//     std::vector<Image*> imageList;
//     ImageUtils::Snapshot ( cam, *model, rayList, 0, imageList);
//     PPMReader writer;
//     int index = 0;
//     for(Image* img : imageList) {
//         std::stringstream ss;
//         ss << "output" << index << ".ppm";
//         writer.writePGM5 ( ss.str(),*img );
//         index++;
//         delete img;
//     }
//
//     SECTION( "Check SkeletonMesh" ) {
//         INFO("Check SkeletonMesh");
//         REQUIRE( 1==1 );
//     }
//
//
// }
