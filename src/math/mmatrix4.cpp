/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
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

#include "mmatrix4.h"

template <class Real>
MMatrix4<Real>::MMatrix4() {

}

template <class Real>
MMatrix4<Real>::MMatrix4(const MMatrix4& other) {

}

template <class Real>
MMatrix4<Real>::~MMatrix4() {

}


template<class Real>
Real MMatrix4<Real>::operator[](int i) {
    return mcomponents[i];
}

template<class Real>
void MMatrix4<Real>::set(Real c00, Real c01, Real c02, Real c03,
        Real c10, Real c11, Real c12, Real c13,
        Real c20, Real c21, Real c22, Real c23,
        Real c30, Real c31, Real c32, Real c33) {
    mcomponents[0] = c00;
    mcomponents[1] = c01;
    mcomponents[2] = c02;
    mcomponents[3] = c03;
    mcomponents[4] = c10;
    mcomponents[5] = c11;
    mcomponents[6] = c12;
    mcomponents[7] = c13;
    mcomponents[8] = c20;
    mcomponents[9] = c21;
    mcomponents[10] = c22;
    mcomponents[11] = c23;
    mcomponents[12] = c30;
    mcomponents[13] = c31;
    mcomponents[14] = c32;
    mcomponents[15] = c33;
}

template<class Real>
void MMatrix4<Real>::setTranspose(MMatrix4<Real>& matrix) {

    mcomponents[0] = matrix[0];
    mcomponents[1] = matrix[4];
    mcomponents[2] = matrix[8];
    mcomponents[3] = matrix[12];
    mcomponents[4] = matrix[1];
    mcomponents[5] = matrix[5];
    mcomponents[6] = matrix[9];
    mcomponents[7] = matrix[13];
    mcomponents[8] = matrix[2];
    mcomponents[9] = matrix[6];
    mcomponents[10] = matrix[10];
    mcomponents[11] = matrix[14];
    mcomponents[12] = matrix[3];
    mcomponents[13] = matrix[7];
    mcomponents[14] = matrix[11];
    mcomponents[15] = matrix[15];
}

template<class Real>
void MMatrix4<Real>::transpose() {
    setTranspose(*this);
}

template<class Real>
Real* MMatrix4<Real>::getArray() {
    Real* marray = new Real[16];
    marray[0] = mcomponents[0];
    marray[1] = mcomponents[1];
    marray[2] = mcomponents[2];
    marray[3] = mcomponents[3];
    marray[4] = mcomponents[4];
    marray[5] = mcomponents[5];
    marray[6] = mcomponents[6];
    marray[7] = mcomponents[7];
    marray[8] = mcomponents[8];
    marray[9] = mcomponents[9];
    marray[10] = mcomponents[10];
    marray[11] = mcomponents[11];
    marray[12] = mcomponents[12];
    marray[13] = mcomponents[13];
    marray[14] = mcomponents[14];
    marray[15] = mcomponents[15];
    return marray;
}


