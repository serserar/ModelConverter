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

#ifndef POINT2D_H
#define POINT2D_H

/**
 * @todo write docs
 */
template <class T>
class Point2D
{
public:
    /**
     * Default constructor
     */
    Point2D();

    
    /**
     * Default constructor
     */
    Point2D(T x, T y);
    
    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Point2D(const Point2D& other);

    /**
     * Destructor
     */
    ~Point2D() = default;
    
    T GetX();
    void SetX(T x);
    
    T GetY();
    void SetY(T y);
    
private:
    
T x;
T y;

};

template<class T> 
Point2D<T>::Point2D()
{
    this->x=T{};
    this->y=T{};
}

template<class T> 
Point2D<T>::Point2D(T x, T y)
{
    this->x=x;
    this->y=y;
}

template<class T> 
Point2D<T>::Point2D(const Point2D<T>& other)
{
    this->x=other.x;
    this->y=other.y;
}

template<class T> 
T Point2D<T>::GetX()
{
    return this->x;
}

template<class T> 
void Point2D<T>::SetX(T x)
{
    this->x = x;
}

template<class T> 
T Point2D<T>::GetY()
{
    return this->y;
}

template<class T> 
void Point2D<T>::SetY(T y)
{
    this->y=y;
}



#endif // POINT2D_H
