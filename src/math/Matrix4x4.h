/*
 * Copyright 2017 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "mquaternion.h"

    // Type definitions
enum Axis {
  kXaxis, kYaxis, kZaxis
};
/////////////////////////////////////////////////////////////////////////////
//
// class Matrix4x4<Real> - Implement a 4x4 Matrix class that can represent
// any 3D affine transformation.
//
/////////////////////////////////////////////////////////////////////////////

template <typename Real>
class Matrix4x4
{
public:

  // Constructor - Initialize the last (never used) row of the matrix
  // so that we can do any operation on matrices on the 3x4 portion
  // and forget that line which will (and should) never change.
  Matrix4x4 ()
    : _h14 (0.0f), _h24 (0.0f), _h34 (0.0f), _tw (1.0f) { }

  // Note that we don't define the copy constructor and let the compiler
  // doing it itself because such initialization is not necessary
  // since the source matrix has its last row already initialized...

public:
  // Public interface
  void identity ();
  void transpose ();
  void invert ();
  void setTranslation (const MVector3<Real> &v);

  void transform (MVector3<Real> &v) const;
  void rotate (MVector3<Real> &v) const;
  void inverseRotate (MVector3<Real> &v) const;
  void inverseTranslate (MVector3<Real> &v) const;

  void fromQuaternion (const MQuaternion<Real> &q);

  // Matrix <-> Euler conversions; XYZ rotation order; angles in radians
  void fromEulerAngles (Real x, Real y, Real z);
  void toEulerAngles (Real &x, Real &y, Real &z) const;

  // Return a base vector from the matrix
  MVector3<Real> rightVector () const;
  MVector3<Real> upVector () const;
  MVector3<Real> forwardVector () const;
  MVector3<Real> translationVector () const;

  // Accessor.  This allows to use the matrix object
  // like an array of Real. For example:
  // Matrix4x4<float> mat;
  // float f = mat[4]; // access to _m21
  operator const Real *() { return _m; }

public:
  // Member variables

  // The values of the matrix.  Basically the upper 3x3 portion
  // contains a linear transformation, and the last column is the
  // translation portion. Here data is transposed, see the Mathlib.inl
  // for more details.
  union
  {
    struct
    {
      Real _m11, _m12, _m13, _h14;
      Real _m21, _m22, _m23, _h24;
      Real _m31, _m32, _m33, _h34;
      Real _tx,  _ty,  _tz,  _tw;
    };

    // Access to raw packed matrix data (usefull for
    // glLoadMatrixf () and glMultMatrixf ())
    Real _m[16];
  };
};


// Predefined Matrix4x4 types
typedef Matrix4x4<float> Matrix4x4f;
typedef Matrix4x4<double> Matrix4x4d;


//
// Nonmember Matrix4x4 functions
//

// Matrix concatenation
template <typename Real>
Matrix4x4<Real> operator* (const Matrix4x4<Real> &a, const Matrix4x4<Real> &b);

template <typename Real>
Matrix4x4<Real> &operator*= (Matrix4x4<Real> &a, const Matrix4x4<Real> &b);

// Vector transformation
template <typename Real>
MVector3<Real> operator* (const Matrix4x4<Real> &m, const MVector3<Real> &p);

// Transpose matrix
template <typename Real>
Matrix4x4<Real> Transpose (const Matrix4x4<Real> &m);

// Invert matrix
template <typename Real>
Matrix4x4<Real> Invert (const Matrix4x4<Real> &m);

//
// Matrix-builder functions
//

template <typename Real> Matrix4x4<Real> RotationMatrix (Axis axis, Real theta);
template <typename Real> Matrix4x4<Real> RotationMatrix (const MVector3<Real> &axis, Real theta);
template <typename Real> Matrix4x4<Real> TranslationMatrix (Real x, Real y, Real z);
template <typename Real> Matrix4x4<Real> TranslationMatrix (const MVector3<Real> &v);
template <typename Real> Matrix4x4<Real> ScaleMatrix (const MVector3<Real> &s);
template <typename Real> Matrix4x4<Real> ScaleAlongAxisMatrix (const MVector3<Real> &axis, Real k);
template <typename Real> Matrix4x4<Real> ShearMatrix (Axis axis, Real s, Real t);
template <typename Real> Matrix4x4<Real> ProjectionMatrix (const MVector3<Real> &n);
template <typename Real> Matrix4x4<Real> ReflectionMatrix (Axis axis, Real k);
template <typename Real> Matrix4x4<Real> AxisReflectionMatrix (const MVector3<Real> &n);

template <typename Real>
Matrix4x4<Real> LookAtMatrix (const MVector3<Real> &camPos,
	const MVector3<Real> &target, const MVector3<Real> &camUp);
template <typename Real>
Matrix4x4<Real> FrustumMatrix (Real l, Real r, Real b, Real t, Real n, Real f);
template <typename Real>
Matrix4x4<Real> PerspectiveMatrix (Real fovY, Real aspect, Real n, Real f);
template <typename Real>
Matrix4x4<Real> OrthoMatrix (Real l, Real r, Real b, Real t, Real n, Real f);
template <typename Real>
Matrix4x4<Real> OrthoNormalMatrix (const MVector3<Real> &xdir,
	const MVector3<Real> &ydir, const MVector3<Real> &zdir);

#include "Matrix4x4.cpp"
#endif // MATRIX4X4_H
