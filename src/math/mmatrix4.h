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

#ifndef MMATRIX4_H
#define MMATRIX4_H
#include "MVector3.h"

template <class Real>
class MMatrix4 {
public:
    MMatrix4();
    MMatrix4(const MMatrix4& other);
    ~MMatrix4();
    Real operator[](int i);
    void set(Real c00, Real c01, Real c02, Real c03,
            Real c10, Real c11, Real c12, Real c13,
            Real c20, Real c21, Real c22, Real c23,
            Real c30, Real c31, Real c32, Real c33);
    void setTranspose(MMatrix4<Real>& matrix);
    void transpose();
    void projectionMatrix (const MVector3<Real> &n);
    Real* getArray();
    Real getM00();
    Real getM01();
    Real getM02();
    Real getM03();
    Real getM10();
    Real getM11();
    Real getM12();
    Real getM13();
    Real getM20();
    Real getM21();
    Real getM22();
    Real getM23();
    Real getM30();
    Real getM31();
    Real getM32();
    Real getM33();
    void setM00(Real c00);
    void setM01(Real c01);
    void setM02(Real c02);
    void setM03(Real c03);
    void setM10(Real c10);
    void setM11(Real c11);
    void setM12(Real c12);
    void setM13(Real c13);
    void setM20(Real c20);
    void setM21(Real c21);
    void setM22(Real c22);
    void setM23(Real c23);
    void setM30(Real c30);
    void setM31(Real c31);
    void setM32(Real c32);
    void setM33(Real c33);
private:
    Real mcomponents[16];

    inline friend std::ostream& operator<<(std::ostream& output, MMatrix4<Real>& matrix) {
        output << "("
                << matrix[0] << ", " << matrix[1] << ", " << matrix[2] << ", " << matrix[3] << std::endl
                << matrix[4] << ", " << matrix[5] << ", " << matrix[6] << ", " << matrix[7] << std::endl
                << matrix[8] << ", " << matrix[9] << ", " << matrix[10] << ", " << matrix[11] << std::endl
                << matrix[12] << ", " << matrix[13] << ", " << matrix[14] << ", " << matrix[15] << std::endl
                << ")";
        return output;
    }

    
};

template <class Real>
MMatrix4<Real>::MMatrix4() {

}

template <class Real>
MMatrix4<Real>::MMatrix4(const MMatrix4& other) {
    mcomponents[0] = other.getM00();
    mcomponents[1] = other.getM01();
    mcomponents[2] = other.getM02();
    mcomponents[3] = other.getM03();
    mcomponents[4] = other.getM10();
    mcomponents[5] = other.getM11();
    mcomponents[6] = other.getM12();
    mcomponents[7] = other.getM13();
    mcomponents[8] = other.getM20();
    mcomponents[9] = other.getM21();
    mcomponents[10] = other.getM22();
    mcomponents[11] = other.getM23();
    mcomponents[12] = other.getM30();
    mcomponents[13] = other.getM31();
    mcomponents[14] = other.getM32();
    mcomponents[15] = other.getM33();
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

/**
 * 
 * ProjectionMatrix
 * Setup the matrix to perform a projection onto a plane passing
 * through the origin.  The plane is perpendicular to the
 * unit vector n.
 * 
 */
template<class Real> 
void MMatrix4<Real>::projectionMatrix(const MVector3<Real>& n)
{
  MMatrix4<Real> res;

  // Quick sanity check to make sure they passed in a unit vector
  // to specify the axis
  assert (fabs (n.dotProduct(n) - 1.0) < 0.001);

  // Fill in the matrix elements.  We'll do the common
  // subexpression optimization ourselves here, since diagonally
  // opposite matrix elements are equal
  res.setM01(1.0 - (n.getX() * n.getX()));
  res.setM12(1.0 - (n.getY() * n.getY()));
  res.setM23(1.0 - (n.getZ() * n.getZ()));

  res.setM02(-(n.getX() * n.getY()));
  res.setM11(res.getM02());
  res.setM03(-(n.getX()* n.getZ()));
  res.setM21(res.getM03());
  res.setM13(-(n.getY() * n.getZ()));
  res.setM22(res.get13());

  // Reset the translation portion
  res.setM31(0.0);
  res.setM32(0.0);
  res.setM33(0.0);

  return res;
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

template<class Real>
Real MMatrix4<Real>::getM00(){
    return mcomponents[0];
}

template<class Real>
Real MMatrix4<Real>::getM01(){
    return mcomponents[1];
}

template<class Real>
Real MMatrix4<Real>::getM02(){
    return mcomponents[2];
}

template<class Real>
Real MMatrix4<Real>::getM03(){
    return mcomponents[3];
}

template<class Real>
Real MMatrix4<Real>::getM10(){
    return mcomponents[4];
}

template<class Real>
Real MMatrix4<Real>::getM11(){
    return mcomponents[5];
}

template<class Real>
Real MMatrix4<Real>::getM12(){
    return mcomponents[6];
}

template<class Real>
Real MMatrix4<Real>::getM13(){
    return mcomponents[7];
}

template<class Real>
Real MMatrix4<Real>::getM20(){
    return mcomponents[8];
}

template<class Real>
Real MMatrix4<Real>::getM21(){
    return mcomponents[9];
}

template<class Real>
Real MMatrix4<Real>::getM22(){
    return mcomponents[10];
}

template<class Real>
Real MMatrix4<Real>::getM23(){
    return mcomponents[11];
}

template<class Real>
Real MMatrix4<Real>::getM30(){
    return mcomponents[12];
}

template<class Real>
Real MMatrix4<Real>::getM31(){
    return mcomponents[13];
}

template<class Real>
Real MMatrix4<Real>::getM32(){
    return mcomponents[14];
}

template<class Real>
Real MMatrix4<Real>::getM33(){
    return mcomponents[15];
}

template<class Real> 
void MMatrix4<Real>::setM00(Real c00)
{
    this->mcomponents[0]=c00;
}

template<class Real> 
void MMatrix4<Real>::setM01(Real c01)
{
    this->mcomponents[1]=c01;
}

template<class Real> 
void MMatrix4<Real>::setM02(Real c02)
{
    this->mcomponents[2]=c02;
}

template<class Real> 
void MMatrix4<Real>::setM03(Real c03)
{
    this->mcomponents[3]=c03;
}

template<class Real> 
void MMatrix4<Real>::setM10(Real c10)
{
    this->mcomponents[4]=c10;
}

template<class Real> 
void MMatrix4<Real>::setM11(Real c11)
{
    this->mcomponents[5]=c11;
}

template<class Real> 
void MMatrix4<Real>::setM12(Real c12)
{
    this->mcomponents[6]=c12;
}

template<class Real> 
void MMatrix4<Real>::setM13(Real c13)
{
    this->mcomponents[7]=c13;
}

template<class Real> 
void MMatrix4<Real>::setM20(Real c20)
{
    this->mcomponents[8]=c20;
}

template<class Real> 
void MMatrix4<Real>::setM21(Real c21)
{
    this->mcomponents[9]=c21;
}

template<class Real> 
void MMatrix4<Real>::setM22(Real c22)
{
    this->mcomponents[10]=c22;
}

template<class Real> 
void MMatrix4<Real>::setM23(Real c23)
{
    this->mcomponents[11]=c23;
}

template<class Real> 
void MMatrix4<Real>::setM30(Real c30)
{
    this->mcomponents[12]=c30;
}

template<class Real> 
void MMatrix4<Real>::setM31(Real c31)
{
    this->mcomponents[13]=c31;
}

template<class Real> 
void MMatrix4<Real>::setM32(Real c32)
{
    this->mcomponents[14]=c32;
}

template<class Real> 
void MMatrix4<Real>::setM33(Real c33)
{
    this->mcomponents[15]=c33;
}
//#include "mmatrix4.cpp"
#endif // MMATRIX4_H
