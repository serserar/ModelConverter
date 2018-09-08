/*
 * File:   main.cpp
 * Author: serserar
 *
 * Created on February 21, 2016, 2:02 AM
 */

//#include <cstdlib>
#include "mdl/MDLReader.h"
#include "base/MDLImporter.h"
#include "util/ImageUtils.h"
#include "util/PoissonDiskAlg.h"
#include "util/PoissonDiskAlg3D.h"
#include "md5/md5writer.h"
#include "md5/md5reader.h"
#include "viewer/GLRender.h"
#include "md5/MD5Exporter.h"
#include "md5/MD5Converter.h"
#include "md5/Options.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <pthread.h>
#include "Poco/Timer.h"
#include "Poco/Thread.h"
#include "Poco/Stopwatch.h"
#include "entity/EntityManager.h"
#include "entity/DynamicEntity.h"
#include "event/Event.h"
#include "input/InputManager.h"
#include "base/Octree.h"
#include "image/PPMReader.h"
#include "base/AutoRig.h"

using namespace std;
using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;


class TimerExample {
public:
    TimerExample() {
        _sw.start();
    }

    void onTimer(Timer& timer) {
        std::cout << "Callback called after " << _sw.elapsed()/1000 << " milliseconds." << std::endl;
    }
private:
    Stopwatch _sw;
};

void checkEvents() {
    DynamicEntity* dynamicEntity = new DynamicEntity();
    EntityManager::GetInstance()->RegisterEntity(dynamicEntity);
    cout << dynamicEntity->GetId() << endl;
    EventManager::GetInstance()->RegisterEventListener(EventType::EV_ENTITY, EntityManager::GetInstance());
    InputManager* inputManager = new InputManager();
    Event* vk_jump = new Event(EventType::EV_INPUT, EventType::EV_ENTITY,"vk_jump", "jump", dynamicEntity->GetId());
    inputManager->registerEvent(vk_jump);
    inputManager->fireEvent("vk_jump");
}
void checkAnimatioFSM() {

}

void checkPoissonDisk() {
    PoissonDiskAlg poissonDiskAlg;
    std::vector<Point2D<float>> samples;
    poissonDiskAlg.GeneratePoisson(100, 100,1.0f,10, samples);
    cout << samples.size()<< endl;
}

void checkPoissonDisk3D() {
    PoissonDiskAlg3D poissonDiskAlg3d;
    MVector3<float>bmin;
    MVector3<float>bmax(10.f, 10.f,10.f);
    BBox box(bmin, bmax);
    std::vector<Point3D<float>> samples;
    poissonDiskAlg3d.GeneratePoisson(&box, 0.3f, 10, samples);
    cout << samples.size()<< endl;
}

void writeMD5(AnimatedModel* model){
    Options options;
    options.SetMaterialPath("models/characters/vampire/eightball/edgar/");
    MD5Exporter converter;
    md5model* md5 = converter.Convert(*model, options);
    md5writer writer;
    writer.write(md5, "");
}

void checkOctree() {
    MVector3<float> min;
    MVector3<float> max(100.0f, 100.0f,100.0f);
    BBox box(min, max);
    std::vector<OctreeEntity*> entityList;
    Octree octree(box, entityList);
    octree.BuildTree();
}

int main(int argc, char** argv) {
    //checkOctree();
    //checkEvents();
    //checkPoissonDisk();
    //checkPoissonDisk3D();
    MDLReader mreader;
    //MDLModel* mdlmodel =  mreader.readModel("../samples/edgar.mdl");
    //MDLModel* mdlmodel =  mreader.readModel("../samples/eightball.mdl");
    //MDLModel* mdlmodel =  mreader.readModel("../samples/brit-inf.mdl");
    MDLModel* mdlmodel =  mreader.readModel("../samples/axis-inf.mdl");
    MD5Converter converter;
    md5model*  md5model = converter.Convert(*mdlmodel);
    md5writer writer;
    writer.write(md5model, "");
    //MDLModel* mdlmodel =  mreader.readModel("../samples/fatherd.mdl");
    //MDLModel* mdlmodel =  mreader.readModel("../samples/louis.mdl");
    //MDLModel* mdlmodel =  mreader.readModel("../samples/v_claw.mdl");
    
    MDLImporter mdlImporter;
    AnimatedModel* model = mdlImporter.Convert(*mdlmodel);
    //writeMD5(model);
    vector<int> visibleMeshes;
    visibleMeshes.push_back(0);
    visibleMeshes.push_back(1);
    visibleMeshes.push_back(2);
    visibleMeshes.push_back(3);
    visibleMeshes.push_back(4);
    visibleMeshes.push_back(5);
    visibleMeshes.push_back(6);
    visibleMeshes.push_back(7);
    visibleMeshes.push_back(8);
    visibleMeshes.push_back(9);
    visibleMeshes.push_back(10);
    visibleMeshes.push_back(11);
    visibleMeshes.push_back(12);
    visibleMeshes.push_back(13);
    visibleMeshes.push_back(14);
    visibleMeshes.push_back(15);
    visibleMeshes.push_back(16);
    visibleMeshes.push_back(17);
    visibleMeshes.push_back(18);
    visibleMeshes.push_back(19);
    visibleMeshes.push_back(20);
    visibleMeshes.push_back(21);
    visibleMeshes.push_back(22);
    visibleMeshes.push_back(23);
    visibleMeshes.push_back(24);
    visibleMeshes.push_back(25);
    visibleMeshes.push_back(26);
    visibleMeshes.push_back(27);
    visibleMeshes.push_back(28);
    visibleMeshes.push_back(29);
    visibleMeshes.push_back(30);
    visibleMeshes.push_back(31);
    visibleMeshes.push_back(32);
    visibleMeshes.push_back(33);
    visibleMeshes.push_back(34);
    visibleMeshes.push_back(35);
    visibleMeshes.push_back(36);
    model->SetVisibleMeshes(visibleMeshes);
    auto it = model->GetBeginMeshIterator();
    auto endIt = model->GetEndMeshIterator();
    AutoRig autoRig;
    Skeleton* skeleton = model->GetSkeleton();
    SkinnedMesh* mesh;
    vector<SkinnedMesh*> meshArray;
    SkinnedMesh* skinnedMesh=nullptr;
    int meshIndex=0;
    while(it!=endIt) {
        mesh = *it;
        autoRig.BuildClusters(*mesh, *skeleton);
        skinnedMesh=autoRig.AutoRigMesh(*mesh, meshIndex, *skeleton);
        skinnedMesh->SetBindPoseMesh(new Mesh(*mesh->GetBindPoseMesh()));
        meshArray.push_back(skinnedMesh);
        std::cout << "**** original *****" << std::endl;
        autoRig.PrintBoneCluster(*mesh, *skeleton, std::cout);
        std::cout << "**** generated *****" << std::endl;
        autoRig.PrintBoneCluster(*skinnedMesh, *skeleton, std::cout);
        meshIndex++;
        ++it;
    }
    //model->meshes=meshArray;
    bool view = true;
    if(view) {
        runViewer(model);
    }
    return 0;
}

