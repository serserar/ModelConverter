/*
 * File:   MPlane.h
 * Author: serserar
 *
 * Created on July 23, 2014, 5:54 PM
 */

#ifndef MPLANE_H
#define	MPLANE_H
#include "MVector3.h"

template <class Real>
class MPlane {
public:
    MPlane();
    MPlane(const MPlane& orig);
    MPlane(MVector3<Real>& normal, MVector3<Real> origin);
    MPlane(Real x, Real y, Real z, MVector3<Real> origin);
    virtual ~MPlane()=default;
    MVector3<Real> GetNormal();
    MVector3<Real> GetDistance();
    bool IntersectsRay(MVector3<Real>& rayOrigin, MVector3<Real>& rayDest, MVector3<Real>& intersectionPoint);
private:
    MVector3<Real> normal;
    MVector3<Real> origin;
};

template<class Real>
MPlane<Real>::MPlane() {
}

template<class Real>
MPlane<Real>::MPlane(const MPlane<Real>& orig) {
    this->normal = orig.normal;
    this->origin = orig.origin;
}

template<class Real>
MPlane<Real>::MPlane(MVector3<Real>& normal, MVector3<Real> origin) {
    this->normal = normal;
    this->origin = origin;
}


template<class Real>
MPlane<Real>::MPlane(Real x, Real y, Real z, MVector3<Real> origin) {
    this->normal.setX(x);
    this->normal.setY(y);
    this->normal.setZ(z);
    this->origin = origin;
}

template<class Real>
MVector3<Real> MPlane<Real>::GetNormal() {
    return normal;
}

template<class Real>
MVector3<Real> MPlane<Real>::GetDistance() {
    return this->origin;
}
template<class Real>
bool MPlane<Real>::IntersectsRay(MVector3<Real>& rayOrigin, MVector3<Real>& rayDest, MVector3<Real>& intersectionPoint)
{
    //t=(p0−l0).n/l⋅n
    Real t = (origin-rayOrigin).dotProduct(normal)/normal.dotProduct(rayDest);
    intersectionPoint.SetX(rayOrigin.GetX() + rayDest.GetX() * t);
    intersectionPoint.SetY(rayOrigin.GetY() + rayDest.GetY() * t);
    intersectionPoint.SetZ(rayOrigin.GetZ() + rayDest.GetZ() * t);
    return t > 0;//if exist constant t
}



#endif	/* MPLANE_H */

