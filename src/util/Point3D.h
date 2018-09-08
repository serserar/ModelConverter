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

#ifndef POINT3D_H
#define POINT3D_H

/**
 * @todo write docs
 */
template <class T>
class Point3D
{
public:
    /**
     * Default constructor
     */
    Point3D();

    /**
    * Default constructor
    */
    Point3D(T x, T y, T z);
    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Point3D(const Point3D& other);
 
    /**
     * Destructor
     */
    ~Point3D() = default;

    static Point3D<T> ZERO;
    
    T GetX();
    void SetX(T x);
    T GetY();
    void SetY(T y);
    T GetZ();
    void SetZ(T z);

private:

    T x;
    T y;
    T z;

};



template<class T>
Point3D<T>::Point3D()
{
    this->x=T {};
    this->y=T {};
    this->z=T {};
}

template<class T> 
Point3D<T>::Point3D(T x, T y, T z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}

template<class T>
Point3D<T>::Point3D(const Point3D<T>& other)
{
    this->x=other.x;
    this->y=other.y;
    this->z=other.z;
}

template <typename T>
Point3D<T> Point3D<T>::ZERO;

template<class T>
T Point3D<T>::GetX()
{
    return this->x;
}

template<class T>
void Point3D<T>::SetX(T x)
{
    this->x = x;
}

template<class T>
T Point3D<T>::GetY()
{
    return this->y;
}

template<class T>
void Point3D<T>::SetY(T y)
{
    this->y=y;
}

template<class T>
T Point3D<T>::GetZ()
{
    return this->z;
}

template<class T>
void Point3D<T>::SetZ(T z)
{
    this->z= z;
}




#endif // POINT3D_H
