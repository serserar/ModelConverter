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

#include "ImageUtils.h"

ImageUtils::ImageUtils()
{

}

ImageUtils::ImageUtils ( const ImageUtils& other )
{

}

ImageUtils::~ImageUtils()
{

}

void ImageUtils::Snapshot ( Camera& camera, AnimatedModel& model, vector<Ray>& rayList, int type, vector<Image*>& imageList )
{
    Image* modelImage = new Image ( Image::GRAYSCALE, Image::UNSIGNED_BYTE, camera.GetWidth(), camera.GetHeight() );
    modelImage->setPixelData ( new unsigned char[camera.GetWidth() * camera.GetHeight()] );
    Image* skeletonImage = nullptr;
    Mesh* skeletonMesh = nullptr;
    float size = 0.2f;
    if ( model.GetCurrentPose() ) {
        skeletonImage = new Image ( Image::GRAYSCALE, Image::UNSIGNED_BYTE, camera.GetWidth(), camera.GetHeight() );
        skeletonImage->setPixelData ( new unsigned char[camera.GetWidth() * camera.GetHeight()] );
        auto skeleton = model.GetCurrentPose()->skeleton;
        skeletonMesh = MeshUtils::buildMeshFromSkeleton ( skeleton, size );
    }
    //scale model to cube proportionally to z grayscale
    MVector3<float> max, min;
    max.SetX ( camera.GetWidth() );
    max.SetY ( camera.GetHeight() );
    max.SetZ ( 255 );
    BBox resizeBox ( min, max );
    model.GetBoundingBox();
    rayList.clear();
    for ( int i = 0; i < camera.GetWidth(); i++ ) {
        for ( int j = 0; j < camera.GetHeight(); j++ ) {
            MVector2<float> vec ( i,j );
            Ray ray = camera.ProjectPixelTo3dRay ( vec );
            rayList.push_back ( ray );
            cout << "(" << vec.GetX() << "," << vec.GetY() << ")" << "=" << ray.GetDirection().GetX() << "," << ray.GetDirection().GetY() << "," << ray.GetDirection().GetZ() << endl;
            MVector3<float> origin = ray.GetOrigin();
            MVector3<float> direction= ray.GetDirection();
            MVector3<float> modelIntersectionPoint;
            modelIntersectionPoint.SetZ ( -1000.0f );
            bool intersects = model.intersect ( origin, direction, modelIntersectionPoint );
            int zmodel = 0;
            //int index = i*camera.GetHeight()+j;
            int index = j*camera.GetWidth()+i;
            cout << "index : " << index << endl;
            if ( intersects ) {
                zmodel = modelIntersectionPoint.GetZ() >254?255:modelIntersectionPoint.GetZ();
                //image->setComponent(i*camera.GetHeight()+j, 255);
            }
            modelImage->setComponent ( index, zmodel );
            if ( skeletonMesh ) {
                MVector3<float> skeletonIntersectionPoint;
                skeletonIntersectionPoint.SetZ ( -1000.0f );
                bool intersects = skeletonMesh->intersect ( origin, direction, skeletonIntersectionPoint );
                int zskeleton = 0;
                if ( intersects ) {
                    zskeleton = skeletonIntersectionPoint.GetZ() >254?255:skeletonIntersectionPoint.GetZ();
                }
                skeletonImage->setComponent ( index, zskeleton );
            }
        }
    }
    imageList.push_back ( modelImage );
    if ( skeletonImage ) {
        imageList.push_back ( skeletonImage );
        delete skeletonMesh;
    }
    cout << "end capture" << endl;
}

Image * ImageUtils::Snapshot(Camera& camera, AnimatedModel& model, bool printDebug)
{
    Image* modelImage = new Image ( Image::GRAYSCALE, Image::UNSIGNED_BYTE, camera.GetWidth(), camera.GetHeight() );
    modelImage->setPixelData ( new unsigned char[camera.GetWidth() * camera.GetHeight()] );
    //init image to black
    for ( int i = 0; i < camera.GetWidth(); i++ ) {
        for ( int j = 0; j < camera.GetHeight(); j++ ) {
            int index = j*camera.GetWidth()+i;
            modelImage->setComponent ( index, 0 );
        }
    }
    auto it = model.GetBeginVisibleMeshIterator();
    auto endIt = model.GetEndVisibleMeshIterator();
    Mesh modelMesh;
    while(it!=endIt) {
        modelMesh = **it;
        Snapshot(*modelImage, camera, modelMesh, printDebug);
        ++it;
    }
    return modelImage;
}


Image* ImageUtils::Snapshot ( Camera& camera, Mesh& mesh,bool printDebug )
{
    Image* modelImage = new Image ( Image::GRAYSCALE, Image::UNSIGNED_BYTE, camera.GetWidth(), camera.GetHeight() );
    modelImage->setPixelData ( new unsigned char[camera.GetWidth() * camera.GetHeight()] );
    //init image to black
    for ( int i = 0; i < camera.GetWidth(); i++ ) {
        for ( int j = 0; j < camera.GetHeight(); j++ ) {
            int index = j*camera.GetWidth()+i;
            modelImage->setComponent ( index, 0 );
        }
    }
    Snapshot(*modelImage, camera, mesh, printDebug);
    return modelImage;
}


void ImageUtils::Snapshot(Image& modelImage, Camera& camera, Mesh& mesh, bool printDebug)
{
    //scale model to cube proportionally to z grayscale
    MVector3<float> max, min;
    max.SetX ( camera.GetWidth() );
    max.SetY ( camera.GetHeight() );
    max.SetZ ( 255 );
    BBox resizeBox ( min, max );
    for ( int i = 0; i < camera.GetWidth(); i++ ) {
        for ( int j = 0; j < camera.GetHeight(); j++ ) {
            MVector2<float> vec ( i,j );
            Ray ray = camera.ProjectPixelTo3dRay ( vec );
            if(printDebug) {
                cout << "(" << vec.GetX() << "," << vec.GetY() << ")" << "=" << ray.GetDirection().GetX() << "," << ray.GetDirection().GetY() << "," << ray.GetDirection().GetZ() << endl;
            }
            MVector3<float> origin = ray.GetOrigin();
            MVector3<float> direction= ray.GetDirection();
            MVector3<float> modelIntersectionPoint;
            modelIntersectionPoint.SetZ ( -1000.0f );
            bool intersects = mesh.intersect ( origin, direction, modelIntersectionPoint );
            int zmodel = 0;
            //int index = i*camera.GetHeight()+j;
            int index = j*camera.GetWidth()+i;
            if(printDebug) {
                cout << "index : " << index << endl;
            }
            if ( intersects ) {
                zmodel = camera.GetZFromPoint(modelIntersectionPoint);
                //zmodel = modelIntersectionPoint.GetZ() >254?255:modelIntersectionPoint.GetZ();
                //image->setComponent(i*camera.GetHeight()+j, 255);
                if(zmodel > modelImage.getComponent(index)) {//is near
                    modelImage.setComponent ( index, zmodel );
                }
            }
        }
    }
    if(printDebug) {
        cout << "end capture" << endl;
    }
}



