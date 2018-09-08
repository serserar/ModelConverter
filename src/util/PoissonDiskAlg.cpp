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

#include "PoissonDiskAlg.h"

PoissonDiskAlg::PoissonDiskAlg()
{

}

PoissonDiskAlg::PoissonDiskAlg(const PoissonDiskAlg& other)
{

}

PoissonDiskAlg::~PoissonDiskAlg()
{

}

void PoissonDiskAlg::GeneratePoisson(float width, float height, float min_dist, int new_points_count, std::vector<Point2D<float>>& samplePoints)
{
    float cellSize = min_dist/sqrt(2);
    Grid2D<float> grid(width, height, cellSize);
    vector<Point2D<float>> processList ;
    PRNG prng;
    Point2D<float> firstPoint(prng.RandomInt(width), prng.RandomInt(height));
    //update containers
    processList.push_back(firstPoint);
    samplePoints.push_back(firstPoint);
    grid.SetElement(firstPoint);
    //generate other points from points in queue.
    Point2D<float> point;
    while (!processList.empty())
    {
        point = PopRandom(processList, prng);
        for ( int i = 0; i < new_points_count; i++ )
		{
            Point2D<float> newPoint = generateRandomPointAround( point, min_dist, prng);
            //check that the point is in the image region
            //and no points exists in the point's neighbourhood
            bool Fits = newPoint.GetX() <= width && newPoint.GetY() <= height;

			if ( Fits && !grid.IsInNeighbourhood( newPoint, min_dist) )
			{
				processList.push_back( newPoint );
				samplePoints.push_back( newPoint );
				grid.SetElement( newPoint );
				continue;
			}
        }
    }
}

Point2D<float> PoissonDiskAlg::PopRandom(std::vector<Point2D<float> >& points, PRNG& generator)
{
    const int Idx = generator.RandomInt( points.size()-1 );
	const Point2D<float> p = points[ Idx ];
	points.erase( points.begin() + Idx );
	return p;
}

Point2D<float> PoissonDiskAlg::generateRandomPointAround(Point2D<float> point, float min_dist, PRNG& generator)
{
    // start with non-uniform distribution
	float r1 = generator.RandomFloat();
	float r2 = generator.RandomFloat();
    // radius should be between MinDist and 2 * MinDist
	float radius = min_dist * ( r1 + 1.0f );

	// random angle
	float angle = 2 * 3.141592653589f * r2;

	// the new point is generated around the point (x, y)
	float x = point.GetX() + radius * cos( angle );
	float y = point.GetY() + radius * sin( angle );

	return Point2D<float>( x, y );
}
    
