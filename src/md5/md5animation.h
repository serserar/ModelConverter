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


#ifndef MD5ANIMATION_H
#define MD5ANIMATION_H
#include "string.h"
#include <string>
#include <vector>
#include "md5animjoint.h"
#include "md5animbound.h"
#include "md5animbaseframe.h"
#include "md5animframe.h"


using namespace std;

class md5animation
{
public:
    md5animation();
    md5animation(string animationName);
    ~md5animation();
    int getVersion();
    void setVersion(int version);
    string getAnimationName();
    void setAnimationName(string animationName);
    string getCommandLine();
    void setCommandLine(string commandline);
    int getNumFrames();
    void setNumFrames(int numFrames);
    int getNumJoints();
    void setNumJoints(int numJoints);
    int getFrameRate();
    void setFrameRate(int frameRate);
    int getNumAnimatedComponents();
    void setNumAnimatedComponents(int numAnimatedComponents);
    vector<md5animjoint*> getJoints();
    void setJoints(vector<md5animjoint*> joints);
    vector<md5animbound*> getBounds();
    void setBounds(vector<md5animbound*> bounds);
    md5animbaseframe* getBaseFrame();
    void setBaseFrame(md5animbaseframe* baseframe);
    vector<md5animframe*> getFrames();
    void setFrames(vector<md5animframe*> frames);
private:
    string animationName;
    int version;
    string commandline;
    int numFrames;
    int numJoints;
    int frameRate;
    int numAnimatedComponents;
    vector<md5animjoint*> joints;
    vector<md5animbound*> bounds;
    md5animbaseframe* baseframe;
    vector<md5animframe*> frames;
};

#endif // MD5ANIMATION_H
