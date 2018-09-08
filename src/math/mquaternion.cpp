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

#include "mquaternion.h"

template <class Real>
MQuaternion<Real>::MQuaternion() {

}

template <class Real>
MQuaternion<Real>::MQuaternion(const Real w, const Real i, const Real j, const Real k) {
    this->w = w;
    this->i = i;
    this->j = j;
    this->k = k;
}

template <class Real>
MQuaternion<Real>::MQuaternion(const MQuaternion& qt) {
    this->w = qt.w;
    this->i = qt.i;
    this->j = qt.j;
    this->k = qt.k;
}

template <class Real>
MQuaternion<Real>::MQuaternion(MVector3<Real>& vector) {
    this->w = Real(0.0);
    this->i = vector.getX();
    this->j = vector.getY();
    this->k = vector.getZ();
}

template <class Real>
MQuaternion<Real>::~MQuaternion() {

}

template <class Real>
Real MQuaternion<Real>::getI() const{
    return i;
}

template <class Real>
Real MQuaternion<Real>::getJ() const{
    return j;
}

template <class Real>
Real MQuaternion<Real>::getK() const{
    return k;
}

template <class Real>
Real MQuaternion<Real>::getW() const{
    return w;
}

template <class Real>
void MQuaternion<Real>::SetI(Real i) {
    this->i = i;
}

template <class Real>
void MQuaternion<Real>::SetJ(Real j) {
    this->j = j;
}

template <class Real>
void MQuaternion<Real>::SetK(Real k) {
    this->k = k;
}

template <class Real>
void MQuaternion<Real>::SetW(Real w) {
    this->w = w;
}


template <class Real>
void MQuaternion<Real>::operator+=(const MQuaternion<Real>& qt) {
    w += qt.getW();
    i += qt.getI();
    j += qt.getJ();
    k += qt.getK();
}

template <class Real>
void MQuaternion<Real>::operator-=(const MQuaternion<Real>& qt) {
    w -= qt.getW();
    i -= qt.getI();
    j -= qt.getJ();
    k -= qt.getK();
}

template <class Real>
void MQuaternion<Real>::operator*=(Real scalar) {
    w *= scalar;
    i *= scalar;
    j *= scalar;
    k *= scalar;
}

template <class Real>
void MQuaternion<Real>::operator*=(const MQuaternion<Real>& qt) {
    w = w * qt;
}

template<class Real> 
MQuaternion<Real> * MQuaternion<Real>::operator*(const MQuaternion<Real>& qt)
{
    MQuaternion<Real>* nquaternion = new MQuaternion<Real>(
        w * qt.getW() - i * qt.getI() - j * qt.getJ() - k * qt.getK(),
        w * qt.getI() + i * qt.getW() + j * qt.getK() - k * qt.getJ(),
        w * qt.getJ() + j * qt.getW() + k * qt.getI() - i * qt.getK(),
        w * qt.getK() + k * qt.getW() + i * qt.getJ() - j * qt.getI()
    );
    return nquaternion;
}


template <class Real>
void MQuaternion<Real>::operator/=(Real scalar) {
    if (scalar > 0) {
        Real invScalar = ((Real) 1.0) / scalar;
        w *= invScalar;
        i *= invScalar;
        j *= invScalar;
        k *= invScalar;
    }
}

template <class Real>
MQuaternion<Real>& MQuaternion<Real>::FromRotationMatrix (
    const MMatrix3<Real>& rkRot)
{
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "MQuaternion Calculus and Fast Animation".

    Real fTrace = rkRot(0,0) + rkRot(1,1) + rkRot(2,2);
    Real fRoot;

    if ( fTrace > (Real)0.0 )
    {
        // |w| > 1/2, may as well choose w > 1/2
        fRoot = Math<Real>::Sqrt(fTrace + (Real)1.0);  // 2w
        w = ((Real)0.5)*fRoot;
        fRoot = ((Real)0.5)/fRoot;  // 1/(4w)
        i = (rkRot(2,1)-rkRot(1,2))*fRoot;
        j = (rkRot(0,2)-rkRot(2,0))*fRoot;
        k = (rkRot(1,0)-rkRot(0,1))*fRoot;
    }
//    else
//    {
//         // |w| <= 1/2
//         Real i = 0;
//         if ( rkRot(1,1) > rkRot(0,0) )
//             i = 1;
//         if ( rkRot(2,2) > rkRot(i,i) )
//             i = 2;
//         Real j = (Real)ms_iNext[(int)i];
//         Real k = (Real)ms_iNext[(int)j];
// 
//         fRoot = Math<Real>::Sqrt(rkRot(i,i)-rkRot(j,j)-rkRot(k,k)+(Real)1.0);
//         Real* apfQuat[3] = { &i, &j, &k };
//         *apfQuat[(int)i] = ((Real)0.5)*fRoot;
//         fRoot = ((Real)0.5)/fRoot;
//         w = (rkRot(k,j)-rkRot(j,k))*fRoot;
//         *apfQuat[(int)j] = (rkRot(j,i)+rkRot(i,j))*fRoot;
//         *apfQuat[(int)k] = (rkRot(k,i)+rkRot(i,k))*fRoot;
        else if (rkRot(0,0) > rkRot(1,1) && rkRot(0,0) > rkRot(2,2)) {
            Real s =  Math<Real>::Sqrt(1.0 + rkRot(0,0) - rkRot(1,1) - rkRot(2,2)); // |s|>=1
            i = s * 0.5; // |x| >= .5
            s = 0.5 / s;
            j = (rkRot(1,0) + rkRot(0,1)) * s;
            k = (rkRot(0,2) + rkRot(2,0)) * s;
            w = (rkRot(2,1) - rkRot(1,2)) * s;
        } else if (rkRot(1,1) > rkRot(2,2)) {
            Real s =  Math<Real>::Sqrt(1.0 + rkRot(1,1) - rkRot(0,0) - rkRot(2,2)); // |s|>=1
            j = s * 0.5; // |y| >= .5
            s = 0.5 / s;
            i = (rkRot(1,0) + rkRot(0,1)) * s;
            k = (rkRot(2,1) + rkRot(1,2)) * s;
            w = (rkRot(0,2) - rkRot(2,0)) * s;
        } else {
            Real s =  Math<Real>::Sqrt(1.0 + rkRot(2,2) - rkRot(0,0) - rkRot(1,1)); // |s|>=1
            k = s * 0.5; // |z| >= .5
            s = 0.5 / s;
            i = (rkRot(0,2) + rkRot(2,0)) * s;
            j = (rkRot(2,1) + rkRot(1,2)) * s;
            w = (rkRot(1,0) - rkRot(0,1)) * s;
        }
    //}

    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
void MQuaternion<Real>::ToRotationMatrix (MMatrix3<Real>& rkRot) const
{
    Real fTx  = ((Real)2.0)*i;
    Real fTy  = ((Real)2.0)*j;
    Real fTz  = ((Real)2.0)*k;
    Real fTwx = fTx*w;
    Real fTwy = fTy*w;
    Real fTwz = fTz*w;
    Real fTxx = fTx*i;
    Real fTxy = fTy*i;
    Real fTxz = fTz*i;
    Real fTyy = fTy*j;
    Real fTyz = fTz*j;
    Real fTzz = fTz*k;

    rkRot(0,0) = (Real)1.0-(fTyy+fTzz);
    rkRot(0,1) = fTxy-fTwz;
    rkRot(0,2) = fTxz+fTwy;
    rkRot(1,0) = fTxy+fTwz;
    rkRot(1,1) = (Real)1.0-(fTxx+fTzz);
    rkRot(1,2) = fTyz-fTwx;
    rkRot(2,0) = fTxz-fTwy;
    rkRot(2,1) = fTyz+fTwx;
    rkRot(2,2) = (Real)1.0-(fTxx+fTyy);
}
//----------------------------------------------------------------------------
template <class Real>
MQuaternion<Real>& MQuaternion<Real>::FromRotationMatrix (
    const MVector3<Real> akRotColumn[3])
{
    MMatrix3<Real> kRot;
    for (int iCol = 0; iCol < 3; iCol++)
    {
        kRot(0,iCol) = akRotColumn[iCol][0];
        kRot(1,iCol) = akRotColumn[iCol][1];
        kRot(2,iCol) = akRotColumn[iCol][2];
    }
    return FromRotationMatrix(kRot);
}
//----------------------------------------------------------------------------
template <class Real>
void MQuaternion<Real>::ToRotationMatrix (MVector3<Real> akRotColumn[3]) const
{
    MMatrix3<Real> kRot;
    ToRotationMatrix(kRot);
    for (int iCol = 0; iCol < 3; iCol++)
    {
        akRotColumn[iCol][0] = kRot(0,iCol);
        akRotColumn[iCol][1] = kRot(1,iCol);
        akRotColumn[iCol][2] = kRot(2,iCol);
    }
}
//----------------------------------------------------------------------------
template <class Real>
MQuaternion<Real>& MQuaternion<Real>::FromAxisAngle (
    const MVector3<Real>& rkAxis, Real fAngle)
{
    // assert:  axis[] is unit length
    //
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    Real fHalfAngle = ((Real)0.5)*fAngle;
    Real fSin = Math<Real>::Sin(fHalfAngle);
    w = Math<Real>::Cos(fHalfAngle);
    i = fSin*rkAxis.getX();
    j = fSin*rkAxis.getY();
    k = fSin*rkAxis.getX();

    return *this;
}
//----------------------------------------------------------------------------
template <class Real>
void MQuaternion<Real>::ToAxisAngle (MVector3<Real>& rkAxis, Real& rfAngle)
    const
{
    // The quaternion representing the rotation is
    //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    Real fSqrLength = i*i + j*j
        + k*k;
    if ( fSqrLength > Math<Real>::ZERO_TOLERANCE )
    {
        rfAngle = ((Real)2.0)*Math<Real>::ACos(w);
        Real fInvLength = Math<Real>::InvSqrt(fSqrLength);
        rkAxis[0] = i*fInvLength;
        rkAxis[1] = j*fInvLength;
        rkAxis[2] = k*fInvLength;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        rfAngle = (Real)0.0;
        rkAxis[0] = (Real)1.0;
        rkAxis[1] = (Real)0.0;
        rkAxis[2] = (Real)0.0;
    }
}

template <class Real>
Real MQuaternion<Real>::length() {
    Real d = Math<Real>::Pow2(w) + Math<Real>::Pow2(i) + Math<Real>::Pow2(j) + Math<Real>::Pow2(k);
    if (d > 0) {
        d = Math<Real>::Sqrt(d);
    }
    return d;
}

template <class Real>
Real MQuaternion<Real>::squaredLength() {
    Real d = Math<Real>::Pow2(w) + Math<Real>::Pow2(i) + Math<Real>::Pow2(j) + Math<Real>::Pow2(k);
    return d;
}

template <class Real>
void MQuaternion<Real>::normalize() {
    Real d = MQuaternion<Real>::length();
    if (d > 0) {
        d = Real(1) / d;
        w *= d;
        i *= d;
        j *= d;
        k *= d;
    }
}

template <class Real>
MQuaternion<Real> MQuaternion<Real>::normalize() const {
    MQuaternion<Real> q(*this);
    q.normalize();
    return q;
}

template <class Real>
void MQuaternion<Real>::conjugate() {
    i = -i;
    j = -j;
    k = -k;
}

template<class Real> 
void MQuaternion<Real>::negate()
{
    i = -i;
    j = -j;
    k = -k;
    w = -w;
}


template <class Real>
void MQuaternion<Real>::inverse() {
    Real mag = MQuaternion<Real>::length();
    this->conjugate();
    *this /= mag;
}

template <class Real>
void MQuaternion<Real>::rotatev(MVector3<Real>& rvector) {
    // Given a vector u = (x0,y0,z0) and a unit length quaternion
    // q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
    // rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
    // multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
    // Note that q^{-1} = <w,-x,-y,-z>, so no real work is required to
    // invert q.  Now
    //
    //   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
    //     = q*(x0*i+y0*j+z0*k)*q^{-1}
    //     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
    //
    // As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
    // of the rotation matrix computed in MQuaternion<Real>::ToRotationMatrix.
    // The vector v is obtained as the product of that rotation matrix with
    // vector u.  As such, the quaternion representation of a rotation
    // matrix requires less space than the matrix and more time to compute
    // the rotated vector.  Typical space-time tradeoff...

    MMatrix3<Real> kRot;
    ToRotationMatrix(kRot);
    return kRot*rvector;
}

template <class Real>
MVector3<Real>* MQuaternion<Real>::rotate(MVector3<Real>& rvector)
{
    // Given a vector u = (x0,y0,z0) and a unit length quaternion
    // q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
    // rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
    // multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
    // Note that q^{-1} = <w,-x,-y,-z>, so no real work is required to
    // invert q.  Now
    //
    //   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
    //     = q*(x0*i+y0*j+z0*k)*q^{-1}
    //     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
    //
    // As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
    // of the rotation matrix computed in MQuaternion<Real>::ToRotationMatrix.
    // The vector v is obtained as the product of that rotation matrix with
    // vector u.  As such, the quaternion representation of a rotation
    // matrix requires less space than the matrix and more time to compute
    // the rotated vector.  Typical space-time tradeoff...
    MVector3<Real>*res;
    MMatrix3<Real> kRot;
    ToRotationMatrix(kRot);
    res = (kRot*rvector);
    return res;
}
