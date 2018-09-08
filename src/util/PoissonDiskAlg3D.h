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

#ifndef POISSONDISKALG3D_H
#define POISSONDISKALG3D_H
#include "../base/BBox.h"
#include "Grid3D.h"
#include "Point3D.h"
#include "PRNG.h"
#include <vector>
/**
 * The idea is to generate points around existing points, 
 * and to check whether they can be added so that they don’t disturb the minimum distance requirement.
 * A grid is used to perform fast lookups * of points. 
 * Two lists keep track of points that are being generated, and those that needs processing.
 * 
 * 
 *   1-A grid is created such that every cell will contain at most one sampling point.
 *       If points are at least distance r from each other, then the cell size must be r/2?. The ill-rendered symbol ? *is pi.
 *   2-The first point is randomly chosen, and put in the output list, processing list and grid.
 *   3-Until the processing list is empty, do the following:
 *     3.1-Choose a random point from the processing list.
 *     3.2-For this point, generate up to k points, randomly selected from the annulus surrounding the point.
 *         You can choose k – a value of 30 gives good results. In general, larger values give tighter packings, but make the algorithm run slower. For every generated point:
 *           3.2.1-Use the grid to check for points that are too close to this point. See below for more detail.
 *           3.2.2-If there is none, add the point to the output list, processing list, and grid.
 *     3.3-Remove the point from the processing list.
 *   4-Return the output list as the sample points.
 *
 * 
 * @todo write docs
 */
class PoissonDiskAlg3D
{
public:
    /**
     * Default constructor
     */
    PoissonDiskAlg3D();

    /**
     * Copy Constructor
     *
     * @param other TODO
     */
    PoissonDiskAlg3D(const PoissonDiskAlg3D& other);

    /**
     * Destructor
     */
    ~PoissonDiskAlg3D();

    void GeneratePoisson(BBox* cube, float min_dist, int new_points_count, std::vector<Point3D<float>>& samplePoints);
private :
    Point3D<float> PopRandom(std::vector<Point3D<float>>& points, PRNG& generator);
    Point3D<float> GenerateRandomPointAround(Point3D<float> point, float min_dist, PRNG& generator);
};

#endif // POISSONDISKALG3D_H
