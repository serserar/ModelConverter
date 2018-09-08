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
#include "../base/Triangle.h"
#include "../base/Ray.h"
#include "../base/CollisionManager.h"

TEST_CASE( "Test Triangle" ) {
    Triangle triangle;
    triangle.v1.SetX(5.0f);
    triangle.v1.SetY(0.0f);
    triangle.v1.SetZ(0.0f);

    triangle.v2.SetX(0.0f);
    triangle.v2.SetY(5.0f);
    triangle.v2.SetZ(0.0f);

    triangle.v3.SetX(0.0f);
    triangle.v3.SetY(0.0f);
    triangle.v3.SetZ(5.0f);

    Ray ray;
    MVector3<float> rorigin;
    MVector3<float> rdirection(3.0f, 3.0f, 3.0f);
    ray.SetOrigin(rorigin);
    ray.SetDirection(rdirection);
    MVector3<float> intersectionPoint;
    CollisionManager collisionManager;
    SECTION( "Check Ray intersection" ) {
        INFO("Check Ray intersection");
        REQUIRE( collisionManager.RayIntersectsTriangle(rorigin, rdirection, triangle, intersectionPoint) );
    }

    Ray ray2;
    MVector3<float> rorigin2;
    MVector3<float> rdirection2(3.0f, 3.0f, -3.0f);
    ray2.SetOrigin(rorigin2);
    ray2.SetDirection(rdirection2);
    MVector3<float> intersectionPoint2;
    SECTION( "Check Ray intersection 2" ) {
        INFO("Check Ray intersection 2");
        REQUIRE( !collisionManager.RayIntersectsTriangle(rorigin2, rdirection2, triangle, intersectionPoint2) );
    }

    Ray ray3;
    MVector3<float> rorigin3;
    MVector3<float> rdirection3(5.0f, 3.0f, 3.0f);
    ray3.SetOrigin(rorigin3);
    ray3.SetDirection(rdirection3);
    MVector3<float> intersectionPoint3;
    SECTION( "Check Ray intersection 3" ) {
        INFO("Check Ray intersection 3");
        REQUIRE( collisionManager.RayIntersectsTriangle(rorigin3, rdirection3, triangle, intersectionPoint3) );
    }

    Ray ray4;
    MVector3<float> rorigin4;
    MVector3<float> rdirection4(5.0f, 0.0f, 0.0f);
    ray4.SetOrigin(rorigin4);
    ray4.SetDirection(rdirection4);
    MVector3<float> intersectionPoint4;
    SECTION( "Check Ray intersection 4" ) {
        INFO("Check Ray intersection 4");
        REQUIRE( collisionManager.RayIntersectsTriangle(rorigin4, rdirection4, triangle, intersectionPoint4) );
    }

    Ray ray5;
    MVector3<float> rorigin5;
    MVector3<float> rdirection5(0.0f, 5.0f, 0.0f);
    ray5.SetOrigin(rorigin5);
    ray5.SetDirection(rdirection5);
    MVector3<float> intersectionPoint5;
    SECTION( "Check Ray intersection 5" ) {
        INFO("Check Ray intersection 5");
        REQUIRE( collisionManager.RayIntersectsTriangle(rorigin5, rdirection5, triangle, intersectionPoint5) );
    }

    Ray ray6;
    MVector3<float> rorigin6;
    MVector3<float> rdirection6(0.0f, 0.0f, 5.0f);
    ray5.SetOrigin(rorigin6);
    ray5.SetDirection(rdirection6);
    MVector3<float> intersectionPoint6;
    SECTION( "Check Ray intersection 6" ) {
        INFO("Check Ray intersection 6");
        REQUIRE( collisionManager.RayIntersectsTriangle(rorigin6, rdirection6, triangle, intersectionPoint6) );
    }
}
