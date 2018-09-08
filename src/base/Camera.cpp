/*
 * Copyright 2018 <copyright holder> <email>
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
 */

#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera ( int width, int height, MVector3<float> eye, MVector3<float> up, MVector3<float> center,  float near, float far, float fovx, float fovy )
{
    this->width = width;
    this->height = height;
    this->eye = eye;
    this->up = up;
    this->center = center;
    this->near = near;
    this->far = far;
    this->fovx = fovx;
    this->fovy = fovy;
    init();
}


Camera::Camera ( const Camera& other )
{
    this->width = other.width;
    this->height = other.height;
    this->eye = other.eye;
    this->up = other.up;
    this->center = other.center;
    this->near = other.near;
    this->far = other.far;
    this->fovx = other.fovx;
    this->fovy = other.fovy;
}

void Camera::init()
{
    float ratio = fovx/fovy;
    hnear = 2 * tanf ( fovx*Math<float>::PI/180/2. ) *near;
    wnear = hnear *ratio;
    hfar = 2 * tanf ( fovy*Math<float>::PI/180/2. ) * far;
    wfar = hfar * ratio;
}

int Camera::GetWidth()
{
    return this->width;
}

void Camera::SetWidth ( int width )
{
    this->width = width;
}

int Camera::GetHeight()
{
    return this->height;
}

void Camera::SetHeight ( int height )
{
    this->height = height;
}

float Camera::GetFovX()
{
    return this->fovx;
}

void Camera::SetFovX ( float focusx )
{
    this->fovx = focusx;
}

float Camera::GetFovY()
{
    return fovy;
}

void Camera::SetFovY ( float focusy )
{
    this->fovy = focusy;
}

MVector3<float> Camera::GetEye()
{
    return this->eye;
}
void Camera::SetEye ( MVector3<float> eye )
{
    this->eye = eye;
}

MVector3<float> Camera::GetUp()
{
    return this->up;
}

void Camera::SetUp ( MVector3<float> up )
{
    this->up=up;
}

MVector3<float> Camera::GetCenter()
{
    return this->center;
}

void Camera::SetCenter ( MVector3<float> center )
{
    this->center=center;
}

float Camera::GetFar()
{
    return this->far;
}

void Camera::SetFar ( float far )
{
    this->far = far;
}

float Camera::GetNear()
{
    return this->near;
}

void Camera::SetNear ( float near )
{
    this->near = near;
}


Ray Camera::ProjectPixelTo3dRay ( MVector2<float>& pixel )
{
    Ray ray;
    ray.SetOrigin ( this->eye ); //set camera eye as the origin of the ray
    MVector3<float> u, v, w;
    w =  center - eye;
    w.normalize();
    up.CrossProduct ( w,u );
    w.CrossProduct ( u,v );
    float alpha, beta;
    alpha = tanf ( fovx*Math<float>::PI/180/2. ) * ( pixel.GetX() - width/2. ) / ( width/2. );
    beta  = tanf ( fovy*Math<float>::PI/180/2. ) * ( pixel.GetY() - height/2. ) / ( height/2. );
    u=u*alpha;
    v=v*beta;
    MVector3<float> direction;
    direction = u+v-w;//positive direction
    direction.normalize();
    direction *=-1.0f;
    ray.SetDirection ( direction );
    return ray;
}

float Camera::GetZFromPoint ( MVector3<float>& point )
{
    //tener en cuenta la profundidad desde la camara distance = center - eye y no tomar dfar.GetZ() - point.GetZ() see Test SkeletonSnapshot2
    float zpoint= 0;
    //isvisble
    MVector3<float> distance =  center - eye;
    distance.normalize();
    MVector3<float> dnear =  distance * near;
    MVector3<float> dfar =  distance * far;
    dnear+=eye;
    dfar+=eye;
    float ztotal = Math<float>::Abs ( near -far );
    zpoint = point.GetZ();
    if ( distance.GetZ() > 0 ) {
        if ( point.GetZ() >= dnear.GetZ() && point.GetZ() <= dfar.GetZ() ) {
            zpoint = ( 1.0f - ( ( dfar.GetZ() - point.GetZ() ) / ztotal ) ) * 255;
        }
    } else {
        if ( point.GetZ() <= dnear.GetZ() && point.GetZ() >= dfar.GetZ() ) {
            zpoint = ( 1.0f - ( ( dnear.GetZ() -point.GetZ() ) / ztotal ) ) * 255;
        }
    }
    //zpoint = point.GetZ() >254?255:point.GetZ();
    return zpoint;
}

float Camera::GetWidthNear()
{
    return wnear;
}

float Camera::GetHeightNear()
{
    return hnear;
}

float Camera::GetWidthFar()
{
    return wfar;
}

float Camera::GetHeightFar()
{
    return hfar;
}

float Camera::GetWidthZ ( float z )
{
    float ratio = fovx/fovy;
    float hz = 2 * tanf ( fovx*Math<float>::PI/180/2. ) *z;
    float wz = hz *ratio;
    return wz;
}

float Camera::GetHeightZ ( float z )
{
    float hz = 2 * tanf ( fovx*Math<float>::PI/180/2. ) *z;
    return hz;
}


float Camera::GetNormalizedZ(float z)
{
    float normalizedZ = 0;
    float nearz = eye.GetZ() - near;
    float farz = eye.GetZ() - near - far;
    if(z < nearz &&  z > farz){
        normalizedZ = nearz - z;
    }
    return normalizedZ;
}

