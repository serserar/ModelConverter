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

#ifndef GRID2D_H
#define GRID2D_H
#include "Point2D.h"
#include <vector>
#include <utility>
#include <cmath>

/**
 * @todo write docs
 */
template <class T>
class Grid2D
{
public:
    /**
     * Default constructor
     */
    Grid2D();

    /**
     * Default constructor
     */
    Grid2D(int width, int height, T cellSize);

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    Grid2D(const Grid2D& other);

    Point2D<T> GetElement(int x,int y);
    void SetElement(int x, int y, Point2D<T> element);
    void SetElement(Point2D<T> element);
    static std::pair<int,int> PointToGrid(Point2D<T> point, T cellSize);
    bool IsInNeighbourhood( Point2D<T> point, float minDist);
    T Distance(Point2D<T>& point, Point2D<T>& otherPoint);
private:
    int gwidth;
    int gheight;
    T cellSize;
    std::vector<Point2D<T>> gridData;
};

template<class T>
Grid2D<T>::Grid2D()
{
    this->gwidth = 0;
    this->gheight= 0;
    this->cellSize = T {};
}

template<class T>
Grid2D<T>::Grid2D(int width, int height, T cellSize)
{
    this->gwidth = ceil(width/cellSize);
    this->gheight = ceil(height/cellSize); 
    this->gridData.reserve(this->gwidth * this->gheight);
    this->gridData.resize(this->gwidth * this->gheight);
    this->cellSize = cellSize;
}

template<class T>
Grid2D<T>::Grid2D(const Grid2D<T>& other)
{
    this->gwidth = other.gwidth;
    this->gheight = other.gheight;
    this->cellSize = other.cellSize;
    this->gridData = other.gridData;
}


template<class T>
Point2D<T> Grid2D<T>::GetElement(int x, int y)
{
    int index = y*gwidth + x;
    return gridData[index];
}

template<class T>
void Grid2D<T>::SetElement(int x, int y, Point2D<T> element)
{
    int index = y*gwidth + x;
    gridData.insert(gridData.begin() + index, element);
}

template<class T>
void Grid2D<T>::SetElement(Point2D<T> element)
{
    auto coords = PointToGrid(element, cellSize);
    int index = coords.second*gwidth + coords.first;
    gridData.insert(gridData.begin() + index, element);
}


template<class T>
std::pair<int, int> Grid2D<T>::PointToGrid(Point2D<T> point, T cellSize)
{
    int gridX = (int)(point.GetX() / cellSize);
    int gridY = (int)(point.GetY() / cellSize);
    return std::make_pair(gridX, gridY);
}

template<class T>
bool Grid2D<T>::IsInNeighbourhood(Point2D<T> point, float minDist)
{
    auto coords = PointToGrid(point, cellSize);

    // number of adjucent cells to look for neighbour points
    const int D = 5;

    // scan the neighbourhood of the point in the grid
    for ( int i = coords.first - D; i < coords.first + D; i++ )
    {
        for ( int j = coords.second - D; j < coords.second + D; j++ )
        {
            if ( i >= 0 && i < gwidth && j >= 0 && j < gheight )
            {
                Point2D<T> otherPoint = GetElement(i,j);
                if (Distance(point, otherPoint) < minDist ) {
                    return true;

                }
            }
        }
    }


    return false;
}

template<class T> 
T Grid2D<T>::Distance(Point2D<T>& point, Point2D<T>& otherPoint)
{
    return sqrt( ( point.GetX() - otherPoint.GetX() ) * ( point.GetX() - otherPoint.GetX() ) + ( point.GetY() - otherPoint.GetY() ) * (  point.GetY() - otherPoint.GetY() ) );
}

#endif // GRID2D_H
