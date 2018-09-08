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


#include "floatbuffer.h"

floatbuffer::floatbuffer(int size)
{
    this->size = size;
    this->offset = 0;
    this->buffer = new float[size];
}

floatbuffer::floatbuffer(int size, float* buffer)
{
    this->size = size;
    this->offset = 0;
    this->buffer = buffer;
}

int floatbuffer::getSize()
{
    this->size;
}

void floatbuffer::add(int index, float f)
{
    this->buffer[index]=f;
}

void floatbuffer::append(float f)
{
    this->buffer[offset] = f;
    this->offset++;
}

void floatbuffer::add(int index, MVector3* vec)
{
    this->buffer[index] = vec->get(0);
    this->buffer[index + 1] = vec->get(1);
    this->buffer[index + 2] = vec->get(2);
}

void floatbuffer::append(MVector3* vec)
{
    this->buffer[this->offset] = vec->get(0);
    this->buffer[this->offset + 1] = vec->get(1);
    this->buffer[this->offset + 2] = vec->get(2);
    this->offset+=3;
}

float floatbuffer::get(int index)
{
    return this->buffer[index];
}

void floatbuffer::update(int index, float f)
{
    this->buffer[index] = f;
}

float& floatbuffer::operator[](int index)
{
    return this->buffer[index];
}

float* floatbuffer::asFloatArray()
{
    return this->buffer;
}

void floatbuffer::initialize()
{
    if (this->buffer) {
        delete[] this->buffer;
    }
    this->buffer = new float[this->size];
}


