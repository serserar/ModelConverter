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


#ifndef MD5ANIMBASEFRAME_H
#define MD5ANIMBASEFRAME_H
#include "md5animjointlocation.h"
#include <vector>

using namespace std;

class md5animbaseframe
{
public:
    vector<md5animjointlocation*> getJointLocations();
    void setJointLocations(vector<md5animjointlocation*> jointLocations);
private:
    vector<md5animjointlocation*> jointLocations;
};

#endif // MD5ANIMBASEFRAME_H
