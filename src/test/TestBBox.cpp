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

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../base/BBox.h"

TEST_CASE( "Test BBox" ) {
    MVector3<float> min1;
    MVector3<float> max1(10.0f, 10.0f, 10.0f);
    BBox box1(min1, max1);
    MVector3<float> min2;
    MVector3<float> max2(9.0f, 9.0f, 9.0f);
    BBox box2(min2, max2);
    MVector3<float> min3;
    MVector3<float> max3(9.0f, 10.1f, 9.0f);
    BBox box3(min3, max3);
    MVector3<float> min4;
    MVector3<float> max4(10.0f, 10.0f, 10.0f);
    BBox box4(min4, max4);
    SECTION( "Check box1 contains box2" ) {
        INFO("Check box1 contains box2");
        REQUIRE( box1.Contains(box2) );
    }
    SECTION( "Check box2 not contains box1" ) {
        INFO("Check box2 not contains box1");
        REQUIRE( !box2.Contains(box1) );
    }
    SECTION( "Check box1 not contains box3" ) {
        INFO("Check box1 not contains box3");
        REQUIRE( !box1.Contains(box3) );
    }
    SECTION( "Check box1 contains box4" ) {
        INFO("Check box1 contains box4");
        REQUIRE(box1.Contains(box4));
        REQUIRE(box4.Contains(box1));
    }
    SECTION( "Octree" ) {
        BBox* octant = box1.OcTreeSubDivision();
        if(octant) {

        }
    }
}
