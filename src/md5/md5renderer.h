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


#ifndef MD5RENDERER_H
#define MD5RENDERER_H
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <string>
#include "string.h"
#include "md5model.h"

class md5renderer
{
public :
    md5renderer(md5model* model);
    void initialize(int argc, char *argv[]);
    static void setModel(md5model* model);
    static md5model* getModel();
    void drawModel();
    void drawSkeleton(md5joint* skeleton, int numjoints);
    
private :
    static md5model* model;
    float* vertexArray;
    int* vertexIndex;
    static void display();
    static void reshape(int w, int h);
    static void keyboard (unsigned char key, int x, int y);
    void cleanup();
    void drawVertexArrayf(float*vertexArray, int *vertexIndices, int ntriangles);
    void init(void);
    void initGL (int argc, char *argv[]);
};



#endif // MD5RENDERER_H
