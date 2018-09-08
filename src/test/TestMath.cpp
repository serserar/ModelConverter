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
#include "../math/MVector3.h"
#include "../math/MPlane.h"

TEST_CASE( "Test vector" ) {
    MVector3<float> vec1(5.0f, 5.0f, 5.0f);
    MVector3<float> vec2(5.0f, 5.0f, 5.0f);
    MVector3<float> vec3 = vec1-vec2;
    MVector3<float> vec4;
    REQUIRE( vec3 == vec4 );
}

TEST_CASE( "Test plane Intersecction" ) {
    MVector3<float> normal(1.0f,2.0f,4.0f);
    MVector3<float> point(6.0f, 4.0f, 4.0f);
    MPlane<float> plane(normal, point);
    MVector3<float> origin;
    MVector3<float> direction(1.0f,2.0f, 5.0f);
    MVector3<float> intersection;
    plane.IntersectsRay(origin, direction, intersection);
    MVector3<float> testIntersection(1.2f, 2.4f, 6.0f);
    REQUIRE( intersection == testIntersection );
}

TEST_CASE( "Test plane Intersecction 2" ) {
    MVector3<float> normal(-2.0f, 6.0f, -3.0f);
    MVector3<float> point(2.0f, 7.0f, 1.0f);
    MPlane<float> plane(normal, point);
    MVector3<float> origin;
    MVector3<float> direction(8.0f,8.0f, 4.0f);
    MVector3<float> intersection;
    plane.IntersectsRay(origin, direction, intersection);
    MVector3<float> testIntersection(14.0f, 14.0f, 7.0f);
    REQUIRE( intersection == testIntersection );
}
