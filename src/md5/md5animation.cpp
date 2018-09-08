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


#include "md5animation.h"

md5animation::md5animation()
{

}

md5animation::md5animation(string animationName)
{
    this->animationName = animationName;
}

md5animation::~md5animation()
{

}

string md5animation::getAnimationName()
{
    return this->animationName;
}

void md5animation::setAnimationName(string animationName)
{
    this->animationName = animationName;
}

int md5animation::getVersion()
{
    return this->version;
}

void md5animation::setVersion(int version)
{
    this->version = version;
}

string md5animation::getCommandLine()
{
    return this->commandline;
}

void md5animation::setCommandLine(string commandline)
{
    this->commandline = commandline;
}

int md5animation::getFrameRate()
{
    return this->frameRate;
}

void md5animation::setFrameRate(int frameRate)
{
    this->frameRate = frameRate;
}

int md5animation::getNumAnimatedComponents()
{
    return this->numAnimatedComponents;
}

void md5animation::setNumAnimatedComponents(int numAnimatedComponents)
{
    this->numAnimatedComponents = numAnimatedComponents;
}

int md5animation::getNumFrames()
{
    return this->numFrames;
}

void md5animation::setNumFrames(int numFrames)
{
    this->numFrames = numFrames;
}

int md5animation::getNumJoints()
{
    return this->numJoints;
}

void md5animation::setNumJoints(int numJoints)
{
    this->numJoints = numJoints;
}

std::vector< md5animjoint* > md5animation::getJoints()
{
    return this->joints;
}

void md5animation::setJoints(std::vector< md5animjoint* > joints)
{
    this->joints = joints;
}

std::vector< md5animbound* > md5animation::getBounds()
{
    return this->bounds;
}

void md5animation::setBounds(std::vector< md5animbound* > bounds)
{
    this->bounds = bounds;
}

md5animbaseframe* md5animation::getBaseFrame()
{
    return this->baseframe;
}

void md5animation::setBaseFrame(md5animbaseframe* baseframe)
{
    this->baseframe = baseframe;
}

std::vector< md5animframe* > md5animation::getFrames()
{
    return this->frames;
}

void md5animation::setFrames(std::vector< md5animframe* > frames)
{
    this->frames = frames;
}


