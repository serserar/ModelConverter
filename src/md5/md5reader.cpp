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


#include "md5reader.h"
#include "md5mesh.h"

const char* md5reader::MD5_COMMENT = "//";
const char* md5reader::MD5_LIST_START = "{";
const char* md5reader::MD5_LIST_END = "}";
const char* md5reader::MD5_VEC_START = "(";
const char* md5reader::MD5_VEC_END = ")";
const char* md5reader::MD5_MODEL_VERSION = "MD5Version";
const char* md5reader::MD5_COMMANDLINE = "commandline";
const char* md5reader::MD5_NUM_JOINTS = "numJoints";
const char* md5reader::MD5_NUM_MESHES = "numMeshes";
const char* md5reader::MD5_JOINTS = "joints";
const char* md5reader::MD5_MESH = "mesh";
const char* md5reader::MD5_SHADER = "shader";
const char* md5reader::MD5_NUM_VERTEX = "numverts";
const char* md5reader::MD5_VERTEX = "vert";
const char* md5reader::MD5_NUM_TRIANGLES = "numtris";
const char* md5reader::MD5_TRIANGLE = "tri";
const char* md5reader::MD5_NUM_WEIGHTS = "numweights";
const char* md5reader::MD5_WEIGHT = "weight";
const char* md5reader::MD5_ANIM_NUMFRAMES = "numFrames";
const char* md5reader::MD5_ANIM_NUMJOINTS = "numJoints";
const char* md5reader::MD5_ANIM_FRAMERATE = "frameRate";
const char* md5reader::MD5_ANIM_NUMANIMATEDCOMPONENTS = "numAnimatedComponents";
const char* md5reader::MD5_ANIM_HIERARCHY = "hierarchy";
const char* md5reader::MD5_ANIM_BOUNDS = "bounds";
const char* md5reader::MD5_ANIM_BASEFRAME = "baseframe";
const char* md5reader::MD5_ANIM_FRAME = "frame";

md5reader::md5reader()
{
}

md5reader::md5reader(string meshpath, vector< string > animspath)
{
    this->meshpath = meshpath;
    this->animspath = animspath;
}


md5reader::md5reader(const md5reader& other)
{

}

md5model* md5reader::parsemodel(string meshpath, vector<string> animspath)
{
    this->meshpath = meshpath;
    this->animspath = animspath;
    return this->parsemodel();
}

md5model* md5reader::parsemodel()
{
    md5model* model = new md5model();
    int version;
    int numJoints;
    int numMeshes;
    string ntoken;
    model->setName(extractFilename(this->meshpath));
    Tokenizer* parser = new Tokenizer(this->meshpath.c_str());

    while (parser->hasnext()) {
        ntoken = parser->next();
        if (!ntoken.compare(md5reader::MD5_MODEL_VERSION)) {
            version = parser->nextAsInt();
            model->setVersion(version);
            cout << version << endl;
        } else if (!ntoken.compare(md5reader::MD5_NUM_JOINTS)) {
            numJoints = parser->nextAsInt();
            model->setNumJoints(numJoints);
            cout << numJoints << endl;
        } else if (!ntoken.compare(md5reader::MD5_NUM_MESHES)) {
            numMeshes = parser->nextAsInt();
            model->setNumMeshes(numMeshes);
            cout << numMeshes << endl;
        } else if (!ntoken.compare(md5reader::MD5_JOINTS)) {
            model->setSkeleton(buildSkeleton(parser, numJoints));
        } else if (!ntoken.compare(md5reader::MD5_MESH)) {
            model->setMeshes(buildMeshes(parser, numMeshes));
        }
    }
    parser = 0;
    vector<md5animation*> animations;
    for (int i = 0; i < this->animspath.size(); i ++) {
        animations.push_back(parseAnimation(this->animspath.at(i)));
    }
    model->setAnimations(animations);
    return model;
}

vector<md5joint*> md5reader::buildSkeleton(Tokenizer* parser, int joints)
{
    vector<md5joint*> skeleton;
    string ntoken = parser->next();
    if (!ntoken.compare(md5reader::MD5_LIST_START)) {
        for (int i = 0; i < joints; i ++) {
            parser->nextLine();//skip to the next line
            skeleton.push_back(buildJoint(parser));
        }
    }
    return skeleton;
}

md5joint* md5reader::buildJoint(Tokenizer* parser)
{
    md5joint* mjoint = new md5joint();
    mjoint->setName(replaceStr(parser->next(),"\"", ""));
    mjoint->setParent(parser->nextAsInt());
    mjoint->setPosition(buildMVector(parser,3));
    mjoint->setRotation(buildQuaternion(parser));
    return mjoint;
}

MVector3<float>* md5reader::buildMVector(Tokenizer* parser, int dimension)
{
    MVector3<float>* vec = 0;
    string ntoken = parser->next();
    if (!ntoken.compare(md5reader::MD5_VEC_START)) {
        vec = new MVector3<float>(parser->nextAsFloat(), parser->nextAsFloat(), parser->nextAsFloat());
    }
    ntoken = parser->next();//close ')'
    return vec;
}

double* md5reader::buildDArray(Tokenizer* parser, int dimension, bool delimiter)
{
    double* array = 0;
    array= new double[dimension];
    if (delimiter) {
        string ntoken = parser->next();
        if (!ntoken.compare(md5reader::MD5_VEC_START)) {
            for (int i = 0; i < dimension; i ++) {
                array[i] = parser->nextAsDouble();
            }
        }
        ntoken = parser->next();//close ')'
    } else {
        for (int i = 0; i < dimension; i ++) {
            array[i] = parser->nextAsDouble();
        }
    }
    return array;
}

double* md5reader::buildDArrayLine(Tokenizer* parser)
{
    double* array = 0;
    array = parser->nextLineAsDouble();
    return array;
}

int* md5reader::buildIArray(Tokenizer* parser, int dimension)
{
    int* array = 0;
    array= new int[dimension];
    for (int i = 0; i < dimension; i ++) {
        array[i] = parser->nextAsInt();
    }
    return array;
}


MQuaternion<float>* md5reader::buildQuaternion(Tokenizer* parser)
{
    MQuaternion<float>* q = 0;
    string ntoken = parser->next();
    float x,y,z,w;
    if (!ntoken.compare(md5reader::MD5_VEC_START)) {
        
        x = parser->nextAsFloat();
        y = parser->nextAsFloat();
        z = parser->nextAsFloat();
	w = 
        
        w = 1.0f - (x * x) - (y * y) - (z * z);
        if (w < 0.0f) {
            w = 0.0f;
        }
        else {
            w= -Math<float>::Sqrt(w);
        }
        q = new  MQuaternion<float>(w, x, y, z);
    }
    ntoken = parser->next();//close ')'
    return q;
}

vector<md5mesh*> md5reader::buildMeshes(Tokenizer* parser, int numMeshes) {
    vector<md5mesh*> meshes;
    string ntoken = parser->next();
    if (!ntoken.compare(md5reader::MD5_LIST_START)) {
        for (int i = 0; i < numMeshes; i ++) {
            parser->nextLine();//skip to the next line
            meshes.push_back(buildMesh(parser));
        }
    }
    return meshes;
}

md5mesh* md5reader::buildMesh(Tokenizer* parser)
{
    md5mesh* mesh = new md5mesh();
    string ntoken = parser->next();
    while (ntoken.compare(md5reader::MD5_LIST_END) && parser->hasnext()) {
        if (!ntoken.compare(md5reader::MD5_SHADER)) {
            mesh->shader = replaceStr(parser->next(),"\"", "");
        } else if (!ntoken.compare(md5reader::MD5_NUM_VERTEX)) {
            mesh->numverts = parser->nextAsInt();
        } else if (!ntoken.compare(md5reader::MD5_VERTEX)) {
            mesh->vertexList.push_back(buildVertex(parser));
        } else if (!ntoken.compare(md5reader::MD5_NUM_TRIANGLES)) {
            mesh->numtris = parser->nextAsInt();
        } else if (!ntoken.compare(md5reader::MD5_TRIANGLE)) {
            mesh->triangleList.push_back(buildTriangle(parser));
        } else if (!ntoken.compare(md5reader::MD5_NUM_WEIGHTS)) {
            mesh->numweights = parser->nextAsInt();
        } else if (!ntoken.compare(md5reader::MD5_WEIGHT)) {
            mesh->weightList.push_back(buildWeight(parser));
        } else if (!ntoken.compare(md5reader::MD5_COMMENT)) {
            parser->nextLine();
        }
        ntoken = parser->next();
    }
    return mesh;
}

md5vertex* md5reader::buildVertex(Tokenizer* parser)
{
    md5vertex* vertex = new md5vertex();
    vertex->verIndex = parser->nextAsInt();
    vertex->uv = buildDArray(parser, 2, true);
    vertex->startWeight = parser->nextAsInt();
    vertex->countWeight = parser->nextAsInt();
    return vertex;
}

md5triangle* md5reader::buildTriangle(Tokenizer* parser)
{
    md5triangle* triangle = new md5triangle();
    triangle->triIndex = parser->nextAsInt();
    triangle->vertIndex = buildIArray(parser, 3);
    return triangle;
}

md5weight* md5reader::buildWeight(Tokenizer* parser)
{
    md5weight* weight = new md5weight();
    weight->weightIndex = parser->nextAsInt();
    weight->joint = parser->nextAsInt();
    weight->bias = parser->nextAsDouble();
    weight->pos = buildMVector(parser, 3);
    return weight;
}

md5animation* md5reader::parseAnimation(string path)
{
    md5animation* animation = new md5animation();
    animation->setAnimationName(extractFilename(path));
    Tokenizer* parser = new Tokenizer(path.c_str());
    string ntoken;
    int version;
    int numFrames;
    int numJoints;
    int frameRate;
    int numAnimatedComponents;
    vector<md5animframe*> frames;
    while (parser->hasnext()) {
        ntoken = parser->next();
        if (!ntoken.compare(md5reader::MD5_MODEL_VERSION)) {
            version = parser->nextAsInt();
            animation->setVersion(version);
        } else if (!ntoken.compare(md5reader::MD5_ANIM_NUMFRAMES)) {
            numFrames = parser->nextAsInt();
            animation->setNumFrames(numFrames);
        }  else if (!ntoken.compare(md5reader::MD5_ANIM_NUMJOINTS)) {
            numJoints = parser->nextAsInt();
            animation->setNumJoints(numJoints);
        } else if (!ntoken.compare(md5reader::MD5_ANIM_FRAMERATE)) {
            frameRate = parser->nextAsInt();
            animation->setFrameRate(frameRate);
        } else if (!ntoken.compare(md5reader::MD5_ANIM_NUMANIMATEDCOMPONENTS)) {
            numAnimatedComponents = parser->nextAsInt();
            animation->setNumAnimatedComponents(numAnimatedComponents);
        } else if (!ntoken.compare(md5reader::MD5_ANIM_HIERARCHY)) {
            animation->setJoints(buildAnimJoints(parser, numJoints));
        } else if (!ntoken.compare(md5reader::MD5_ANIM_BOUNDS)) {
            animation->setBounds(buildAnimBounds(parser, numFrames));
        } else if (!ntoken.compare(md5reader::MD5_ANIM_BASEFRAME)) {
            animation->setBaseFrame(buildAnimBaseFrame(parser, numJoints));
        } else if (!ntoken.compare(md5reader::MD5_ANIM_FRAME)) {
            frames.push_back(buildAnimFrame(parser, numAnimatedComponents));
        }
    }
    animation->setFrames(frames);
    parser = 0;
    return animation;
}

vector<md5animjoint*> md5reader::buildAnimJoints(Tokenizer* parser, int njoints)
{
    vector<md5animjoint*> joints;
    string ntoken = parser->next();
    if (!ntoken.compare(md5reader::MD5_LIST_START)) {
        for (int i = 0;i < njoints; i ++) {
            parser->nextLine();//skip to the next line
            joints.push_back(buildAnimJoint(parser));
        }
    }
    return joints;
}

md5animjoint* md5reader::buildAnimJoint(Tokenizer* parser)
{
    md5animjoint* joint = new md5animjoint();
    joint->setJointName(replaceStr(parser->next(),"\"", ""));
    joint->setParent(parser->nextAsInt());
    joint->setFlags(parser->nextAsInt());
    joint->setStartIndex(parser->nextAsInt());
    return joint;
}


vector<md5animbound*> md5reader::buildAnimBounds(Tokenizer* parser, int numFrames)
{
    vector<md5animbound*> bounds;
    string ntoken = parser->next();
    if (!ntoken.compare(md5reader::MD5_LIST_START)) {
        for (int i = 0; i < numFrames; i ++) {
            bounds.push_back(buildAnimBound(parser,i));
            parser->nextLine();
        }
    }
    return bounds;
}

md5animbound* md5reader::buildAnimBound(Tokenizer* parser, int index)
{
    md5animbound* bound = new md5animbound();
    bound->setFrameIndex(index);
    bound->setminb(buildMVector(parser, 3));
    bound->setmaxb(buildMVector(parser, 3));
    return bound;
}

md5animbaseframe* md5reader::buildAnimBaseFrame(Tokenizer* parser, int numJoints)
{
    md5animbaseframe* baseframe = new md5animbaseframe();
    string ntoken = parser->next();
    if (!ntoken.compare(md5reader::MD5_LIST_START)) {
        vector<md5animjointlocation*> jointLocations;
        for (int i = 0; i < numJoints;i++) {
            jointLocations.push_back(buildAnimJointLocation(parser, i));
        }
        baseframe->setJointLocations(jointLocations);
    }
    return baseframe;
}

md5animjointlocation* md5reader::buildAnimJointLocation(Tokenizer* parser, int jointIndex)
{
    md5animjointlocation* jointLocation = new md5animjointlocation();
    jointLocation->setJointIndex(jointIndex);
    jointLocation->setPosition(buildMVector(parser, 3));
    jointLocation->setRotation(buildQuaternion(parser));
    return jointLocation;
}


md5animframe* md5reader::buildAnimFrame(Tokenizer* parser, int numAnimatedComponents)
{
    md5animframe* frame = new md5animframe();
    frame->setFrameIndex(parser->nextAsInt());
    string ntoken = parser->next();//{
    double* frames;
    frames = buildDArray(parser, numAnimatedComponents, false);
    frame->setFrameData(frames);
    return frame;
}

md5reader::~md5reader()
{

}

string replaceStr(string str, const string& find, const string& replace) {

    // set our locator equal to the first appearance of any character in replace
    size_t found = str.find_first_of(find);
    while (found != string::npos) { // While our position in the sting is in range.
        str.replace(found,1,replace);  // Change the character at position.
        found = str.find_first_of(find, found+1); // Relocate again.
    }
    return str; // return our new string.
}


string md5reader::getFilename(string path)
{

}

string md5reader::extractDirectory( const std::string& path )
{
    return path.substr( 0, path.find_last_of(OS_SEP) +1 );
}

string md5reader::extractFilename( const std::string& path )
{
    return path.substr( path.find_last_of(OS_SEP) +1 );
}

string md5reader::changeExtension( const std::string& path, const std::string& ext )
{
    std::string filename = extractFilename( path );
    return extractDirectory( path ) +filename.substr( 0, filename.find_last_of( '.' ) ) +ext;
}
