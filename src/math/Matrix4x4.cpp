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



/////////////////////////////////////////////////////////////////////////////
//
// class Matrix4x4<Real> implementation.
//
// --------------------------------------------------------------------------
//
// MATRIX ORGANIZATION
//
// The purpose of this class is so that a user might perform transformations
// without fiddling with plus or minus signs or transposing the matrix
// until the output "looks right".  But of course, the specifics of the
// internal representation is important.  Not only for the implementation
// in this file to be correct, but occasionally direct access to the
// matrix variables is necessary, or beneficial for optimization.  Thus,
// we document our matrix conventions here.
//
// Strict adherance to linear algebra rules dictates that the
// multiplication of a 4x4 matrix by a 3D vector is actually undefined.
// To circumvent this, we can consider the input and output vectors as
// having an assumed fourth coordinate of 1.  Also, since the rightmost
// column is [ 0 0 0 1 ], we can simplificate calculations ignoring
// this last column. This is shown below:
//
//         | m11 m12 m13 0 | | x |   | x'|
//         | m21 m22 m23 0 | | y | = | y'|
//         | m31 m32 m33 0 | | z |   | z'|
//         | tx  ty  tz  1 | | 1 |   | 1 |
//
// We use row vectors to represent the right, up and forward vectors
// in the 4x4 matrix.  OpenGL uses column vectors, but the elements of
// an OpenGL matrix are ordered in columns so that m[i][j] is in row j
// and column i.  This is the reverse of the standard C convention in
// which m[i][j] is in row i and column j.  The matrix should be
// transposed before being sent to OpenGL.
//
//   | m11 m21 m31 tx |    |  m0  m4  m8 m12 |    |  m0  m1  m2  m3 |
//   | m12 m22 m32 ty |    |  m1  m5  m9 m13 |    |  m4  m5  m6  m7 |
//   | m13 m23 m33 tz |    |  m2  m6 m10 m14 |    |  m8  m9 m10 m11 |
//   |  0   0   0  tw |    |  m3  m7 m11 m15 |    | m12 m13 m14 m15 |
//
//      OpenGL style          OpenGL matrix            standard C
//                             arrangement             convention
//
// Fortunately, accessing to the raw matrix data via the _m[] array gives
// us the transpose matrix; i.e. in OpenGL form, so that we can directly use
// it with glLoadMatrix{fd}() or glMultMatrix{fd}().
//
// Also, since the rightmost column (in standard C form) should always
// be [ 0 0 0 1 ], and sice these values (_h14, _h24, _h34 and _tw) are
// initialized in constructors, we don't need to modify them in our
// matrix operations, so we don't perform useless calculations...
//
// The right-hand rule is used to define "positive" rotation.
//
//               +y                          +x'
//                |                           |
//                |                           |
//                |______ +x        +y' ______|
//               /                            /
//              /                            /
//             +z                          +z'
//
//          initial position      Positive rotation of
//                                 pi/2 around z-axis
//
/////////////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------------
// Matrix4x4::identity
//
// Set matrix to identity.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::identity ()
{
  _m11 = 1.0; _m21 = 0.0; _m31 = 0.0; _tx = 0.0;
  _m12 = 0.0; _m22 = 1.0; _m32 = 0.0; _ty = 0.0;
  _m13 = 0.0; _m23 = 0.0; _m33 = 1.0; _tz = 0.0;
  _h14 = 0.0; _h24 = 0.0; _h34 = 0.0; _tw = 1.0;
}


// --------------------------------------------------------------------------
// Matrix4x4::transpose
//
// Transpose the current matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::transpose ()
{
  *this = Transpose (*this);
}


// --------------------------------------------------------------------------
// Matrix4x4::invert
//
// Invert the current matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::invert ()
{
  *this = Invert (*this);
}


// --------------------------------------------------------------------------
// Matrix4x4::setTranslation
//
// Set the translation portion of the matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::setTranslation (const MVector3<Real> &v)
{
  _tx = v._x; _ty = v._y; _tz = v._z;
}


// --------------------------------------------------------------------------
// Matrix4x4::transform
//
// Transform a point by the matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::transform (MVector3<Real> &v) const
{
  // Grind through the linear algebra.
  v = MVector3<Real> (
	(v._x * _m11) + (v._y * _m21) + (v._z * _m31) + _tx,
	(v._x * _m12) + (v._y * _m22) + (v._z * _m32) + _ty,
	(v._x * _m13) + (v._y * _m23) + (v._z * _m33) + _tz
   );
}


// --------------------------------------------------------------------------
// Matrix4x4::rotate
//
// Rotate a point by the 3x3 upper left portion of the matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::rotate (MVector3<Real> &v) const
{
  v = MVector3<Real> (
	(v._x * _m11) + (v._y * _m21) + (v._z * _m31),
	(v._x * _m12) + (v._y * _m22) + (v._z * _m32),
	(v._x * _m13) + (v._y * _m23) + (v._z * _m33)
   );
}


// --------------------------------------------------------------------------
// Matrix4x4::inverseRotate
//
// Rotate a point by the inverse 3x3 upper left portion of the matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::inverseRotate (MVector3<Real> &v) const
{
  v = MVector3<Real> (
	(v._x * _m11) + (v._y * _m12) + (v._z * _m13),
	(v._x * _m21) + (v._y * _m22) + (v._z * _m23),
	(v._x * _m31) + (v._y * _m32) + (v._z * _m33)
   );
}


// --------------------------------------------------------------------------
// Matrix4x4::inverseRotate
//
// Translate a point by the inverse matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::inverseTranslate (MVector3<Real> &v) const
{
  v._x -= _tx;
  v._y -= _ty;
  v._z -= _tz;
}


// --------------------------------------------------------------------------
// Matrix4x4::fromQuaternion
//
// Convert a quaternion to a matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::fromQuaternion (const MQuaternion<Real> &q)
{
  // Compute a few values to optimize common subexpressions
  Real ww = 2.0 * q._w;
  Real xx = 2.0 * q._x;
  Real yy = 2.0 * q._y;
  Real zz = 2.0 * q._z;

  // Set the matrix elements.  There is still a little more
  // opportunity for optimization due to the many common
  // subexpressions.  We'll let the compiler handle that...
  _m11 = 1.0 - (yy * q._y) - (zz * q._z);
  _m12 = (xx * q._y) + (ww * q._z);
  _m13 = (xx * q._z) - (ww * q._y);

  _m21 = (xx * q._y) - (ww * q._z);
  _m22 = 1.0 - (xx * q._x) - (zz * q._z);
  _m23 = (yy * q._z) + (ww * q._x);

  _m31 = (xx * q._z) + (ww * q._y);
  _m32 = (yy * q._z) - (ww * q._x);
  _m33 = 1.0 - (xx * q._x) - (yy * q._y);

  // Reset the translation portion
  _tx = _ty = _tz = 0.0;
}


// --------------------------------------------------------------------------
// Matrix4x4::fromEulerAngles
//
// Setup a rotation matrix, given three X-Y-Z rotation angles. The
// rotations are performed first on x-axis, then y-axis and finaly z-axis.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::fromEulerAngles (Real x, Real y, Real z)
{
  // Fetch sine and cosine of angles
  Real cx = std::cos (x);
  Real sx = std::sin (x);
  Real cy = std::cos (y);
  Real sy = std::sin (y);
  Real cz = std::cos (z);
  Real sz = std::sin (z);

  Real sxsy = sx * sy;
  Real cxsy = cx * sy;

  // Fill in the matrix elements
  _m11 =  (cy * cz);
  _m12 =  (sxsy * cz) + (cx * sz);
  _m13 = -(cxsy * cz) + (sx * sz);

  _m21 = -(cy * sz);
  _m22 = -(sxsy * sz) + (cx * cz);
  _m23 =  (cxsy * sz) + (sx * cz);

  _m31 =  (sy);
  _m32 = -(sx * cy);
  _m33 =  (cx * cy);

  // Reset the translation portion
  _tx = _ty = _tz = 0.0;
}


// --------------------------------------------------------------------------
// Matrix4x4::toEulerAngles
//
// Setup the euler angles in radians, given a rotation matrix. The rotation
// matrix could have been obtained from euler angles given the expression:
//   M = X.Y.Z
// where X, Y and Z are rotation matrices about X, Y and Z axes.
// This is the "opposite" of the fromEulerAngles function.
// --------------------------------------------------------------------------

template <typename Real>
inline void
Matrix4x4<Real>::toEulerAngles (Real &x, Real &y, Real &z) const
{
  // Compute Y-axis angle
  y = std::asin (_m31);

  // Compute cos and one over cos for optimization
  Real cy = std::cos (y);
  Real oneOverCosY = 1.0 / cy;

  if (std::fabs (cy) > 0.001)
    {
      // No gimball lock
      x = std::atan2 (-_m32 * oneOverCosY, _m33 * oneOverCosY);
      z = std::atan2 (-_m21 * oneOverCosY, _m11 * oneOverCosY);
    }
  else
    {
      // Gimbal lock case
      x = 0.0;
      z = std::atan2 (_m12, _m22);
    }
}


// --------------------------------------------------------------------------
// Matrix4x4::rightVector
// Matrix4x4::upVector
// Matrix4x4::forwardVector
// Matrix4x4::translationVector
//
// Return a base vector from the matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline MVector3<Real>
Matrix4x4<Real>::rightVector () const
{
  return MVector3<Real> (_m11, _m12, _m13);
}

template <typename Real>
inline MVector3<Real>
Matrix4x4<Real>::upVector () const
{
  return MVector3<Real> (_m21, _m22, _m23);
}

template <typename Real>
inline MVector3<Real>
Matrix4x4<Real>::forwardVector () const
{
  return MVector3<Real> (_m31, _m32, _m33);
}

template <typename Real>
inline MVector3<Real>
Matrix4x4<Real>::translationVector () const
{
  return MVector3<Real> (_tx, _ty, _tz);
}


// --------------------------------------------------------------------------
//
// Nonmember Matrix4x4<Real> functions
//
// --------------------------------------------------------------------------


// --------------------------------------------------------------------------
// Matrix4x4 * Matrix4x4
//
// Matrix concatenation.
//
// We also provide a *= operator, as per C convention.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
operator* (const Matrix4x4<Real> &a, const Matrix4x4<Real> &b)
{
  Matrix4x4<Real> res;

  // Compute the left 4x3 (linear transformation) portion
  res._m11 = (a._m11 * b._m11) + (a._m21 * b._m12) + (a._m31 * b._m13);
  res._m12 = (a._m12 * b._m11) + (a._m22 * b._m12) + (a._m32 * b._m13);
  res._m13 = (a._m13 * b._m11) + (a._m23 * b._m12) + (a._m33 * b._m13);

  res._m21 = (a._m11 * b._m21) + (a._m21 * b._m22) + (a._m31 * b._m23);
  res._m22 = (a._m12 * b._m21) + (a._m22 * b._m22) + (a._m32 * b._m23);
  res._m23 = (a._m13 * b._m21) + (a._m23 * b._m22) + (a._m33 * b._m23);

  res._m31 = (a._m11 * b._m31) + (a._m21 * b._m32) + (a._m31 * b._m33);
  res._m32 = (a._m12 * b._m31) + (a._m22 * b._m32) + (a._m32 * b._m33);
  res._m33 = (a._m13 * b._m31) + (a._m23 * b._m32) + (a._m33 * b._m33);

  // Compute the translation portion
  res._tx = (a._m11 * b._tx) + (a._m21 * b._ty) + (a._m31 * b._tz) + a._tx;
  res._ty = (a._m12 * b._tx) + (a._m22 * b._ty) + (a._m32 * b._tz) + a._ty;
  res._tz = (a._m13 * b._tx) + (a._m23 * b._ty) + (a._m33 * b._tz) + a._tz;

  return res;
}

template <typename Real>
inline Matrix4x4<Real> &
operator*= (Matrix4x4<Real> &a, const Matrix4x4<Real> &b)
{
  a = a * b;
  return a;
}


// --------------------------------------------------------------------------
// Matrix4x4 * MVector3
//
// Transform a point by a matrix.  This makes using the vector class look
// like it does with linear algebra notation on paper.
// --------------------------------------------------------------------------

template <typename Real>
inline MVector3<Real>
operator* (const Matrix4x4<Real> &m, const MVector3<Real> &p)
{
  MVector3<Real> res (p);
  m.transform (res);
  return res;
}


// --------------------------------------------------------------------------
// Transpose
//
// Return the transpose matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
Transpose (const Matrix4x4<Real> &m)
{
  Matrix4x4<Real> res;

  res._m11 = m._m11; res._m21 = m._m12; res._m31 = m._m13; res._tx = m._h14;
  res._m12 = m._m21; res._m22 = m._m22; res._m32 = m._m23; res._ty = m._h24;
  res._m13 = m._m31; res._m23 = m._m32; res._m33 = m._m33; res._tz = m._h34;
  res._h14 = m._tx;  res._h24 = m._ty;  res._h34 = m._tz;  res._tw = m._tw;

  return res;
}


// --------------------------------------------------------------------------
// Determinant
//
// Compute the determinant of the 3x3 portion of the matrix.
// --------------------------------------------------------------------------

template <typename Real>
inline static Real
Determinant3x3 (const Matrix4x4<Real> &m)
{
  return m._m11 * ((m._m22 * m._m33) - (m._m23 * m._m32))
    + m._m12 * ((m._m23 * m._m31) - (m._m21 * m._m33))
    + m._m13 * ((m._m21 * m._m32) - (m._m22 * m._m31));
}


// --------------------------------------------------------------------------
// Invert
//
// Compute the inverse of a matrix.  We use the classical adjoint divided
// by the determinant method.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
Invert (const Matrix4x4<Real> &m)
{
  // Compute the determinant of the 3x3 portion
  Real det = Determinant3x3 (m);

  // If we're singular, then the determinant is zero and there's
  // no inverse
  assert (std::fabs (det) > 0.000001);

  // Compute one over the determinant, so we divide once and
  // can *multiply* per element
  Real oneOverDet = 1.0 / det;

  // Compute the 3x3 portion of the inverse, by
  // dividing the adjoint by the determinant
  Matrix4x4<Real> res;

  res._m11 = ((m._m22 * m._m33) - (m._m23 * m._m32)) * oneOverDet;
  res._m12 = ((m._m13 * m._m32) - (m._m12 * m._m33)) * oneOverDet;
  res._m13 = ((m._m12 * m._m23) - (m._m13 * m._m22)) * oneOverDet;

  res._m21 = ((m._m23 * m._m31) - (m._m21 * m._m33)) * oneOverDet;
  res._m22 = ((m._m11 * m._m33) - (m._m13 * m._m31)) * oneOverDet;
  res._m23 = ((m._m13 * m._m21) - (m._m11 * m._m23)) * oneOverDet;

  res._m31 = ((m._m21 * m._m32) - (m._m22 * m._m31)) * oneOverDet;
  res._m32 = ((m._m12 * m._m31) - (m._m11 * m._m32)) * oneOverDet;
  res._m33 = ((m._m11 * m._m22) - (m._m12 * m._m21)) * oneOverDet;

  // Compute the translation portion of the inverse
  res._tx = -((m._tx * res._m11) + (m._ty * res._m21) + (m._tz * res._m31));
  res._ty = -((m._tx * res._m12) + (m._ty * res._m22) + (m._tz * res._m32));
  res._tz = -((m._tx * res._m13) + (m._ty * res._m23) + (m._tz * res._m33));

  // Return it.
  return res;
}


// --------------------------------------------------------------------------
// RotationMatrix
//
// Setup the matrix to perform a rotation about one of the three cardinal
// X-Y-Z axes.
//
// The axis of rotation is specified by the 1-based "axis" index.
//
// theta is the amount of rotation, in radians.  The right-hand rule is
// used to define "positive" rotation.
//
// The translation portion is reset.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
RotationMatrix (Axis axis, Real theta)
{
  Matrix4x4<Real> res;

  // Get sin and cosine of rotation angle
  Real s = std::sin (theta);
  Real c = std::cos (theta);

  // Check which axis they are rotating about
  switch (axis)
    {
    case kXaxis: // Rotate about the x-axis
      res._m11 = 1.0; res._m21 = 0.0; res._m31 = 0.0;
      res._m12 = 0.0; res._m22 = c;   res._m32 = -s;
      res._m13 = 0.0; res._m23 = s;   res._m33 =  c;
      break;

    case kYaxis: // Rotate about the y-axis
      res._m11 = c;   res._m21 = 0.0; res._m31 = s;
      res._m12 = 0.0; res._m22 = 1.0; res._m32 = 0.0;
      res._m13 = -s;  res._m23 = 0.0; res._m33 = c;
      break;

    case kZaxis: // Rotate about the z-axis
      res._m11 = c;   res._m21 = -s;  res._m31 = 0.0;
      res._m12 = s;   res._m22 =  c;  res._m32 = 0.0;
      res._m13 = 0.0; res._m23 = 0.0; res._m33 = 1.0;
      break;

    default:
      // bogus axis index
      assert (false);
    }

  // Reset the translation portion
  res._tx = res._ty = res._tz = 0.0;

  return res;
}


//---------------------------------------------------------------------------
// AxisRotationMatrix
//
// Setup the matrix to perform a rotation about an arbitrary axis.
// The axis of rotation must pass through the origin.
//
// axis defines the axis of rotation, and must be a unit vector.
//
// theta is the amount of rotation, in radians.  The right-hand rule is
// used to define "positive" rotation.
//
// The translation portion is reset.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
RotationMatrix (const MVector3<Real> &axis, Real theta)
{
  Matrix4x4<Real> res;

  // Quick sanity check to make sure they passed in a unit vector
  // to specify the axis
  assert (std::fabs (DotProduct (axis, axis) - 1.0) < 0.001);

  // Get sin and cosine of rotation angle
  Real s = std::sin (theta);
  Real c = std::cos (theta);

  // Compute 1 - cos(theta) and some common subexpressions
  Real a = 1.0 - c;
  Real ax = a * axis._x;
  Real ay = a * axis._y;
  Real az = a * axis._z;

  // Set the matrix elements.  There is still a little more
  // opportunity for optimization due to the many common
  // subexpressions.  We'll let the compiler handle that...
  res._m11 = (ax * axis._x) + c;
  res._m12 = (ax * axis._y) + (axis._z * s);
  res._m13 = (ax * axis._z) - (axis._y * s);

  res._m21 = (ay * axis._x) - (axis._z * s);
  res._m22 = (ay * axis._y) + c;
  res._m23 = (ay * axis._z) + (axis._x * s);

  res._m31 = (az * axis._x) + (axis._y * s);
  res._m32 = (az * axis._y) - (axis._x * s);
  res._m33 = (az * axis._z) + c;

  // Reset the translation portion
  res._tx = res._ty = res._tz = 0.0;

  return res;
}


// --------------------------------------------------------------------------
// TranslationMatrix
//
// Build a translation matrix given a translation vector.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
TranslationMatrix (Real x, Real y, Real z)
{
  return TranslationMatrix (MVector3<Real> (x, y, z));
}

template <typename Real>
inline Matrix4x4<Real>
TranslationMatrix (const MVector3<Real> &v)
{
  Matrix4x4<Real> res;

  res._m11 = 1.0; res._m21 = 0.0; res._m31 = 0.0; res._tx = v._x;
  res._m12 = 0.0; res._m22 = 1.0; res._m32 = 0.0; res._ty = v._y;
  res._m13 = 0.0; res._m23 = 0.0; res._m33 = 1.0; res._tz = v._z;

  return res;
}


// --------------------------------------------------------------------------
// ScaleMatrix
//
// Setup the matrix to perform scale on each axis.  For uniform scale by k,
// use a vector of the form MVector3( k, k, k ).
//
// The translation portion is reset.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
ScaleMatrix (const MVector3<Real> &s)
{
  Matrix4x4<Real> res;

  // Set the matrix elements.  Pretty straightforward
  res._m11 = s._x; res._m21 = 0.0;  res._m31 = 0.0;
  res._m12 = 0.0;  res._m22 = s._y; res._m32 = 0.0;
  res._m13 = 0.0;  res._m23 = 0.0;  res._m33 = s._z;

  // Reset the translation portion
  res._tx = res._ty = res._tz = 0.0;

  return res;
}


// --------------------------------------------------------------------------
// ScaleAlongAxisMatrix
//
// Setup the matrix to perform scale along an arbitrary axis.
//
// The axis is specified using a unit vector.
//
// The translation portion is reset.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
ScaleAlongAxisMatrix (const MVector3<Real> &axis, Real k)
{
  Matrix4x4<Real> res;

  // Quick sanity check to make sure they passed in a unit vector
  // to specify the axis
  assert (std::fabs (DotProduct (axis, axis) - 1.0) < 0.001);

  // Compute k-1 and some common subexpressions
  Real a = k - 1.0;
  Real ax = a * axis._x;
  Real ay = a * axis._y;
  Real az = a * axis._z;

  // Fill in the matrix elements.  We'll do the common
  // subexpression optimization ourselves here, since diagonally
  // opposite matrix elements are equal
  res._m11 = (ax * axis._x) + 1.0;
  res._m22 = (ay * axis._y) + 1.0;
  res._m32 = (az * axis._z) + 1.0;

  res._m12 = res._m21 = (ax * axis._y);
  res._m13 = res._m31 = (ax * axis._z);
  res._m23 = res._m32 = (ay * axis._z);

  // Reset the translation portion
  res._tx = res._ty = res._tz = 0.0;

  return res;
}


// --------------------------------------------------------------------------
// ShearMatrix
//
// Setup the matrix to perform a shear
//
// The type of shear is specified by the 1-based "axis" index.  The effect
// of transforming a point by the matrix is described by the pseudocode
// below:
//
//	xAxis  =>  y += s * x, z += t * x
//	yAxis  =>  x += s * y, z += t * y
//	zAxis  =>  x += s * z, y += t * z
//
// The translation portion is reset.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
ShearMatrix (Axis axis, Real s, Real t)
{
  Matrix4x4<Real> res;

  // Check which type of shear they want
  switch (axis)
    {
    case kXaxis: // Shear y and z using x
      res._m11 = 1.0; res._m21 = 0.0; res._m31 = 0.0;
      res._m12 = s;   res._m22 = 1.0; res._m32 = 0.0;
      res._m13 = t;   res._m23 = 0.0; res._m33 = 1.0;
      break;

    case kYaxis: // Shear x and z using y
      res._m11 = 1.0; res._m21 = s;   res._m31 = 0.0;
      res._m12 = 0.0; res._m22 = 1.0; res._m32 = 0.0;
      res._m13 = 0.0; res._m23 = t;   res._m33 = 1.0;
      break;

    case kZaxis: // Shear x and y using z
      res._m11 = 1.0; res._m21 = 0.0; res._m31 = s;
      res._m12 = 0.0; res._m22 = 1.0; res._m32 = t;
      res._m13 = 0.0; res._m23 = 0.0; res._m33 = 1.0;
      break;

    default:
      // bogus axis index
      assert (false);
    }

  // Reset the translation portion
  res._tx = res._ty = res._tz = 0.0;

  return res;
}


// --------------------------------------------------------------------------
// ProjectionMatrix
//
// Setup the matrix to perform a projection onto a plane passing
// through the origin.  The plane is perpendicular to the
// unit vector n.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
ProjectionMatrix (const MVector3<Real> &n)
{
  Matrix4x4<Real> res;

  // Quick sanity check to make sure they passed in a unit vector
  // to specify the axis
  assert (std::fabs (DotProduct (n, n) - 1.0) < 0.001);

  // Fill in the matrix elements.  We'll do the common
  // subexpression optimization ourselves here, since diagonally
  // opposite matrix elements are equal
  res._m11 = 1.0 - (n._x * n._x);
  res._m22 = 1.0 - (n._y * n._y);
  res._m33 = 1.0 - (n._z * n._z);

  res._m12 = res._m21 = -(n._x * n._y);
  res._m13 = res._m31 = -(n._x * n._z);
  res._m23 = res._m32 = -(n._y * n._z);

  // Reset the translation portion
  res._tx = res._ty = res._tz = 0.0;

  return res;
}


// --------------------------------------------------------------------------
// ReflectionMatrix
//
// Setup the matrix to perform a reflection about a plane parallel
// to a cardinal plane.
//
// axis is a 1-based index which specifies the plane to project about:
//
//	xAxis => reflect about the plane x=k
//	yAxis => reflect about the plane y=k
//	zAxis => reflect about the plane z=k
//
// The translation is set appropriately, since translation must occur if
// k != 0
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
ReflectionMatrix (Axis axis, Real k)
{
  Matrix4x4<Real> res;

  // Check which plane they want to reflect about
  switch (axis)
    {
    case kXaxis: // Reflect about the plane x=k
      res._m11 = -1.0; res._m21 =  0.0; res._m31 =  0.0; res._tx = 2.0 * k;
      res._m12 =  0.0; res._m22 =  1.0; res._m32 =  0.0; res._ty = 0.0;
      res._m13 =  0.0; res._m23 =  0.0; res._m33 =  1.0; res._tz = 0.0;
      break;

    case kYaxis: // Reflect about the plane y=k
      res._m11 =  1.0; res._m21 =  0.0; res._m31 =  0.0; res._tx = 0.0;
      res._m12 =  0.0; res._m22 = -1.0; res._m32 =  0.0; res._ty = 2.0 * k;
      res._m13 =  0.0; res._m23 =  0.0; res._m33 =  1.0; res._tz = 0.0;
      break;

    case kZaxis: // Reflect about the plane z=k
      res._m11 =  1.0; res._m21 =  0.0; res._m31 =  0.0; res._tx = 0.0;
      res._m12 =  0.0; res._m22 =  1.0; res._m32 =  0.0; res._ty = 0.0;
      res._m13 =  0.0; res._m23 =  0.0; res._m33 = -1.0; res._tz = 2.0 * k;
      break;

    default:
      // bogus axis index
      assert (false);
    }

  return res;
}


// --------------------------------------------------------------------------
// AxisReflectionMatrix
//
// Setup the matrix to perform a reflection about an arbitrary plane
// through the origin.  The unit vector n is perpendicular to the plane.
//
// The translation portion is reset.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
AxisReflectionMatrix (const MVector3<Real> &n)
{
  Matrix4x4<Real> res;

  // Quick sanity check to make sure they passed in a unit vector
  // to specify the axis
  assert (std::fabs (DotProduct (n, n) - 1.0) < 0.001);

  // Compute common subexpressions
  Real ax = -2.0 * n._x;
  Real ay = -2.0 * n._y;
  Real az = -2.0 * n._z;

  // Fill in the matrix elements.  We'll do the common
  // subexpression optimization ourselves here, since diagonally
  // opposite matrix elements are equal
  res._m11 = 1.0 + (ax * n._x);
  res._m22 = 1.0 + (ay * n._y);
  res._m32 = 1.0 + (az * n._z);

  res._m12 = res._m21 = (ax * n._y);
  res._m13 = res._m31 = (ax * n._z);
  res._m23 = res._m32 = (ay * n._z);

  // Reset the translation portion
  res._tx = res._ty = res._tz = 0.00;

  return res;
}


// --------------------------------------------------------------------------
// LookAtMatrix
//
// Setup the matrix to perform a "Look At" transformation like a first
// person camera.
// --------------------------------------------------------------------------
template <typename Real>
inline Matrix4x4<Real>
LookAtMatrix (const MVector3<Real> &camPos, const MVector3<Real> &target,
	      const MVector3<Real> &camUp)
{
  Matrix4x4<Real> rot, trans;

  MVector3<Real> forward (camPos - target);
  forward.normalize ();

  MVector3<Real> right (CrossProduct (camUp, forward));
  MVector3<Real> up (CrossProduct (forward, right));

  right.normalize ();
  up.normalize ();

  rot._m11 = right._x;
  rot._m21 = right._y;
  rot._m31 = right._z;

  rot._m12 = up._x;
  rot._m22 = up._y;
  rot._m32 = up._z;

  rot._m13 = forward._x;
  rot._m23 = forward._y;
  rot._m33 = forward._z;

  rot._tx  = 0.0;
  rot._ty  = 0.0;
  rot._tz  = 0.0;

  trans = TranslationMatrix (-camPos);

  return (rot * trans);
}


// --------------------------------------------------------------------------
// FrustumMatrix
//
// Setup a frustum matrix given the left, right, bottom, top, near, and far
// values for the frustum boundaries.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
FrustumMatrix (Real l, Real r, Real b, Real t, Real n, Real f)
{
  assert (n >= 0.0);
  assert (f >= 0.0);

  Matrix4x4<Real> res;

  Real width  = r - l;
  Real height = t - b;
  Real depth  = f - n;

  res._m[0] = (2 * n) / width;
  res._m[1] = 0.0;
  res._m[2] = 0.0;
  res._m[3] = 0.0;

  res._m[4] = 0.0;
  res._m[5] = (2 * n) / height;
  res._m[6] = 0.0;
  res._m[7] = 0.0;

  res._m[8] = (r + l) / width;
  res._m[9] = (t + b) / height;
  res._m[10]= -(f + n) / depth;
  res._m[11]= -1.0;

  res._m[12]= 0.0;
  res._m[13]= 0.0;
  res._m[14]= -(2 * f * n) / depth;
  res._m[15]= 0.0;

  return res;
}


// --------------------------------------------------------------------------
// PerspectiveMatrix
//
// Setup a perspective matrix given the field-of-view in the Y direction
// in degrees, the aspect ratio of Y/X, and near and far plane distances.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
PerspectiveMatrix (Real fovY, Real aspect, Real n, Real f)
{
  Matrix4x4<Real> res;

  Real angle;
  Real cot;

  angle = fovY / 2.0;
  angle = degToRad (angle);

  cot = std::cos (angle) / std::sin (angle);

  res._m[0] = cot / aspect;
  res._m[1] = 0.0;
  res._m[2] = 0.0;
  res._m[3] = 0.0;

  res._m[4] = 0.0;
  res._m[5] = cot;
  res._m[6] = 0.0;
  res._m[7] = 0.0;

  res._m[8] = 0.0;
  res._m[9] = 0.0;
  res._m[10]= -(f + n) / (f - n);
  res._m[11]= -1.0;

  res._m[12]= 0.0;
  res._m[13]= 0.0;
  res._m[14]= -(2 * f * n) / (f - n);
  res._m[15]= 0.0;

  return res;
}


// --------------------------------------------------------------------------
// OrthoMatrix
//
// Setup an orthographic Matrix4x4 given the left, right, bottom, top, near,
// and far values for the frustum boundaries.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
OrthoMatrix (Real l, Real r, Real b, Real t, Real n, Real f)
{
  Matrix4x4<Real> res;

  Real width  = r - l;
  Real height = t - b;
  Real depth  = f - n;

  res._m[0] =  2.0 / width;
  res._m[1] =  0.0;
  res._m[2] =  0.0;
  res._m[3] =  0.0;

  res._m[4] =  0.0;
  res._m[5] =  2.0 / height;
  res._m[6] =  0.0;
  res._m[7] =  0.0;

  res._m[8] =  0.0;
  res._m[9] =  0.0;
  res._m[10]= -2.0 / depth;
  res._m[11]=  0.0;

  res._m[12]= -(r + l) / width;
  res._m[13]= -(t + b) / height;
  res._m[14]= -(f + n) / depth;
  res._m[15]=  1.0;

  return res;
}


// --------------------------------------------------------------------------
// OrthoNormalMatrix
//
// Setup an orientation matrix using 3 basis normalized vectors.
// --------------------------------------------------------------------------

template <typename Real>
inline Matrix4x4<Real>
OrthoNormalMatrix (const MVector3<Real> &xdir, const MVector3<Real> &ydir,
		   const MVector3<Real> &zdir)
{
  Matrix4x4<Real> res;

  res._m[0] = xdir._x; res._m[4] = ydir._x; res._m[8] = zdir._x; res._m[12] = 0.0;
  res._m[1] = xdir._y; res._m[5] = ydir._y; res._m[9] = zdir._y; res._m[13] = 0.0;
  res._m[2] = xdir._z; res._m[6] = ydir._z; res._m[10]= zdir._z; res._m[14] = 0.0;
  res._m[3] = 0.0;     res._m[7] = 0.0;     res._m[11]= 0.0;     res._m[15] = 1.0;

  return res;
}
