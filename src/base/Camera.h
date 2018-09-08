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

#ifndef CAMERA_H
#define CAMERA_H
#include "../math/MVector3.h"
#include "../math/MVector2.h"
#include "Ray.h"
/**
 * @todo write docs
 */
class Camera
{
public:
    /**
     * Default constructor
     */
    Camera();

    Camera(int width, int height, MVector3<float> eye, MVector3<float> up, MVector3<float> center, float near, float far, float fovx, float fovy);

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Camera(const Camera& other);

    /**
     * Destructor
     */
    ~Camera()=default;

    int GetWidth();
    void SetWidth(int width);
    int GetHeight();
    void SetHeight(int height);
    float GetNear();
    void SetNear(float znear);
    float GetFar();
    void SetFar(float zfar);
    float GetFovX();
    void SetFovX(float focusx);
    float GetFovY();
    void SetFovY(float focusy);
    MVector3<float> GetEye();
    void SetEye(MVector3<float> eye);
    MVector3<float> GetUp();
    void SetUp(MVector3<float> up);
    MVector3<float> GetCenter();
    void SetCenter(MVector3<float> center);
    Ray ProjectPixelTo3dRay(MVector2<float>& pixel);
    float GetZFromPoint(MVector3<float>& point);
    float GetWidthNear();
    float GetHeightNear();
    float GetWidthFar();
    float GetHeightFar();
    float GetWidthZ(float z);
    float GetHeightZ(float z);
    float GetNormalizedZ(float z);
    void init();
private:
    int width, height;
    float near, far;
    float fovx, fovy;
    float hnear, wnear,hfar,wfar;
    MVector3<float> eye;
    MVector3<float> up;
    MVector3<float> center;
};

#endif // CAMERA_H
