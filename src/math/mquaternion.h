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

#ifndef MQUATERNION_H
#define MQUATERNION_H

#include "mmatrix3.h"

template <class Real>
class MQuaternion {
public:

    MQuaternion();
    MQuaternion(const Real w, const Real i, const Real j, const Real k);
    MQuaternion(const MQuaternion<Real>& qt);
    MQuaternion(MVector3<Real>& vector);
    ~MQuaternion();
    Real getW() const;
    Real getI() const;
    Real getJ() const;
    Real getK() const;
    void SetI(Real i);
    void SetJ(Real j);
    void SetK(Real k);
    void SetW(Real w);
    void operator +=(const MQuaternion<Real>& qt);
    void operator -=(const MQuaternion<Real>& qt);
    void operator *=(Real scalar);
    void operator *=(const MQuaternion<Real>& qt);
    MQuaternion<Real>* operator *(const MQuaternion<Real>& qt);
    void operator *(const MVector3<Real>& vec);
    void operator /=(Real scalar);
    // conversion between quaternions, matrices, and axis-angle
    MQuaternion& FromRotationMatrix (const MMatrix3<Real>& rkRot);
    void ToRotationMatrix (MMatrix3<Real>& rkRot) const;
    MQuaternion& FromRotationMatrix (const MVector3<Real> akRotColumn[3]);
    void ToRotationMatrix (MVector3<Real> akRotColumn[3]) const;
    MQuaternion& FromAxisAngle (const MVector3<Real>& rkAxis, Real fAngle);
    void ToAxisAngle (MVector3<Real>& rkAxis, Real& rfAngle) const;
    
    Real length();
    Real squaredLength();
    void normalize();
    MQuaternion<Real> normalize() const;
    void conjugate();
    void negate();
    void inverse();
    void rotatev(MVector3<Real>& rvector);
    MVector3<Real>* rotate(MVector3<Real>& rvector);
    
    static constexpr MQuaternion<Real> IDENTITY = MQuaternion<Real>::IDENTITY(1.0f,0.0f,0.0f,0.0f);
    static constexpr MQuaternion<Real> ZERO = MQuaternion<Real>::ZERO(0.0f,0.0f,0.0f,0.0f);
    
private:

    Real w; //real component of the quaternion
    Real i; //first complex component of the quaternion
    Real j; //second complex component of the quaternion
    Real k; //third complex component of the quaternion
    // support for FromRotationMatrix
    static constexpr int ms_iNext[3] = { 1, 2, 0 };
    inline friend std::ostream& operator <<(std::ostream& out, MQuaternion<Real>& qt) {
        out << "[ X=" << qt.getI() << ", Y=" << qt.getJ() << ", Z=" << qt.getK() << ", W=" << qt.getW() << " ]";
        return out;
    }
};
#include "mquaternion.cpp"
#endif // MQUATERNION_H
