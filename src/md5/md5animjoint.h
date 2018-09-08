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


#ifndef MD5ANIMJOINT_H
#define MD5ANIMJOINT_H
#include <string>

using namespace std;

class md5animjoint
{
public :
    md5animjoint();
    ~md5animjoint();
    string getJointName();
    void setJointName(string jointName);
    int getParent();
    void setParent(int parent);
    int getFlags();
    void setFlags(int flags);
    int getStartIndex();
    void setStartIndex(int startIndex);
private:
    string jointName;
    int parent;
    int flags;
    int startIndex;
};

#endif // MD5ANIMJOINT_H
