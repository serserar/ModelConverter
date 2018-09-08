/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef MVECTOR2_H
#define MVECTOR2_H
#include "math.h"

template <class Real>
class MVector2 {
public:
    MVector2();
    MVector2(const MVector2<Real>& other);
    MVector2(Real x, Real y);
    ~MVector2()=default;
    float GetX();
    void SetX(Real x);
    float GetY();
    void SetY(Real y);

private:
    Real x;
    Real y;
};

template<class Real>
MVector2<Real>::MVector2() {
    this->x = Real(0);
    this->y = Real(0);
}

template<class Real>
MVector2<Real>::MVector2(const MVector2<Real>& other)
{
    this->x=other.x;
    this->y=other.y;
}

template<class Real>
MVector2<Real>::MVector2(Real x, Real y) {
    this->x = x;
    this->y = y;
}

template<class Real>
float MVector2<Real>::GetX() {
    return this->x;
}

template<class Real>
void MVector2<Real>::SetX(Real x) {
    this->x = x;
}

template<class Real>
float MVector2<Real>::GetY() {
    return this->y;
}

template<class Real>
void MVector2<Real>::SetY(Real y) {
    this->y = y;
}

#endif // MVECTOR2_H
