/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "md5writer.h"

const char* md5writer::MD5_COMMENT = "//";
const char* md5writer::MD5_LIST_START = "{";
const char* md5writer::MD5_LIST_END = "}";
const char* md5writer::MD5_VEC_START = "(";
const char* md5writer::MD5_VEC_END = ")";
const char* md5writer::MD5_MODEL_VERSION = "MD5Version";
const char* md5writer::MD5_COMMANDLINE = "commandline";
const char* md5writer::MD5_NUM_JOINTS = "numJoints";
const char* md5writer::MD5_NUM_MESHES = "numMeshes";
const char* md5writer::MD5_JOINTS = "joints";
const char* md5writer::MD5_MESH = "mesh";
const char* md5writer::MD5_SHADER = "shader";
const char* md5writer::MD5_NUM_VERTEX = "numverts";
const char* md5writer::MD5_VERTEX = "vert";
const char* md5writer::MD5_NUM_TRIANGLES = "numtris";
const char* md5writer::MD5_TRIANGLE = "tri";
const char* md5writer::MD5_NUM_WEIGHTS = "numweights";
const char* md5writer::MD5_WEIGHT = "weight";
const char* md5writer::MD5_ANIM_NUMFRAMES = "numFrames";
const char* md5writer::MD5_ANIM_NUMJOINTS = "numJoints";
const char* md5writer::MD5_ANIM_FRAMERATE = "frameRate";
const char* md5writer::MD5_ANIM_NUMANIMATEDCOMPONENTS = "numAnimatedComponents";
const char* md5writer::MD5_ANIM_HIERARCHY = "hierarchy";
const char* md5writer::MD5_ANIM_BOUNDS = "bounds";
const char* md5writer::MD5_ANIM_BASEFRAME = "baseframe";
const char* md5writer::MD5_ANIM_FRAME = "frame";
const char* md5writer::TAB = "\t";
const char* md5writer::SPACE = " ";
const char* md5writer::MD5_MESH_EXTENSION = ".md5mesh";
const char* md5writer::MD5_ANIMATION_EXTENSION = ".md5anim";

void md5writer::write(md5model* model, std::string destPath)
{
    this->destfile = new ofstream((destPath + model->getName()).c_str());
    if (this->destfile->is_open())
    {
        this->writeMD5Version(model->getVersion());
        this->writeMD5CommandLine("Converted by ModelConverter");
        this->writeEndOfLine();
        this->writeMD5NumJoints(model->getNumJoints());
        this->writeMD5NumMeshes(model->getNumMeshes());
        this->writeEndOfLine();
        this->writeMD5Joints(model->getSkeleton());
        this->writeEndOfLine();
        this->writeMD5Meshes(model->getMeshes());
        this->writeEndOfLine();
        this->destfile->close();
    }
    delete destfile;
    this->destfile = 0;
    for (int i = 0; i < model->getAnimations().size();i++) {
        this->writeMD5Animation(model->getAnimations().at(i),destPath);
    }
}

void md5writer::writeMD5Version(int version)
{
    *this->destfile << md5writer::MD5_MODEL_VERSION << md5writer::SPACE << version << endl;
}

void md5writer::writeMD5CommandLine(string commandLine)
{
    *this->destfile << md5writer::MD5_COMMANDLINE << md5writer::SPACE << "\"" <<  commandLine << "\"" << endl;
}

void md5writer::writeMD5NumJoints(int numJoints)
{
    *this->destfile << md5writer::MD5_NUM_JOINTS << md5writer::SPACE << numJoints << endl;
}

void md5writer::writeMD5NumMeshes(int numMeshes)
{
    *this->destfile << md5writer::MD5_NUM_MESHES << md5writer::SPACE << numMeshes << endl;
}

void md5writer::writeMD5Joints(vector<md5joint*> skeleton)
{
    *this->destfile << md5writer::MD5_JOINTS << md5writer::SPACE << md5writer::MD5_LIST_START << endl;
    for (int i = 0; i < skeleton.size(); i ++) {
        writeMD5Joint(skeleton.at(i));
    }
    *this->destfile << md5writer::MD5_LIST_END << endl;
}

void md5writer::writeMD5Joint(md5joint* joint)
{
    *this->destfile << md5writer::TAB << "\"" << joint->getName() << "\""
    << md5writer::TAB << joint->getParent() << md5writer::SPACE;
    writeMD5MVector(joint->getPosition());
    *this->destfile << md5writer::SPACE;
    writeMD5MQuaternion(joint->getRotation());
    *this->destfile << md5writer::SPACE << endl;
}

void md5writer::writeMD5Meshes(std::vector<md5mesh*> meshes)
{
    for (int i = 0; i < meshes.size(); i ++) {
        writeMD5Mesh(meshes.at(i));
        this->writeEndOfLine();
    }
}

void md5writer::writeMD5Mesh(md5mesh* mesh)
{
    *this->destfile << md5writer::MD5_MESH << md5writer::SPACE << md5writer::MD5_LIST_START << endl;
    writeMD5Shader(mesh->shader);
    this->writeEndOfLine();
    writeMD5NumVerts(mesh->numverts);
    for (int i = 0; i < mesh->vertexList.size();i++) {
        writeMD5Vertex(mesh->vertexList.at(i));
    }
    this->writeEndOfLine();
    writeMD5NumTriangles(mesh->numtris);
    for (int i = 0; i < mesh->triangleList.size();i++) {
        writeMD5Triangle(mesh->triangleList.at(i));
    }
    this->writeEndOfLine();
    writeMD5NumWeights(mesh->numweights);
    for (int i = 0; i < mesh->weightList.size();i++) {
        writeMD5Weight(mesh->weightList.at(i));
    }
    *this->destfile << md5writer::MD5_LIST_END << endl;
}

void md5writer::writeMD5MVector(MVector3<float>* vector)
{
    *this->destfile << md5writer::MD5_VEC_START << md5writer::SPACE
    << parseToDoubleString(vector->GetX()) << md5writer::SPACE
    << parseToDoubleString(vector->GetY()) << md5writer::SPACE
    << parseToDoubleString(vector->GetZ()) << md5writer::SPACE
    << md5writer::MD5_VEC_END;
}

void md5writer::writeMD5MQuaternion(MQuaternion<float>* quaternion)
{
    *this->destfile << md5writer::MD5_VEC_START << md5writer::SPACE
    << parseToDoubleString(quaternion->getI()) << md5writer::SPACE
    << parseToDoubleString(quaternion->getJ()) << md5writer::SPACE
    << parseToDoubleString(quaternion->getK()) << md5writer::SPACE
    << md5writer::MD5_VEC_END;
}

void md5writer::writeMD5Shader(string shader)
{
    *this->destfile << md5writer::TAB << md5writer::MD5_SHADER << md5writer::SPACE
    << "\"" << shader << "\"" << endl;
}

void md5writer::writeMD5NumVerts(int numVerts)
{
    *this->destfile << md5writer::TAB << md5writer::MD5_NUM_VERTEX << md5writer::SPACE
    << numVerts << endl;
}

void md5writer::writeMD5Vertex(md5vertex* vertex)
{
    *this->destfile << md5writer::TAB << md5writer::MD5_VERTEX << md5writer::SPACE
    << vertex->verIndex << md5writer::SPACE;
    writeArray2D(vertex->uv);
    *this->destfile << md5writer::SPACE << vertex->startWeight
    << md5writer::SPACE << vertex->countWeight << endl;
}

void md5writer::writeArray2D(double* darray)
{
    *this->destfile << md5writer::MD5_VEC_START << md5writer::SPACE;
    for (int i = 0; i < 2; i ++) {
        *this->destfile << parseToDoubleString(*darray) << md5writer::SPACE;
        darray++;
    }
    *this->destfile << md5writer::MD5_VEC_END ;
}

void md5writer::writeArray3D(double* darray)
{
    *this->destfile << md5writer::MD5_VEC_START << md5writer::SPACE;
    for (int i = 0; i < 3; i ++) {
        *this->destfile << parseToDoubleString(*darray) << md5writer::SPACE;
        darray++;
    }
    *this->destfile << md5writer::MD5_VEC_END ;
}

void md5writer::writeArray3I(int* iarray)
{
    for (int i = 0; i < 3; i ++) {
        *this->destfile << *iarray << md5writer::SPACE;
        iarray++;
    }
}

void md5writer::writeMD5NumTriangles(int numTriangles)
{
    *this->destfile << md5writer::TAB << md5writer::MD5_NUM_TRIANGLES << md5writer::SPACE
    << numTriangles << endl;
}

void md5writer::writeMD5Triangle(md5triangle* triangle)
{
    *this->destfile << md5writer::TAB << md5writer::MD5_TRIANGLE << md5writer::SPACE
    << triangle->triIndex  << md5writer::SPACE;
    writeArray3I(triangle->vertIndex);
    *this->destfile << endl;
}

void md5writer::writeMD5NumWeights(int numWeights)
{
    *this->destfile << md5writer::TAB << md5writer::MD5_NUM_WEIGHTS << md5writer::SPACE
    << numWeights << endl;
}

void md5writer::writeMD5Weight(md5weight* weight)
{
    *this->destfile << md5writer::TAB << md5writer::MD5_WEIGHT << md5writer::SPACE
    << weight->weightIndex << md5writer::SPACE
    << weight->joint << md5writer::SPACE
    << parseToDoubleString(weight->bias) << md5writer::SPACE;
    writeMD5MVector(weight->pos);
    *this->destfile << endl;
}

void md5writer::writeMD5Animation(md5animation* animation, const std::string& path)
{
    this->destfile = new ofstream((path + animation->getAnimationName()).c_str());
    writeMD5Version(animation->getVersion());
    writeMD5AnimationNumFrames(animation->getNumFrames());
    writeMD5AnimationNumJoints(animation->getNumJoints());
    writeMD5AnimationFrameRate(animation->getFrameRate());
    writeMD5AnimationNumAnimatedComponents(animation->getNumAnimatedComponents());
    writeMD5AnimationJoints(animation->getJoints());
    writeMD5AnimationBounds(animation->getBounds());
    writeMD5AnimationBaseFrame(animation->getBaseFrame());
    writeMD5AnimationFrames(animation->getFrames(), animation->getNumAnimatedComponents());
    delete this->destfile;
    this->destfile = 0;
}

void md5writer::writeMD5AnimationNumFrames(int numFrames)
{
    *this->destfile << md5writer::MD5_ANIM_NUMFRAMES << md5writer::SPACE
    << numFrames << endl;
}

void md5writer::writeMD5AnimationNumJoints(int numJoints)
{
    *this->destfile << md5writer::MD5_ANIM_NUMJOINTS << md5writer::SPACE
    << numJoints << endl;
}

void md5writer::writeMD5AnimationFrameRate(int frameRate)
{
    *this->destfile << md5writer::MD5_ANIM_FRAMERATE << md5writer::SPACE
    << frameRate << endl;
}

void md5writer::writeMD5AnimationNumAnimatedComponents(int numAnimatedComponents)
{
    *this->destfile << md5writer::MD5_ANIM_NUMANIMATEDCOMPONENTS << md5writer::SPACE
    << numAnimatedComponents << endl;
}

void md5writer::writeMD5AnimationJoints(std::vector< md5animjoint* > joints)
{
    *this->destfile << md5writer::MD5_ANIM_HIERARCHY << md5writer::SPACE << md5writer::MD5_LIST_START << endl;
    for (int i = 0; i < joints.size(); i ++) {
        writeMD5AnimationJoint(joints.at(i));
    }
    *this->destfile << md5writer::MD5_LIST_END << endl;

}

void md5writer::writeMD5AnimationJoint(md5animjoint* joint)
{
    *this->destfile << md5writer::TAB << "\"" << joint->getJointName() << "\""
    << md5writer::TAB << joint->getParent() << md5writer::SPACE
    << joint->getFlags() << md5writer::SPACE
    << joint->getStartIndex() << md5writer::SPACE
    << md5writer::SPACE << endl;
}

void md5writer::writeMD5AnimationBounds(std::vector< md5animbound* > bounds)
{
    *this->destfile << md5writer::MD5_ANIM_BOUNDS << md5writer::SPACE << md5writer::MD5_LIST_START << endl;
    for (int i = 0; i < bounds.size(); i ++) {
        writeMD5AnimationBound(bounds.at(i));
    }
    *this->destfile << md5writer::MD5_LIST_END << endl;

}

void md5writer::writeMD5AnimationBound(md5animbound* bound)
{
    *this->destfile << md5writer::TAB;
    writeMD5MVector(bound->getminb());
    *this->destfile << md5writer::SPACE;
    writeMD5MVector(bound->getmaxb());
    *this->destfile << endl;
}

void md5writer::writeMD5AnimationBaseFrame(md5animbaseframe* animBase)
{
    *this->destfile << md5writer::MD5_ANIM_BASEFRAME << md5writer::SPACE << md5writer::MD5_LIST_START << endl;
    for (int i = 0; i < animBase->getJointLocations().size(); i ++) {
        writeMD5AnimationJointLocation(animBase->getJointLocations().at(i));
    }
    *this->destfile << md5writer::MD5_LIST_END << endl;
}

void md5writer::writeMD5AnimationJointLocation(md5animjointlocation* jointLocation)
{
    *this->destfile << md5writer::TAB;
    writeMD5MVector(jointLocation->getPosition());
    *this->destfile << md5writer::SPACE;
    writeMD5MQuaternion(jointLocation->getRotation());
    *this->destfile << endl;
}

void md5writer::writeMD5AnimationFrames(std::vector<md5animframe*> frames, int numAnimatedComponents)
{
    for (int i = 0; i < frames.size(); i ++) {
        writeMD5AnimationFrame(frames.at(i), numAnimatedComponents);
    }
}

void md5writer::writeMD5AnimationFrame(md5animframe* frame, int numAnimatedComponents)
{
    *this->destfile << md5writer::MD5_ANIM_FRAME << md5writer::SPACE
    <<frame->getFrameIndex()<< md5writer::SPACE << md5writer::MD5_LIST_START << endl;
    double* fdata = frame->getFrameData();
    *this->destfile << md5writer::TAB;
    for (int i = 0; i < numAnimatedComponents; i ++) {
        *this->destfile << parseToDoubleString(fdata[i]) << md5writer::SPACE;
    }
    *this->destfile << md5writer::MD5_LIST_END << endl;
}

void md5writer::writeEndOfLine()
{
    *this->destfile << endl;
}


string md5writer::parseToDoubleString(double d)
{
    stringstream ss;
    ss.precision(numeric_limits<double>::digits10);//override the default
    ss << d;
    return ss.str();
}

