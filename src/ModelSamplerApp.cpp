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

#include "ModelSamplerApp.h"

using namespace std;
namespace fs = std::experimental::filesystem;

ModelSamplerApp::ModelSamplerApp ( std::string inputPath, std::string destPath, std::string sampleFileName )
{
    this->inputPath = inputPath;
    this->destPath = destPath;
    this->sampleFileName = sampleFileName;
}

ModelSamplerApp::~ModelSamplerApp()
{

}


void ModelSamplerApp::Run()
{

    std::vector<string> fileList;
    fs::path input ( inputPath );
    fs::path output ( destPath );
    fs::path samplelist ( sampleFileName );
    input/=samplelist;
    if ( fs::exists ( input ) ) {
        SamplesConfigParser samplesConfigParser;
        SamplesConfig* samplesConfig = samplesConfigParser.getParsedSamplesConfig(input.c_str());
        if(samplesConfig) {
            Camera cam = samplesConfig->config.cam;
            for (auto sampleModel : samplesConfig->sampleModels) {
                fs::path sampleFile ( inputPath );
                sampleFile/=sampleModel.fileName;
                if ( fs::exists ( sampleFile ) ) {
                    MDLImporter importer;
                    MDLReader reader;
                    MDLModel* mdlModel = reader.readModel ( sampleFile );
                    if ( mdlModel ) {
                        AnimatedModel* model = importer.Convert ( *mdlModel );
                        if ( model ) {
                            fs::path destModelSamplesPath = output;
                            destModelSamplesPath/=sampleModel.name;
                            destModelSamplesPath.replace_extension ( "" );
                            if ( !fs::exists ( destModelSamplesPath ) ) { //hay que  quitar la extension
                                fs::create_directories ( destModelSamplesPath );
                            }
                            vector<MTransform<float>> modelTransforms;
                            for(auto transform : sampleModel.transforms) {
                                modelTransforms.push_back(transform);
                            }
                            if(!sampleModel.visibleMeshes.empty()) {
                                model->SetVisibleMeshes(sampleModel.visibleMeshes);
                            }
                            SampleModel ( *model, cam, destModelSamplesPath, 10, modelTransforms );
                            delete model;
                        }
                        delete mdlModel;
                    }
                }
            }
        }
    }
}

void ModelSamplerApp::SampleModel ( AnimatedModel& model, Camera& cam, string modelDestPath, int samples, std::vector<MTransform<float>>& modelTransforms )
{
    fs::path destPath = modelDestPath;
    auto animit = model.GetBeginAnimationIterator();
    auto animendIt = model.GetEndAnimationIterator();
    while ( animit!=animendIt ) {
        Animation anim = **animit;
        model.setAnimation ( anim.GetName() );
        int frames = anim.GetFrameSize();
        float frameRate = anim.GetFrameRate();
        double animDuration = frames/frameRate;
        double sampleTime = animDuration/samples;
        double currentTime = 0;
        int sample = 0;
        while (currentTime <  animDuration) {
            model.OnUpdate ( currentTime );
            Skeleton& skeleton = model.GetCurrentPose()->skeleton;
            float size = 0.2f;
            Mesh* skeletonMesh = MeshUtils::buildMeshFromSkeleton ( skeleton, size );
            for ( auto transform : modelTransforms ) {
                model.ApplyTransform ( transform );
                skeletonMesh->ApplyTransform ( transform );
                skeletonMesh->ApplyTransforms();
            }
            MTransform<float> scaleTransform = GenerateScaleTransformToCameraBounds(model, cam);
            model.ApplyTransform ( scaleTransform );
            skeletonMesh->ApplyTransform ( scaleTransform );
            skeletonMesh->ApplyTransforms();
            for ( int i = 0; i < 4; i++ ) {
                if ( i == 1 ) {
                    MVector3<float> axisrotation ( 0,-Math<float>::PI/2,0 );
                    MTransform<float> rotationTransform;
                    rotationTransform.SetRotation ( axisrotation );
                    model.ApplyTransform ( rotationTransform );
                    skeletonMesh->ApplyTransform ( rotationTransform );
                    skeletonMesh->ApplyTransforms();
                } else if ( i == 2 ) {
                    MVector3<float> axisrotation ( 0,-Math<float>::PI,0 );
                    MTransform<float> rotationTransform;
                    rotationTransform.SetRotation ( axisrotation );
                    model.ApplyTransform ( rotationTransform );
                    skeletonMesh->ApplyTransform ( rotationTransform );
                    skeletonMesh->ApplyTransforms();
                } else if ( i == 3 ) {
                    MVector3<float> axisrotation ( 0,-Math<float>::PI - Math<float>::PI/2,0 );
                    MTransform<float> rotationTransform;
                    rotationTransform.SetRotation ( axisrotation );
                    model.ApplyTransform ( rotationTransform );
                    skeletonMesh->ApplyTransform ( rotationTransform );
                    skeletonMesh->ApplyTransforms();
                }
                Image* img_model = ImageUtils::Snapshot ( cam, model );
                PPMReader writer;
                fs::path imageModelPath = destPath;
                writer.writePGM5 ( imageModelPath/="img_model_"+ anim.GetName() + std::to_string ( i ) + std::to_string (sample ) +".ppm",*img_model );
                delete img_model;
                Image* img_skeleton = ImageUtils::Snapshot ( cam, *skeletonMesh );
                fs::path imageSkeletonModelPath = destPath;
                writer.writePGM5 ( imageSkeletonModelPath/="img_skeleton_"+ anim.GetName()+ std::to_string ( i ) + std::to_string (sample ) +".ppm",*img_skeleton );
                delete img_skeleton;
            }
            delete skeletonMesh;
            sample++;
            currentTime+=sampleTime;
        }
        animit++;
    }
}

MTransform<float> ModelSamplerApp::GenerateScaleTransformToCameraBounds(AnimatedModel& model, Camera& cam)
{
    //scale
    //get camera max
    BBox modelBox = model.GetBoundingBox();
    
    float modelWidth = modelBox.GetWidth();
    float modelHeight = modelBox.GetHeight();
    float modelDepth = modelBox.GetDepth();
    float scale = 0.1f;
//     float camMax = cam.GetWidthZ ( modelBox.boundMax.GetZ() );
//     float camMay = cam.GetHeightZ ( modelBox.boundMax.GetZ() );
//     camMax/=2;
//     camMay/=2;
//     if ( modelWidth >= modelHeight && modelWidth >= modelDepth ) {
//         scale = camMax / modelWidth;
//     } else if ( modelHeight >= modelWidth && modelHeight >= modelDepth ) {
//         scale = camMay / modelHeight;
//     } else {
//         scale = camMax / modelDepth;
//     }
    float cubeSize = 16;
    float scaleWidth = cubeSize / modelWidth;
    float scaleHeight = cubeSize  / modelHeight;
    float scaleDepth = cubeSize  / modelDepth;
    //MVector3<float> scale(scaleWidth, scaleHeight , scaleDepth);
    MTransform<float> scaleTransform;
    //scaleTransform.SetScale ( scale );
    scaleTransform.SetScale ( scale );
    return scaleTransform;
}


