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

#ifndef GRID3D_H
#define GRID3D_H
#include <cmath>
#include "Point3D.h"
/**
 * @todo write docs
 */
template <class T>
class Grid3D
{
public:
    /**
     * Default constructor
     */
    Grid3D(float width, float height, float depth, float cellSize);

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Grid3D(const Grid3D& other);

    /**
     * Destructor
     */
    ~Grid3D();

    void SetElement(Point3D<T> element);
    bool IsFarEnough(Point3D<T> point, float minDist);
    
private:
    Point3D<T>*** cube;
    int gwidth;
    int gheight;
    int gdepth;
    float cellSize;
    float Distance(Point3D<T>& point, Point3D<T>& otherPoint);
};

template<class T>
Grid3D<T>::Grid3D(float width, float height, float depth, float cellSize)
{
    this->cellSize = cellSize;
    this->gwidth = ceil(width/cellSize);
    this->gheight = ceil(height/cellSize);
    this->gdepth = ceil(depth/cellSize);
    cube = new Point3D<T>**[gwidth];
    for(int i = 0 ; i < gwidth; i++) {
        cube[i] = new Point3D<T>*[gheight];
        for(int j= 0; j < gheight; j++) {
            cube[i][j]=new Point3D<T>[gdepth];
        }
    }
}

template<class T>
Grid3D<T>::~Grid3D()
{
    for(int i = 0 ; i < gwidth; i++) {
        for(int j= 0; j < gheight; j++) {
            delete[] cube[i][j];
        }
        delete[] cube[i];
    }
    delete[] cube;
}

template<class T>
void Grid3D<T>::SetElement(Point3D<T> element)
{
    int gridX = (int)(element.GetX() / cellSize);
    int gridY = (int)(element.GetY() / cellSize);
    int gridZ = (int)(element.GetY() / cellSize);
    cube[gridX][gridY][gridZ] = element;
}


template<class T>
bool Grid3D<T>::IsFarEnough(Point3D<T> point, float minDist)
{
    int gridX = (int)(point.GetX() / cellSize);
    int gridY = (int)(point.GetY() / cellSize);
    int gridZ = (int)(point.GetY() / cellSize);
    int xmin = std::max(gridX - 2, 0);
    int ymin = std::max(gridY - 2, 0);
    int zmin = std::max(gridZ - 2, 0);
    int xmax = std::min(gridX + 2, gwidth - 1);
    int ymax = std::min(gridY + 2, gheight - 1);
    int zmax = std::min(gridZ + 2, gdepth - 1);

    for (int z = zmin; z <= zmax; z++) {
        for (int y = ymin; y <= ymax; y++) {
            for (int x = xmin; x <= xmax; x++) {
                Point3D<T> p = cube[x][y][z];
                if (p.GetX() != Point3D<T>::ZERO.GetX() && p.GetY() != Point3D<T>::ZERO.GetY() && p.GetZ() != Point3D<T>::ZERO.GetZ()) {
                    float distance = Distance(point, p);
                    if (distance < minDist) return false;
                }
            }
        }
    }

    return true;
}

template<class T>
float Grid3D<T>::Distance(Point3D<T>& point, Point3D<T>& otherPoint)
{
    return sqrt( ( point.GetX() - otherPoint.GetX() ) * ( point.GetX() - otherPoint.GetX() ) +
                 ( point.GetY() - otherPoint.GetY() ) * (  point.GetY() - otherPoint.GetY() ) +
                 ( point.GetZ() - otherPoint.GetZ() ) * (  point.GetZ() - otherPoint.GetZ() ));
}



#endif // GRID3D_H
