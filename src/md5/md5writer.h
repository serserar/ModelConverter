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


#ifndef MD5WRITER_H
#define MD5WRITER_H
#ifdef WIN32
#define OS_SEP '\\'
#else
#define OS_SEP '/'
#endif
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include "md5model.h"
#include "string.h"
#include <string>

#define length(x) (sizeof(x) / sizeof(*(x)))

using namespace std;

class md5writer
{
public:
    static const char* MD5_COMMENT;
    static const char* MD5_LIST_START;
    static const char* MD5_LIST_END;
    static const char* MD5_VEC_START;
    static const char* MD5_VEC_END;
    static const char* MD5_MODEL_VERSION;
    static const char* MD5_COMMANDLINE;
    static const char* MD5_NUM_JOINTS;
    static const char* MD5_NUM_MESHES;
    static const char* MD5_JOINTS;
    static const char* MD5_MESH;
    static const char* MD5_SHADER;
    static const char* MD5_NUM_VERTEX;
    static const char* MD5_VERTEX;
    static const char* MD5_NUM_TRIANGLES;
    static const char* MD5_TRIANGLE;
    static const char* MD5_NUM_WEIGHTS;
    static const char* MD5_WEIGHT;
    static const char* MD5_ANIM_NUMFRAMES;
    static const char* MD5_ANIM_NUMJOINTS;
    static const char* MD5_ANIM_FRAMERATE;
    static const char* MD5_ANIM_NUMANIMATEDCOMPONENTS;
    static const char* MD5_ANIM_HIERARCHY;
    static const char* MD5_ANIM_BOUNDS;
    static const char* MD5_ANIM_BASEFRAME;
    static const char* MD5_ANIM_FRAME;
    static const char* TAB;
    static const char* SPACE;
    static const char* MD5_MESH_EXTENSION;
    static const char* MD5_ANIMATION_EXTENSION;
    void write(md5model* model, string destPath);
private:
    ofstream* destfile;
    void writeMD5Version(int version);
    void writeMD5CommandLine(string commandLine);
    void writeMD5NumJoints(int numJoints);
    void writeMD5NumMeshes(int numMeshes);
    void writeMD5Joints(vector<md5joint*> skeleton);
    void writeMD5Joint(md5joint* joint);
    void writeMD5Meshes(vector<md5mesh*> meshes);
    void writeMD5Mesh(md5mesh* mesh);
    void writeMD5MVector(MVector3<float>* vector);
    void writeMD5MQuaternion(MQuaternion<float>* quaternion);
    void writeMD5Shader(string shader);
    void writeMD5NumVerts(int numVerts);
    void writeMD5Vertex(md5vertex* vertex);
    void writeArray2D(double* darray);
    void writeArray3D(double* darray);
    void writeArray3I(int* iarray);
    void writeMD5NumTriangles(int numTriangles);
    void writeMD5Triangle(md5triangle* triangle);
    void writeMD5NumWeights(int numWeights);
    void writeMD5Weight(md5weight* weight);
    void writeMD5Animation(md5animation* animation,const string& path);
    void writeMD5AnimationNumFrames(int numFrames);
    void writeMD5AnimationNumJoints(int numJoints);
    void writeMD5AnimationFrameRate(int frameRate);
    void writeMD5AnimationNumAnimatedComponents(int numAnimatedComponents);
    void writeMD5AnimationJoints(vector<md5animjoint*> joints);
    void writeMD5AnimationJoint(md5animjoint* joint);
    void writeMD5AnimationBounds(vector<md5animbound*> bounds);
    void writeMD5AnimationBound(md5animbound* bound);
    void writeMD5AnimationBaseFrame(md5animbaseframe* animBase);
    void writeMD5AnimationJointLocation(md5animjointlocation* jointLocation);
    void writeMD5AnimationFrames(vector<md5animframe*> frames, int numAnimatedComponents);
    void writeMD5AnimationFrame(md5animframe* frame, int numAnimatedComponents);
    void writeEndOfLine();
    string parseToDoubleString(double d);
};

#endif // MD5WRITER_H
