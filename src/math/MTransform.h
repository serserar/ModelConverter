/*
 * Copyright 2016 <copyright holder> <email>
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

#ifndef MTRANSFORM_H
#define MTRANSFORM_H
#include "mquaternion.h"
#include "mmatrix4.h"
#include <string>
#include <sstream>

template <class Real>
class MTransform
{
public:
    
    MTransform();
    MTransform(bool inverse);
    MTransform(const MTransform<Real>& other);
    ~MTransform();
    MTransform& operator=(MTransform& other);
    void SetMatrix(MMatrix3<Real>& nmatrix);
    void SetTranslation(MVector3<Real>& nstrans);
    void SetScale(MVector3<Real>& nscale);
    void SetScale(float nscale);
    void SetRotation(MVector3<Real>& rotation);
    void SetIdentity();
    MTransform<Real>* invert(MTransform<Real>& store);
    MTransform<Real> multiply(MTransform<Real>& transformby, MTransform<Real>& store);
    MVector3<Real> ApplyForward(MVector3<Real>& point);
    MMatrix4<Real>* ToMatrix4x4(MMatrix4<Real>& store);
    static MTransform<Real>* GetInstance(MVector3<Real>& translation, MVector3<Real>& rotation);
    static MTransform<Real> GetInstance(MVector3<Real>& rotation);
    std::string toString();
    MMatrix3<Real> matrix;
    MVector3<Real> translation;
    MVector3<Real> scale;
    bool identity;
    bool rotationMatrix;
    bool uniformScale;
    
private:

    inline friend std::ostream& operator <<(std::ostream& o, const MTransform<Real>& transform) {
        o << "[" << std::endl;
        o << "M:" << *transform.matrix << std::endl;
        o << "S:" << *transform.scale << std::endl;
        o << "T:" << *transform.translation << std::endl;
        o << "]" << std::endl;
        return o;
    }

};

template<class Real>
MTransform<Real>::MTransform(bool inverse)
{
    scale.set(1.0,1.0,1.0);
    SetIdentity();
    identity = inverse;
    rotationMatrix = true;
    uniformScale = true;
}

template<class Real>
MTransform<Real>::MTransform()
{
    scale.set(1.0,1.0,1.0);
    SetIdentity();
    rotationMatrix = true;
    uniformScale = true;
}

template<class Real>
MTransform<Real>::MTransform(const MTransform<Real>& other)
{
    matrix.Set(other.matrix);
    translation.Set(other.translation);
    scale.Set(other.scale);
    identity = other.identity;
    rotationMatrix = other.rotationMatrix;
    uniformScale = other.uniformScale;
}

template<class Real>
MTransform<Real>::~MTransform()
{
}

template<class Real> 
MTransform<Real> & MTransform<Real>::operator=(MTransform<Real>& other)
{
    matrix.Set(other.matrix);
    translation.Set(other.translation);
    scale.Set(other.scale);
    identity = other.identity;
    rotationMatrix = other.rotationMatrix;
    uniformScale = other.uniformScale;
    return *this;
}


template<class Real>
void MTransform<Real>::SetIdentity()
{
    matrix.setIdentity();
    translation.set(Real(0), Real(0), Real(0));
    scale.set(Real(1), Real(1), Real(1));
    identity = true;
}


template<class Real>
MTransform<Real>* MTransform<Real>::invert(MTransform<Real>& store)
{
    if (identity) {
        store.SetIdentity();
    } else {
        if (rotationMatrix) {
            store.matrix.Set(matrix);
            if (uniformScale) {
                store.matrix.transpose();
                float invScale = 1.0f/scale.GetX();
                store.matrix.set(
                    store.matrix.get(0,0)*invScale, store.matrix.get(0,1)*invScale, store.matrix.get(0,2)*invScale,
                    store.matrix.get(1,0)*invScale, store.matrix.get(1,1)*invScale, store.matrix.get(1,2)*invScale,
                    store.matrix.get(2,0)*invScale, store.matrix.get(2,1)*invScale, store.matrix.get(2,2)*invScale);
            } else {
                //Multiplies this matrix by the diagonal matrix formed by the given vector (M * v^D)
                store.matrix.set(0, 0, scale.GetX() * store.matrix.get(0,0));
                store.matrix.set(0, 1, scale.GetY() * store.matrix.get(0,1));
                store.matrix.set(0, 2, scale.GetZ() * store.matrix.get(0,2));
                store.matrix.set(1, 0, scale.GetX() * store.matrix.get(1,0));
                store.matrix.set(1, 1, scale.GetY() * store.matrix.get(1,1));
                store.matrix.set(1, 2, scale.GetZ() * store.matrix.get(1,2));
                store.matrix.set(2, 0, scale.GetX() * store.matrix.get(2,0));
                store.matrix.set(2, 1, scale.GetY() * store.matrix.get(2,1));
                store.matrix.set(2, 2, scale.GetZ() * store.matrix.get(2,2));
                store.matrix.invert();
            }
        } else {
            store.matrix.invert();
        }
        //M*Vtrans
        MVector3<float>* translationResult = store.matrix * translation;
        *translationResult * -1;//negate
        store.translation.Set(*translationResult);
        //store.updateFlags(_rotationMatrix);
        delete translationResult;
    }
    return &store;
}

template<class Real>
MTransform<Real> MTransform<Real>::multiply(MTransform<Real>& transformby, MTransform<Real>& store)
{
    //MTransform<Real> result = store;
    if(!identity) {
        if(rotationMatrix && transformby.rotationMatrix && uniformScale) {
            //R*S*X+T
            store.rotationMatrix=true;
            store.matrix.set(matrix.get(0,0), matrix.get(0,1), matrix.get(0,2),
                              matrix.get(1,0), matrix.get(1,1), matrix.get(1,2),
                              matrix.get(2,0), matrix.get(2,1), matrix.get(2,2));
            MMatrix3<Real>* tmpMat = store.matrix * transformby.matrix;
            store.matrix.set(tmpMat->get(0,0), tmpMat->get(0,1), tmpMat->get(0,2),
                              tmpMat->get(1,0), tmpMat->get(1,1), tmpMat->get(1,2),
                              tmpMat->get(2,0), tmpMat->get(2,1), tmpMat->get(2,2));
            delete tmpMat;
            store.translation.set(transformby.translation.GetX(),
                                   transformby.translation.GetY(),
                                   transformby.translation.GetZ());
            MVector3<float>* ntranslation = matrix * store.translation;
            *ntranslation *scale;
            *ntranslation += translation;
            store.translation.Set(*ntranslation);
            if (transformby.uniformScale) {
                Real nscale = scale.GetX() * transformby.scale.GetX();
                store.scale.set(nscale, nscale, nscale);
            } else {
                store.scale.Set(transformby.scale);
                store.scale *scale;
            }
            delete ntranslation;
        } else {
            //TODO
        }
    } else {
        store.SetMatrix(transformby.matrix);
        store.SetTranslation(transformby.translation);
        store.SetScale(transformby.scale);
    }
    return store;
}

template<class Real>
MVector3<Real> MTransform<Real>::ApplyForward(MVector3<Real>& point)
{
    if(!identity) {
        if (rotationMatrix) {
            // Scale is separate from matrix
            // Y = R*S*X + T
            point.set(point.GetX() * scale.GetX(), point.GetY() * scale.GetY(), point.GetZ() * scale.GetZ());
            point = matrix.ApplyPost(point);
            point+=translation;
        } else {
            // scale is part of matrix.
            // Y = M*X + T
            point = matrix.ApplyPost(point);
            point+=translation;
        }
    }
    MVector3<Real> tpoint = point;
    return tpoint;
}


template<class Real>
void MTransform<Real>::SetMatrix(MMatrix3<Real>& nmatrix)
{
    this->matrix.Set(nmatrix);
    //identity = false;
}

template<class Real>
void MTransform<Real>::SetTranslation(MVector3<Real>& ntrans)
{
    this->translation.Set(ntrans);
    identity = false;
}

template<class Real>
void MTransform<Real>::SetScale(MVector3<Real>& nscale)
{
    this->scale.SetX(nscale.GetX());
    this->scale.SetY(nscale.GetY());
    this->scale.SetZ(nscale.GetZ());
    identity = false;
}

template<class Real>
void MTransform<Real>::SetScale(float nscale)
{
    this->scale.SetX(scale.GetX() * nscale);
    this->scale.SetY(scale.GetY() * nscale);
    this->scale.SetZ(scale.GetZ() * nscale);
    identity = false;
}


template<class Real>
MMatrix4<Real>* MTransform<Real>::ToMatrix4x4(MMatrix4<Real>& store)
{
    if (rotationMatrix) {
        store.setM00(scale.GetX() * matrix.getM00());
        store.setM01(scale.GetX() * matrix.getM01());
        store.setM02(scale.GetX() * matrix.getM02());
        store.setM10(scale.GetY() * matrix.getM10());
        store.setM11(scale.GetY() * matrix.getM11());
        store.setM12(scale.GetY() * matrix.getM12());
        store.setM20(scale.GetZ() * matrix.getM20());
        store.setM21(scale.GetZ() * matrix.getM21());
        store.setM22(scale.GetZ() * matrix.getM22());
    } else {
        store.setM00(matrix.getM00());
        store.setM01(matrix.getM01());
        store.setM02(matrix.getM02());
        store.setM10(matrix.getM10());
        store.setM11(matrix.getM11());
        store.setM12(matrix.getM12());
        store.setM20(matrix.getM20());
        store.setM21(matrix.getM21());
        store.setM22(matrix.getM22());
    }

    store.setM30(0.0);
    store.setM31(0.0);
    store.setM32(0.0);

    store.setM03(translation.GetX());
    store.setM13(translation.GetY());
    store.setM23(translation.GetZ());
    store.setM33(1.0);
    return &store;
}


template<class Real>
MTransform<Real> * MTransform<Real>::GetInstance(MVector3<Real>& translation, MVector3<Real>& rotation)
{
    MTransform<Real>* ntrans = new MTransform<Real>();
    ntrans->SetMatrix(MMatrix3<Real>::GetInstance(rotation));
    ntrans->SetTranslation(translation);
    return ntrans;
}

template<class Real>
MTransform<Real> MTransform<Real>::GetInstance(MVector3<Real>& rotation)
{
    MTransform<Real> ntrans;
    MMatrix3<Real> rmatrix;
    rmatrix = MMatrix3<Real>::GetInstance(rotation);
    ntrans.SetMatrix(rmatrix);
    return ntrans;
}

template<class Real> 
void MTransform<Real>::SetRotation(MVector3<Real>& rotation)
{
    MMatrix3<Real> rmatrix;
    rmatrix = MMatrix3<Real>::GetInstance(rotation);
    SetMatrix(rmatrix);
}

template<class Real>
std::string MTransform<Real>::toString()
{
    std::string transformstr = "";
    std::stringstream ss;
    ss << *matrix;
    std::string matrixstr = ss.str();
    ss.clear();
    ss << *scale;
    std::string scalestr = ss.str();
    ss.clear();
    ss << *translation;
    std::string translationstr = ss.str();
    transformstr = "Transform [\n M: " + matrixstr + "\n S: " + scalestr + "\n T: " + translationstr + "\n]";
    return transformstr;
}

#endif // MTRANSFORM_H
