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


#ifndef FLOATBUFFER_H
#define FLOATBUFFER_H
#include "../math/math.h"
#include "../math/mvector3.h"

class MVector3;
class floatbuffer
{
public:
    floatbuffer(int size);
    floatbuffer(int size, float* buffer);
    int getSize();
    void update(int index, float f);
    void add(int index, float f);
    void append(float f);
    void add(int index, MVector3* vec);
    void append(MVector3* vec);
    float get(int index);
    float& operator[](int index);
    float* asFloatArray();
private:
    int size;
    int offset;
    float* buffer;
    void initialize();
};

#endif // FLOATBUFFER_H
