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


#include "intbuffer.h"

intbuffer::intbuffer(int size)
{
    this->size = size;
    this->buffer = new int[size];
    this->offset = 0;
}

intbuffer::intbuffer(int size, int* buffer)
{
    this->size = size;
    this->buffer = buffer;
    this->offset = size;
}

int intbuffer::getSize()
{
    this->size;
}

void intbuffer::add(int index, int i)
{
    this->buffer[index] = i;
}

void intbuffer::append(int i)
{
    if (this->offset < this->size) {
        this->buffer[this->offset] = i;
        this->offset++;
    }
}

int intbuffer::get(int index)
{
    return this->buffer[index];
}

void intbuffer::update(int index, int i)
{
    this->buffer[index] = i;
}

int& intbuffer::operator[](int index)
{
    return this->buffer[index];
}

int* intbuffer::asIntArray()
{
    return this->buffer;
}




