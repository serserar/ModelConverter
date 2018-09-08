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

#ifndef MMATRIX3_H
#define MMATRIX3_H

#include "MVector3.h"

template <class Real>
class MMatrix3 {
public:
    MMatrix3();
    MMatrix3(Real c00, Real c01, Real c02,
             Real c10, Real c11, Real c12,
             Real c20, Real c21, Real c22);
    MMatrix3(MVector3<Real>& row1,
             MVector3<Real>& row2,
             MVector3<Real>& row3);
    MMatrix3(MMatrix3<Real>& other);
    ~MMatrix3();
    /*!transform the reference vector by this matrix*/
    MVector3<Real>* operator*(MVector3<Real>& vector);
    MMatrix3<Real>* operator*(MMatrix3<Real>& matrix);
    MMatrix3<Real> mult(MMatrix3<Real>& matrix, MMatrix3<Real>& store);
    void operator*=(MMatrix3<Real>& matrix);
    Real operator[](int i);
    Real operator()(int i, int j) const;
    Real& operator()(int i, int j);
    void set(Real c00, Real c01, Real c02,
             Real c10, Real c11, Real c12,
             Real c20, Real c21, Real c22);
    void set(int i,int j, Real value);
    Real get(int i, int j);
    Real getM00() const;
    Real getM01() const;
    Real getM02() const;
    Real getM10() const;
    Real getM11() const;
    Real getM12() const;
    Real getM20() const;
    Real getM21() const;
    Real getM22() const;
    void setM00(Real c00);
    void setM01(Real c01);
    void setM02(Real c02);
    void setM10(Real c10);
    void setM11(Real c11);
    void setM12(Real c12);
    void setM20(Real c20);
    void setM21(Real c21);
    void setM22(Real c22);
    void Set(const MMatrix3<Real>& matrix);
    void setInverse(MMatrix3<Real>& matrix);
    void invert();
    void setTranspose(MMatrix3<Real>& matrix);
    void transpose();
    void setIdentity();
    MVector3<Real> ApplyPost(MVector3<Real>& point);
    MMatrix3<Real>& fromAngleAxis(Real angle, MVector3<Real>& axis);
    MMatrix3<Real>& fromAngleNormalAxis(Real angle, MVector3<Real>& axis);
    MMatrix3<Real>& fromEulerAnglesXYZ(Real xRangle, Real yRangle, Real zRangle);
    MMatrix3<Real>& fromEulerAnglesXZY(Real xRangle, Real yRangle, Real zRangle);
    MMatrix3<Real>& fromEulerAnglesYXZ(Real xRangle, Real yRangle, Real zRangle);
    MMatrix3<Real>& fromEulerAnglesYZX(Real xRangle, Real yRangle, Real zRangle);
    MMatrix3<Real>& fromEulerAnglesZXY(Real xRangle, Real yRangle, Real zRangle);
    MMatrix3<Real>& fromEulerAnglesZYX(Real xRangle, Real yRangle, Real zRangle);
    static MMatrix3<Real> GetInstance(MVector3<Real>& rot);
    static MMatrix3<Real> GetInstance(MVector3<Real>& rot, MMatrix3<Real>& store);
private:
    Real mcomponents[9];

    inline friend std::ostream& operator<<(std::ostream& output, MMatrix3<Real>& matrix) {
        output << "["
               << matrix[0] << " " << matrix[1] << " " << matrix[2] << std::endl
               << matrix[3] << " " << matrix[4] << " " << matrix[5] << std::endl
               << matrix[6] << " " << matrix[7] << " " << matrix[8] << std::endl
               << "]";
        return output;
    }

};

template <class Real>
MMatrix3<Real>::MMatrix3() {

}

template <class Real>
MMatrix3<Real>::MMatrix3(T c00, T c01, T c02, T c10, T c11, T c12, T c20, T c21, T c22) {
    mcomponents[0] = c00;
    mcomponents[1] = c01;
    mcomponents[2] = c02;
    mcomponents[3] = c10;
    mcomponents[4] = c11;
    mcomponents[5] = c12;
    mcomponents[6] = c20;
    mcomponents[7] = c21;
    mcomponents[8] = c22;
}

template <class Real>
MMatrix3<Real>::MMatrix3(MVector3<Real>& row1,
                         MVector3<Real>& row2,
                         MVector3<Real>& row3) {
    mcomponents[0] = row1.getX();
    mcomponents[1] = row1.getY();
    mcomponents[2] = row1.getZ();
    mcomponents[3] = row2.getX();
    mcomponents[4] = row2.getY();
    mcomponents[5] = row2.getZ();
    mcomponents[6] = row3.getX();
    mcomponents[7] = row3.getY();
    mcomponents[8] = row3.getZ();
}

template <class Real>
MMatrix3<Real>::MMatrix3(MMatrix3<Real>& other) {
    mcomponents[0] = other[0];
    mcomponents[1] = other[1];
    mcomponents[2] = other[2];
    mcomponents[3] = other[3];
    mcomponents[4] = other[4];
    mcomponents[5] = other[5];
    mcomponents[6] = other[6];
    mcomponents[7] = other[7];
    mcomponents[8] = other[8];
}

template <class Real>
MMatrix3<Real>::~MMatrix3() {

}

template <class Real>
Real MMatrix3<Real>::operator[](int i) {
    return mcomponents[i];
}

template <class Real>
Real MMatrix3<Real>::operator()(int i, int j) const {
    return mcomponents[i * 3 + j];
}

template <class Real>
Real& MMatrix3<Real>::operator()(int i, int j)
{
    return mcomponents[i * 3 + j];
}

template <class Real>
MVector3<Real>* MMatrix3<Real>::operator*(MVector3<Real>& vector) {
    MVector3<Real>* tvector = new MVector3<Real>(vector.GetX() * mcomponents[0] +
            vector.GetY() * mcomponents[1] +
            vector.GetZ() * mcomponents[2],
            vector.GetX() * mcomponents[3] +
            vector.GetY() * mcomponents[4] +
            vector.GetZ() * mcomponents[5],
            vector.GetX() * mcomponents[6] +
            vector.GetY() * mcomponents[7] +
            vector.GetZ() * mcomponents[8]
                                                );
    return tvector;
}

template <class Real>
MMatrix3<Real>* MMatrix3<Real>::operator*(MMatrix3<Real>& matrix) {
    MMatrix3<Real>* mmatrix = new MMatrix3<Real>(
        mcomponents[0] * matrix[0] +
        mcomponents[1] * matrix[3] +
        mcomponents[2] * matrix[6],
        mcomponents[0] * matrix[1] +
        mcomponents[1] * matrix[4] +
        mcomponents[2] * matrix[7],
        mcomponents[0] * matrix[2] +
        mcomponents[1] * matrix[5] +
        mcomponents[2] * matrix[8],

        mcomponents[3] * matrix[0] +
        mcomponents[4] * matrix[3] +
        mcomponents[5] * matrix[6],
        mcomponents[3] * matrix[1] +
        mcomponents[4] * matrix[4] +
        mcomponents[5] * matrix[7],
        mcomponents[3] * matrix[2] +
        mcomponents[4] * matrix[5] +
        mcomponents[5] * matrix[8],

        mcomponents[6] * matrix[0] +
        mcomponents[7] * matrix[3] +
        mcomponents[8] * matrix[6],
        mcomponents[6] * matrix[1] +
        mcomponents[7] * matrix[4] +
        mcomponents[8] * matrix[7],
        mcomponents[6] * matrix[2] +
        mcomponents[7] * matrix[5] +
        mcomponents[8] * matrix[8]
    );
    return mmatrix;
}

template <class Real>
void MMatrix3<Real>::operator*=(MMatrix3<Real>& matrix) {
    mcomponents[0] = mcomponents[0] * matrix[0] +
                     mcomponents[1] * matrix[3] +
                     mcomponents[2] * matrix[6];

    mcomponents[1] = mcomponents[0] * matrix[1] +
                     mcomponents[1] * matrix[4] +
                     mcomponents[2] * matrix[7];

    mcomponents[2] = mcomponents[0] * matrix[2] +
                     mcomponents[1] * matrix[5] +
                     mcomponents[2] * matrix[8];

    mcomponents[3] = mcomponents[3] * matrix[0] +
                     mcomponents[4] * matrix[3] +
                     mcomponents[5] * matrix[6];

    mcomponents[4] = mcomponents[3] * matrix[1] +
                     mcomponents[4] * matrix[4] +
                     mcomponents[5] * matrix[7];

    mcomponents[5] = mcomponents[3] * matrix[2] +
                     mcomponents[4] * matrix[5] +
                     mcomponents[5] * matrix[8];

    mcomponents[6] = mcomponents[6] * matrix[0] +
                     mcomponents[7] * matrix[3] +
                     mcomponents[8] * matrix[6];

    mcomponents[7] = mcomponents[6] * matrix[1] +
                     mcomponents[7] * matrix[4] +
                     mcomponents[8] * matrix[7];

    mcomponents[8] = mcomponents[6] * matrix[2] +
                     mcomponents[7] * matrix[5] +
                     mcomponents[8] * matrix[8];
}

template<class Real>
MMatrix3<Real> MMatrix3<Real>::mult(MMatrix3<Real>& matrix, MMatrix3<Real>& store)
{
    store.setM00(mcomponents[0] * matrix.getM00() +
                 mcomponents[1] * matrix.getM10() +
                 mcomponents[2] * matrix.getM20());
    store.setM01(mcomponents[0] * matrix.getM01() +
                 mcomponents[1] * matrix.getM11() +
                 mcomponents[2] * matrix.getM21());
    store.setM02(mcomponents[0] * matrix.getM02()+
                 mcomponents[1] * matrix.getM12() +
                 mcomponents[2] * matrix.getM22());
    store.setM10(mcomponents[3] * matrix.getM00() +
                 mcomponents[4] * matrix.getM10() +
                 mcomponents[5] * matrix.getM20());
    store.setM11(mcomponents[3] * matrix.getM01() +
                 mcomponents[4] * matrix.getM11() +
                 mcomponents[5] * matrix.getM21());
    store.setM12(mcomponents[3] * matrix.getM02() +
                 mcomponents[4] * matrix.getM12() +
                 mcomponents[5] * matrix.getM22());
    store.setM20(mcomponents[6] * matrix.getM00() +
                 mcomponents[7] * matrix.getM10() +
                 mcomponents[8] * matrix.getM20());
    store.setM21(mcomponents[6] * matrix.getM01() +
                 mcomponents[7] * matrix.getM11() +
                 mcomponents[8] * matrix.getM21());
    store.setM22(mcomponents[6] * matrix.getM02() +
                 mcomponents[7] * matrix.getM12() +
                 mcomponents[8] * matrix.getM22());
    return store;
}


template<class Real>
void MMatrix3<Real>::set(Real c00, Real c01, Real c02, Real c10, Real c11,
                         Real c12, Real c20, Real c21, Real c22) {
    mcomponents[0] = c00;
    mcomponents[1] = c01;
    mcomponents[2] = c02;
    mcomponents[3] = c10;
    mcomponents[4] = c11;
    mcomponents[5] = c12;
    mcomponents[6] = c20;
    mcomponents[7] = c21;
    mcomponents[8] = c22;
}

template<class Real>
void MMatrix3<Real>::set(int i, int j, Real value)
{
    mcomponents[i * 3 + j]=value;
}

template<class Real>
Real MMatrix3<Real>::get(int i, int j)
{
    return mcomponents[i * 3 + j];
}

template<class Real>
Real MMatrix3<Real>::getM00() const{
    return mcomponents[0];
}

template<class Real>
Real MMatrix3<Real>::getM01() const{
    return mcomponents[1];
}

template<class Real>
Real MMatrix3<Real>::getM02() const{
    return mcomponents[2];
}


template<class Real>
Real MMatrix3<Real>::getM10() const{
    return mcomponents[3];
}

template<class Real>
Real MMatrix3<Real>::getM11() const{
    return mcomponents[4];
}

template<class Real>
Real MMatrix3<Real>::getM12() const{
    return mcomponents[5];
}


template<class Real>
Real MMatrix3<Real>::getM20() const{
    return mcomponents[6];
}

template<class Real>
Real MMatrix3<Real>::getM21() const{
    return mcomponents[7];
}

template<class Real>
Real MMatrix3<Real>::getM22() const{
    return mcomponents[8];
}

template<class Real>
void MMatrix3<Real>::setM00(Real c00)
{
    this->mcomponents[0]=c00;
}

template<class Real>
void MMatrix3<Real>::setM01(Real c01)
{
    this->mcomponents[1]=c01;
}

template<class Real>
void MMatrix3<Real>::setM02(Real c02)
{
    this->mcomponents[2]=c02;
}

template<class Real>
void MMatrix3<Real>::setM10(Real c10)
{
    this->mcomponents[3]=c10;
}

template<class Real>
void MMatrix3<Real>::setM11(Real c11)
{
    this->mcomponents[4]=c11;
}

template<class Real>
void MMatrix3<Real>::setM12(Real c12)
{
    this->mcomponents[5]=c12;
}

template<class Real>
void MMatrix3<Real>::setM20(Real c20)
{
    this->mcomponents[6]=c20;
}

template<class Real>
void MMatrix3<Real>::setM21(Real c21)
{
    this->mcomponents[7]=c21;
}

template<class Real>
void MMatrix3<Real>::setM22(Real c22)
{
    this->mcomponents[8]=c22;
}

template<class Real> 
void MMatrix3<Real>::Set(const MMatrix3<Real>& matrix)
{
    mcomponents[0] = matrix.getM00();
    mcomponents[1] = matrix.getM01();
    mcomponents[2] = matrix.getM02();
    mcomponents[3] = matrix.getM10();
    mcomponents[4] = matrix.getM11();
    mcomponents[5] = matrix.getM12();
    mcomponents[6] = matrix.getM20();
    mcomponents[7] = matrix.getM21();
    mcomponents[8] = matrix.getM22();
}


template <class Real>
void MMatrix3<Real>::setInverse(MMatrix3<Real>& matrix) {
    MMatrix3<Real> tmpmat(matrix);
    Real t1 = tmpmat[0] * tmpmat[4];
    Real t2 = tmpmat[0] * tmpmat[5];
    Real t3 = tmpmat[1] * tmpmat[3];
    Real t4 = tmpmat[2] * tmpmat[3];
    Real t5 = tmpmat[1] * tmpmat[6];
    Real t6 = tmpmat[2] * tmpmat[6];

    //calculate the determinant
    Real determinant = t1 * tmpmat[8] - t2 * tmpmat[7] - t3 * tmpmat[8] +
                       t4 * tmpmat[7] + t5 * tmpmat[5] - t6 * tmpmat[4];
    //check if determinant is non-zero
    if (determinant != 0) {
        Real invd = Real(1) / determinant;
        mcomponents[0] = (tmpmat[4] * tmpmat[8] - tmpmat[5] * tmpmat[7]) * invd;
        mcomponents[1] = -(tmpmat[1] * tmpmat[8] - tmpmat[2] * tmpmat[7]) * invd;
        mcomponents[2] = (tmpmat[1] * tmpmat[5] - tmpmat[2] * tmpmat[4]) * invd;
        mcomponents[3] = -(tmpmat[3] * tmpmat[8] - tmpmat[5] * tmpmat[6]) * invd;
        mcomponents[4] = (tmpmat[0] * tmpmat[8] - t6) * invd;
        mcomponents[5] = -(t2 - t4) * invd;
        mcomponents[6] = (tmpmat[3] * tmpmat[7] - tmpmat[4] * tmpmat[6]) * invd;
        mcomponents[7] = -(tmpmat[0] * tmpmat[7] - t5) * invd;
        mcomponents[8] = (t1 - t3) * invd;
    }
}

template <class Real>
void MMatrix3<Real>::invert() {
    setInverse(*this);
}

template <class Real>
void MMatrix3<Real>::setTranspose(MMatrix3<Real>& matrix) {
    MMatrix3<Real> tmpmat(matrix);
    mcomponents[0] = tmpmat[0];
    mcomponents[1] = tmpmat[3];
    mcomponents[2] = tmpmat[6];
    mcomponents[3] = tmpmat[1];
    mcomponents[4] = tmpmat[4];
    mcomponents[5] = tmpmat[7];
    mcomponents[6] = tmpmat[2];
    mcomponents[7] = tmpmat[5];
    mcomponents[8] = tmpmat[8];
}

template <class Real>
void MMatrix3<Real>::transpose() {
    setTranspose(*this);
}
template <class Real>
void MMatrix3<Real>::setIdentity()
{
    mcomponents[0] = Real(1);
    mcomponents[1] = Real(0);
    mcomponents[2] = Real(0);
    mcomponents[3] = Real(0);
    mcomponents[4] = Real(1);
    mcomponents[5] = Real(0);
    mcomponents[6] = Real(0);
    mcomponents[7] = Real(0);
    mcomponents[8] = Real(1);
}

/*
 *
 */
template <class Real>
MVector3<Real> MMatrix3<Real>::ApplyPost(MVector3<Real>& point)
{
    MVector3<Real> tpoint;
    tpoint.SetX(getM00() * point.GetX() + getM01() * point.GetY() + getM02() * point.GetZ());
    tpoint.SetY(getM10() * point.GetX() + getM11() * point.GetY() + getM12() * point.GetZ());
    tpoint.SetZ(getM20() * point.GetX() + getM21() * point.GetY() + getM22() * point.GetZ());
    return tpoint;
}


template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromAngleAxis(Real angle, MVector3<Real>& axis) {
    MVector3<Real> normAxis(axis);
    normAxis.normalize();
    fromAngleNormalAxis(angle, normAxis);
    return *this;
}


template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromAngleNormalAxis(Real angle, MVector3<Real>& axis) {
    Real fCos = Math<Real>::Cos(angle);
    Real fSin = Math<Real>::Sin(angle);
    Real fOneMinusCos = 1.0 - fCos;
    Real fX2 = axis.GetX() * axis.GetX();
    Real fY2 = axis.GetY() * axis.GetY();
    Real fZ2 = axis.GetZ() * axis.GetZ();
    Real fXYM = axis.GetX() * axis.GetY() * fOneMinusCos;
    Real fXZM = axis.GetX() * axis.GetZ() * fOneMinusCos;
    Real fYZM = axis.GetY() * axis.GetZ() * fOneMinusCos;
    Real fXSin = axis.GetX() * fSin;
    Real fYSin = axis.GetY() * fSin;
    Real fZSin = axis.GetZ() * fSin;

    mcomponents[0] = fX2 * fOneMinusCos + fCos;
    mcomponents[1] = fXYM - fZSin;
    mcomponents[2] = fXZM + fYSin;
    mcomponents[3] = fXYM + fZSin;
    mcomponents[4] = fY2 * fOneMinusCos + fCos;
    mcomponents[5] = fYZM - fXSin;
    mcomponents[6] = fXZM - fYSin;
    mcomponents[7] = fYZM + fXSin;
    mcomponents[8] = fZ2 * fOneMinusCos + fCos;
    return *this;
}

template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromEulerAnglesXYZ(Real xRangle, Real yRangle,
        Real zRangle) {
    Real fCos = Math<Real>::Cos(xRangle);
    Real fSin = Math<Real>::Sin(xRangle);
    MMatrix3 xMat(
        (Real) 1.0, (Real) 0.0, (Real) 0.0,
        (Real) 0.0, fCos, -fSin,
        (Real) 0.0, fSin, fCos);

    fCos = Math<Real>::Cos(yRangle);
    fSin = Math<Real>::Sin(yRangle);
    MMatrix3 yMat(
        fCos, (Real) 0.0, fSin,
        (Real) 0.0, (Real) 1.0, (Real) 0.0,
        -fSin, (Real) 0.0, fCos);

    fCos = Math<Real>::Cos(zRangle);
    fSin = Math<Real>::Sin(zRangle);
    MMatrix3 zMat(
        fCos, -fSin, (Real) 0.0,
        fSin, fCos, (Real) 0.0,
        (Real) 0.0, (Real) 0.0, (Real) 1.0);

    *this = xMat * (yMat * zMat);
    return *this;
}

template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromEulerAnglesXZY(Real xRangle, Real yRangle,
        Real zRangle) {
    Real fCos = Math<Real>::Cos(xRangle);
    Real fSin = Math<Real>::Sin(xRangle);
    MMatrix3 xMat(
        (Real) 1.0, (Real) 0.0, (Real) 0.0,
        (Real) 0.0, fCos, -fSin,
        (Real) 0.0, fSin, fCos);

    fCos = Math<Real>::Cos(yRangle);
    fSin = Math<Real>::Sin(yRangle);
    MMatrix3 yMat(
        fCos, (Real) 0.0, fSin,
        (Real) 0.0, (Real) 1.0, (Real) 0.0,
        -fSin, (Real) 0.0, fCos);

    fCos = Math<Real>::Cos(zRangle);
    fSin = Math<Real>::Sin(zRangle);
    MMatrix3 zMat(
        fCos, -fSin, (Real) 0.0,
        fSin, fCos, (Real) 0.0,
        (Real) 0.0, (Real) 0.0, (Real) 1.0);

    *this = xMat * (zMat * yMat);
    return *this;
}

template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromEulerAnglesYXZ(Real xRangle, Real yRangle,
        Real zRangle) {
    Real fCos = Math<Real>::Cos(xRangle);
    Real fSin = Math<Real>::Sin(xRangle);
    MMatrix3 xMat(
        (Real) 1.0, (Real) 0.0, (Real) 0.0,
        (Real) 0.0, fCos, -fSin,
        (Real) 0.0, fSin, fCos);

    fCos = Math<Real>::Cos(yRangle);
    fSin = Math<Real>::Sin(yRangle);
    MMatrix3 yMat(
        fCos, (Real) 0.0, fSin,
        (Real) 0.0, (Real) 1.0, (Real) 0.0,
        -fSin, (Real) 0.0, fCos);

    fCos = Math<Real>::Cos(zRangle);
    fSin = Math<Real>::Sin(zRangle);
    MMatrix3 zMat(
        fCos, -fSin, (Real) 0.0,
        fSin, fCos, (Real) 0.0,
        (Real) 0.0, (Real) 0.0, (Real) 1.0);

    *this = yMat * (xMat * zMat);
    return *this;
}

template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromEulerAnglesYZX(Real xRangle, Real yRangle,
        Real zRangle) {
    Real fCos = Math<Real>::Cos(xRangle);
    Real fSin = Math<Real>::Sin(xRangle);
    MMatrix3 xMat(
        (Real) 1.0, (Real) 0.0, (Real) 0.0,
        (Real) 0.0, fCos, -fSin,
        (Real) 0.0, fSin, fCos);

    fCos = Math<Real>::Cos(yRangle);
    fSin = Math<Real>::Sin(yRangle);
    MMatrix3 yMat(
        fCos, (Real) 0.0, fSin,
        (Real) 0.0, (Real) 1.0, (Real) 0.0,
        -fSin, (Real) 0.0, fCos);

    fCos = Math<Real>::Cos(zRangle);
    fSin = Math<Real>::Sin(zRangle);
    MMatrix3 zMat(
        fCos, -fSin, (Real) 0.0,
        fSin, fCos, (Real) 0.0,
        (Real) 0.0, (Real) 0.0, (Real) 1.0);

    *this = yMat * (zMat * xMat);
    return *this;
}

template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromEulerAnglesZXY(Real xRangle, Real yRangle,
        Real zRangle) {
    Real fCos = Math<Real>::Cos(xRangle);
    Real fSin = Math<Real>::Sin(xRangle);
    MMatrix3 xMat(
        (Real) 1.0, (Real) 0.0, (Real) 0.0,
        (Real) 0.0, fCos, -fSin,
        (Real) 0.0, fSin, fCos);

    fCos = Math<Real>::Cos(yRangle);
    fSin = Math<Real>::Sin(yRangle);
    MMatrix3 yMat(
        fCos, (Real) 0.0, fSin,
        (Real) 0.0, (Real) 1.0, (Real) 0.0,
        -fSin, (Real) 0.0, fCos);

    fCos = Math<Real>::Cos(zRangle);
    fSin = Math<Real>::Sin(zRangle);
    MMatrix3 zMat(
        fCos, -fSin, (Real) 0.0,
        fSin, fCos, (Real) 0.0,
        (Real) 0.0, (Real) 0.0, (Real) 1.0);

    *this = zMat * (xMat * yMat);
    return *this;
}

template<class Real>
MMatrix3<Real>& MMatrix3<Real>::fromEulerAnglesZYX(Real xRangle, Real yRangle,
        Real zRangle) {
    Real fCos = Math<Real>::Cos(xRangle);
    Real fSin = Math<Real>::Sin(xRangle);
    MMatrix3 xMat(
        (Real) 1.0, (Real) 0.0, (Real) 0.0,
        (Real) 0.0, fCos, -fSin,
        (Real) 0.0, fSin, fCos);

    fCos = Math<Real>::Cos(yRangle);
    fSin = Math<Real>::Sin(yRangle);
    MMatrix3 yMat(
        fCos, (Real) 0.0, fSin,
        (Real) 0.0, (Real) 1.0, (Real) 0.0,
        -fSin, (Real) 0.0, fCos);

    fCos = Math<Real>::Cos(zRangle);
    fSin = Math<Real>::Sin(zRangle);
    MMatrix3 zMat(
        fCos, -fSin, (Real) 0.0,
        fSin, fCos, (Real) 0.0,
        (Real) 0.0, (Real) 0.0, (Real) 1.0);

    *this = zMat * (yMat * xMat);
    return *this;
}

/**
* Method that creates rotation Matrix3f from Vector3f with axis rotation.
* @param rot : Vector3f with axis rotation.
* @return Matrix3f : builded rotation Matrix3f.
*/
template<class Real>
MMatrix3<Real> MMatrix3<Real>::GetInstance(MVector3<Real>& rot)
{
    MMatrix3<Real> m1;
    MMatrix3<Real> m2;
    MMatrix3<Real> m3;
    MVector3<Real> unitx(1.0, 0.0, 0.0);
    MVector3<Real> unity(0.0, 1.0, 0.0);
    MVector3<Real> unitz(0.0, 0.0, 1.0);
    m1.fromAngleAxis(rot.GetX(), unitx);
    m2.fromAngleAxis(rot.GetY(), unity);
    m3.fromAngleAxis(rot.GetZ(), unitz);
    MMatrix3<Real> m21;
    MMatrix3<Real> result;
    m2.mult(m1, m21);
    m3.mult(m21, result);
    return result;
}

/**
* Method that creates rotation Matrix3f from Vector3f with axis rotation.
* @param rot : Vector3f with axis rotation.
* @return Matrix3f : builded rotation Matrix3f.
*/
template<class Real>
MMatrix3<Real> MMatrix3<Real>::GetInstance(MVector3<Real>& rot, MMatrix3<Real>& store)
{
    MMatrix3<Real> m1;
    MMatrix3<Real> m2;
    MMatrix3<Real> m3;
    MVector3<Real> unitx(1.0, 0.0, 0.0);
    MVector3<Real> unity(0.0, 1.0, 0.0);
    MVector3<Real> unitz(0.0, 0.0, 1.0);
    m1.fromAngleAxis(rot.GetX(), unitx);
    m2.fromAngleAxis(rot.GetY(), unity);
    m3.fromAngleAxis(rot.GetZ(), unitz);
    MMatrix3<Real> m21;
    m2.mult(m1, m21);
    m3.mult(m21, store);
    return store;
}

#endif // MMATRIX3_H
