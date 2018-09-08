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

#ifndef MVECTOR3_H
#define MVECTOR3_H
#include "math.h"


template<class Real>
class MVector3 {
public:

    MVector3();
    MVector3(Real x, Real y, Real z);
    MVector3(const MVector3<Real>& vector);
    ~MVector3();
    Real GetX() const;
    void SetX(Real x);
    Real GetY() const;
    void SetY(Real y);
    Real GetZ() const;
    void SetZ(Real z);
    Real* getArray();
    void set(Real x, Real y, Real z);
    void Set(const MVector3<Real>& vector);
    /*! add operations */
    void operator+=(const MVector3<Real>& vec) const;
    MVector3<Real>& operator+=(MVector3<Real>& vec);
    void operator+=(Real scalar);
    MVector3<Real> operator+(MVector3<Real>& vec);
    void addScaleVector(const MVector3<Real>& vec, Real scalar) const;
    void operator-=(const MVector3<Real>& vec);
    MVector3<Real>& operator-=(const MVector3<Real>& vec) const;
    MVector3<Real> operator-(MVector3<Real> vec) ;
    void operator*=(const Real scalar);
    MVector3<Real> operator*(const Real scalar)const;
    void operator*(const MVector3<Real>& vec);
    MVector3<Real>& operator*(const MVector3<Real>& vec) const;
    MVector3<Real> operator/(const Real scalar) ;
    void operator/=(const Real scalar) ;
    bool operator==(const MVector3<Real>& vec)const ;
    void invert();
    Real magnitude();
    Real squareMagnitude();
    void normalize();
    MVector3<Real>& normalize(MVector3<Real>& vec);
    Real dotProduct(const MVector3<Real>& vec);
    void CrossProduct(MVector3<Real>& vec, MVector3<Real>& store);
    MVector3<Real> CrossProduct(const MVector3<Real>& vec) const ;
    void toOrthoNormalBasis(MVector3<Real>& vec1, MVector3<Real>& vec2, MVector3<Real>& vec3);
    static MVector3<Real> UNIT_X();
    static MVector3<Real> UNIT_Y();
    static MVector3<Real> UNIT_Z();
    //static MVector3<Real> UNIT_Y = MVector3<Real>::UNIT_Y(0.0f,1.0f,0.0f);
    //static MVector3<Real> UNIT_Z = MVector3<Real>::UNIT_Z(0.0f,0.0f,1.0f);
private:

    Real x;
    Real y;
    Real z;

    inline friend std::ostream& operator <<(std::ostream& o, const MVector3<Real>& vec) {
        o << "[X=" << vec.x << ", Y=" << vec.y << ", Z=" << vec.z << "]";
        return o;
    }
};

template <class Real>
MVector3<Real>::MVector3() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

template <class Real>
MVector3<Real>::MVector3(Real x, Real y, Real z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class Real>
MVector3<Real>::MVector3(const MVector3<Real>& vector) {
    this->x = vector.GetX();
    this->y = vector.GetY();
    this->z = vector.GetZ();
}

template <class Real>
MVector3<Real>::~MVector3() {

}

template <class Real>
Real MVector3<Real>::GetX() const {
    return this->x;
}

template <class Real>
void MVector3<Real>::SetX(Real x) {
    this->x = x;
}

template <class Real>
Real MVector3<Real>::GetY() const {
    return this->y;
}

template <class Real>
void MVector3<Real>::SetY(Real y) {
    this->y = y;
}

template <class Real>
Real MVector3<Real>::GetZ() const {
    return this->z;
}

template <class Real>
void MVector3<Real>::SetZ(Real z) {
    this->z = z;
}

template <class Real>
void MVector3<Real>::set(Real x, Real y, Real z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template<class Real> 
void MVector3<Real>::Set(const MVector3<Real>& vector)
{
    this->x = vector.GetX();
    this->y = vector.GetY();
    this->z = vector.GetZ();
}


template <class Real>
Real* MVector3<Real>::getArray() {
    return new Real[3] {x, y, z};
}

template <class Real>
void MVector3<Real>::operator+=(const MVector3<Real>& vec) const {
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
}

template <class Real>
MVector3<Real>& MVector3<Real>::operator+=(MVector3<Real>& vec) {
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
    return *this;
}

template<class Real>
void MVector3<Real>::operator+=(Real scalar)
{
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;
}

template <class Real>
MVector3<Real> MVector3<Real>::operator+(MVector3<Real>& vec) {
    MVector3<Real> nvec(this->x + vec.GetX(), this->y + vec.GetY(), this->z + vec.GetZ());
    return nvec;
}

template <class Real>
void MVector3<Real>::addScaleVector(const MVector3<Real>& vec, Real scalar) const {
    this->x += vec.x * scalar;
    this->y += vec.y * scalar;
    this->z += vec.z * scalar;
}

template <class Real>
void MVector3<Real>::operator-=(const MVector3<Real>& vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
}

template <class Real>
MVector3<Real>& MVector3<Real>::operator-=(const MVector3<Real>& vec) const  {
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    return *this;
}

template <class Real>
MVector3<Real> MVector3<Real>::operator-(MVector3<Real> vec) {
    MVector3<Real> nvec(this->x - vec.GetX(), this->y - vec.GetY(), this->z - vec.GetZ());
    return nvec;
}

template <class Real>
void MVector3<Real>::operator*=(const Real scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}

template <class Real>
MVector3<Real> MVector3<Real>::operator*(const Real scalar) const {
    MVector3<Real> nvec(this->x * scalar, this->y * scalar, this->z *scalar);
    return nvec;
}

template <class Real>
void MVector3<Real>::operator*(const MVector3<Real>& vec) {
    this->x *= vec.x;
    this->y *= vec.y;
    this->z *= vec.z;
}

template <class Real>
MVector3<Real>& MVector3<Real>::operator*(const MVector3<Real>& vec) const {
    return MVector3(x * vec.x, y * vec.y, z * vec.z);
}

template<class Real>
MVector3<Real> MVector3<Real>::operator/(const Real scalar)
{
    return MVector3(x/scalar, y/scalar, z/scalar);
}

template<class Real>
void MVector3<Real>::operator/=(const Real scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
}

template<class Real>
bool MVector3<Real>::operator==(const MVector3<Real>& vec)const
{
    return this->x==vec.x && this->y==vec.y && this->z==vec.z;
}


template <class Real>
void MVector3<Real>::invert() {
    this->x = -x;
    this->y = -y;
    this->z = -z;
}

template <class Real>
Real MVector3<Real>::magnitude() {
    return Math<Real>::Sqrt(Math<Real>::Pow(x, Real(2))
                            + Math<Real>::Pow(y, Real(2))
                            + Math<Real>::Pow(z, Real(2)));
}

template <class Real>
Real MVector3<Real>::squareMagnitude() {
    return Math<Real>::Pow(x, Real(2))
           + Math<Real>::Pow(y, Real(2))
           + Math<Real>::Pow(z, Real(2));
}

template <class Real>
void MVector3<Real>::normalize() {
    Real mag = MVector3<Real>::magnitude();
    if (mag > 0) {
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

template<class Real>
MVector3<Real>& MVector3<Real>::normalize(MVector3<Real>& vec) {
    vec.set(GetX(), GetY(), GetZ());
    vec.normalize();
    return vec;
}

template <class Real>
Real MVector3<Real>::dotProduct(const MVector3<Real>& vec) {
    return x * vec.x + y * vec.y + z * vec.z;
}

template <class Real>
MVector3<Real> MVector3<Real>::CrossProduct(const MVector3<Real>& vec) const {
    MVector3<Real> newVec(
        y * vec.GetZ() - z * vec.GetY(),
        z * vec.GetX() - x * vec.GetZ(),
        x * vec.GetY() - y * vec.GetX());
    return newVec;
}

template<class Real>
void MVector3<T>::CrossProduct(MVector3<Real>& vec, MVector3<Real>& store)
{
    store.SetX(y * vec.GetZ() - vec.GetY() * z);
    store.SetY(z * vec.GetX() - vec.GetZ() * x);
    store.SetZ(x * vec.GetY() - vec.GetX() * y);
}


//template <class Real>
//MVector3<Real>& MVector3<Real>::crossProduct(const MVector3<Real>& vec) {
//    return MVector3(
//            y * vec.getZ() - z * vec.getY(),
//            z * vec.getX() - x * vec.getZ(),
//            x * vec.getY() - y * vec.getX());
//}

template <class Real>
void MVector3<Real>::toOrthoNormalBasis(MVector3<Real>& vec1,
                                        MVector3<Real>& vec2,
                                        MVector3<Real>& vec3) {
    vec1.normalize();
    vec3 = *vec1.crossProduct(vec2);
    if (vec3.squareMagnitude() != 0.0) {
        vec3.normalize();
        vec2 = *vec3.crossProduct(vec1);
    }
}

template<class Real>
MVector3<Real> MVector3<Real>::UNIT_X()
{
    MVector3<Real> unitX(Real(1.0),Real(0.0),Real(0.0));
    return unitX;
}

template<class Real>
MVector3<Real> MVector3<Real>::UNIT_Y()
{
    return MVector3<Real>(Real(0.0),Real(1.0),Real(0.0));
}

template<class Real>
MVector3<Real> MVector3<Real>::UNIT_Z()
{
    return MVector3<Real>(Real(0.0),Real(0.0),Real(1.0));
}

#endif // MVECTOR3_H
