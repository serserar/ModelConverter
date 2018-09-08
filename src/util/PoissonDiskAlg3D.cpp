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

#include "PoissonDiskAlg3D.h"
using namespace std;
PoissonDiskAlg3D::PoissonDiskAlg3D()
{

}

PoissonDiskAlg3D::PoissonDiskAlg3D(const PoissonDiskAlg3D& other)
{

}

PoissonDiskAlg3D::~PoissonDiskAlg3D()
{

}

void PoissonDiskAlg3D::GeneratePoisson(BBox* cube, float min_dist, int new_points_count, std::vector<Point3D<float>>& samplePoints)
{
    float cellSize = min_dist/sqrt(2);
    Grid3D<float> grid(cube->GetWidth(), cube->GetHeight(), cube->GetDepth(), cellSize);
    vector<Point3D<float>> processList ;
    PRNG prng;
    Point3D<float> firstPoint(prng.RandomInt(cube->GetWidth()),
                              prng.RandomInt(cube->GetHeight()),
                              prng.RandomInt(cube->GetDepth()));
    //update containers
    processList.push_back(firstPoint);
    samplePoints.push_back(firstPoint);
    grid.SetElement(firstPoint);
    //generate other points from points in queue.
    Point3D<float> point;
    while (!processList.empty())
    {
        point = PopRandom(processList, prng);
        for ( int i = 0; i < new_points_count; i++ )
        {
            Point3D<float> newPoint = GenerateRandomPointAround( point, min_dist, prng);
            //check that the point is in the image region
            //and no points exists in the point's neighbourhood
            bool insideCube = cube->Contains(newPoint.GetX(), newPoint.GetY(), newPoint.GetZ()); 
            // Accept candidates if it's inside the rect and farther than min_dist to any existing sample.
            if (insideCube && grid.IsFarEnough( newPoint, min_dist) )
            {
                processList.push_back( newPoint );
                samplePoints.push_back( newPoint );
                grid.SetElement( newPoint );
                continue;
            }
        }
    }
}

Point3D<float> PoissonDiskAlg3D::PopRandom(std::vector<Point3D<float> >& points, PRNG& generator)
{
    const int index = generator.RandomInt( points.size()-1 );
    const Point3D<float> p = points[ index ];
    points.erase( points.begin() + index );
    return p;
}

Point3D<float> PoissonDiskAlg3D::GenerateRandomPointAround(Point3D<float> point, float min_dist, PRNG& generator)
{
    // start with non-uniform distribution
    float r1 = generator.RandomFloat();
    float r2 = generator.RandomFloat();
    float r3 = generator.RandomFloat();
    // radius should be between MinDist and 2 * MinDist
    float radius = min_dist * ( r1 + 1.0f );

    // random angle
    float angle = 2.0f * M_PI * r2;
    float angle2 = 2.0f * M_PI * r3;

    // the new point is generated around the point (x, y)
    float x = point.GetX() + radius * cos(angle) + sin(angle2);
    float y = point.GetY() + radius * sin(angle) + sin(angle2);;
    float z = point.GetY() + radius * sin(angle2);

    return Point3D<float>(x, y, z);
}
