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


#ifndef MD5MESH_H
#define MD5MESH_H
#include "string.h"
#include <string>
#include <vector>
#include "md5vertex.h"
#include "md5triangle.h"
#include "md5weight.h"

using namespace std;
/*
    shader "<string>"

    numverts <int>
    vert vertIndex ( s t ) startWeight countWeight
    vert ...

    numtris <int>
    tri triIndex vertIndex[0] vertIndex[1] vertIndex[2]
    tri ...

    numweights <int>
    weight weightIndex joint bias ( pos.x pos.y pos.z )
    weight ...
    */
class md5mesh
{
public:
  string shader;
  int numverts;
  int numtris;
  int numweights;
  vector<md5vertex*> vertexList;
  vector<md5triangle*> triangleList;
  vector<md5weight*> weightList;
};

#endif // MD5MESH_H
