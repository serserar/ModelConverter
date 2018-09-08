/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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



#ifndef MD5READER_H
#define MD5READER_H
#ifdef WIN32
#define OS_SEP '\\'
#else
#define OS_SEP '/'
#endif
#include <string.h>
#include <string>
#include <vector>
#include "../util/tokenizer.h"
#include "../math/MVector3.h"
#include "md5model.h"
#include "md5joint.h"
#include "md5mesh.h"
#include "md5vertex.h"
#include "md5triangle.h"
#include "md5weight.h"
#include "md5animation.h"

using namespace std;

class md5reader
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
    
    md5reader();
    md5reader(string meshpath, vector<string> animspath);
    md5reader(const md5reader& other);
    md5model* parsemodel(string meshpath, vector<string> animspath);
    md5model* parsemodel();
    static string getFilename(string path);
    static string extractDirectory( const std::string& path );
    static string extractFilename( const std::string& path );
    static string changeExtension( const std::string& path, const std::string& ext );
    virtual ~md5reader();
private:
    string meshpath;
    vector<string> animspath;
    vector<md5joint*> buildSkeleton(Tokenizer* parser, int joints);
    md5joint* buildJoint(Tokenizer* parser);
    MVector3<float>* buildMVector(Tokenizer* parser, int dimension);
    double* buildDArray(Tokenizer* parser, int dimension, bool delimiter);
    double* buildDArrayLine(Tokenizer* parser);
    int* buildIArray(Tokenizer* parser, int dimension);
    MQuaternion<float>* buildQuaternion(Tokenizer* parser);
    vector<md5mesh*> buildMeshes(Tokenizer* parser, int numMeshes);
    md5mesh* buildMesh(Tokenizer* parser);
    md5vertex* buildVertex(Tokenizer* parser);
    md5triangle* buildTriangle(Tokenizer* parser);
    md5weight* buildWeight(Tokenizer* parser);
    md5animation* parseAnimation(string path);
    vector<md5animjoint*> buildAnimJoints(Tokenizer* parser, int njoints);
    md5animjoint* buildAnimJoint(Tokenizer* parser);
    vector<md5animbound*> buildAnimBounds(Tokenizer* parser, int numFrames);
    md5animbound* buildAnimBound(Tokenizer* parser, int index);
    md5animbaseframe* buildAnimBaseFrame(Tokenizer* parser, int numJoints);
    md5animjointlocation* buildAnimJointLocation(Tokenizer* parser, int jointIndex);
    md5animframe* buildAnimFrame(Tokenizer* parser, int numJoints);
};

string replaceStr(string str, const string& find, const string& replace);

#endif // MD5READER_H
