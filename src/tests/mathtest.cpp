/****************************************************************************
Copyright (c) 2016, OpenLib Project
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/
#include <cmath>

#include <gtest/gtest.h>

#include <openlib/math.hpp>

const static double ALLOWED_ERROR = 0.0000001;

using namespace std;

TEST(Vector2d, isContructable) {
  openlib::Vector2d vector;
  // this test passes if it compiles
}

TEST(Vector2d, isConstructableWithParameters) {
  openlib::Vector2d vector(1, 2);

  EXPECT_NEAR(vector.x, 1, ALLOWED_ERROR);
  EXPECT_NEAR(vector.y, 2, ALLOWED_ERROR);
}

TEST(Vector2d, defaultsToZero) {
  openlib::Vector2d vector;

  EXPECT_NEAR(vector.x, 0, ALLOWED_ERROR);
  EXPECT_NEAR(vector.y, 0, ALLOWED_ERROR);
}

TEST(Vector2d, isCopyable) {
  openlib::Vector2d vector(1, 2);
  openlib::Vector2d copy(vector);

  EXPECT_NEAR(copy.x, 1, ALLOWED_ERROR);
  EXPECT_NEAR(copy.y, 2, ALLOWED_ERROR);
}

TEST(Vector2d, magnitudeStaticMethod) {
  double m = openlib::Vector2d::magnitude(3, 4);

  EXPECT_NEAR(5, m, ALLOWED_ERROR);
}

TEST(Vector2d, angleStaticMethod) {
  double a1 = openlib::Vector2d::angle( 1,  0);
  double a2 = openlib::Vector2d::angle( 1,  1);
  double a3 = openlib::Vector2d::angle( 0,  1);
  double a4 = openlib::Vector2d::angle(-1,  1);
  double a5 = openlib::Vector2d::angle(-1,  0);
  double a6 = openlib::Vector2d::angle(-1, -1);
  double a7 = openlib::Vector2d::angle( 0, -1);
  double a8 = openlib::Vector2d::angle( 1, -1);

  EXPECT_NEAR(a1,  0.00 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(a2,  0.25 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(a3,  0.50 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(a4,  0.75 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(a5,  1.00 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(a6, -0.75 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(a7, -0.50 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(a8, -0.25 * M_PI, ALLOWED_ERROR);
}

TEST(Vector2d, fromPolarCoordinatesStaticMethod) {
  openlib::Vector2d vector = openlib::Vector2d::fromPolarCoordinates(openlib::Vector2d::magnitude(1, 1), openlib::Vector2d::angle( 1,  1));

  EXPECT_NEAR(vector.x, 1, ALLOWED_ERROR);
  EXPECT_NEAR(vector.y, 1, ALLOWED_ERROR);
}

TEST(Vector2d, magnitudeMethod) {
  openlib::Vector2d vector(3, 4);

  EXPECT_NEAR(5, vector.magnitude(), ALLOWED_ERROR);
}

TEST(Vector2d, angleMethod) {
  openlib::Vector2d vector;

  vector.x =  1; vector.y =  0;
  EXPECT_NEAR(vector.angle(),  0.00 * M_PI, ALLOWED_ERROR);

  vector.x =  1; vector.y =  1;
  EXPECT_NEAR(vector.angle(),  0.25 * M_PI, ALLOWED_ERROR);

  vector.x =  0; vector.y =  1;
  EXPECT_NEAR(vector.angle(),  0.50 * M_PI, ALLOWED_ERROR);

  vector.x = -1; vector.y =  1;
  EXPECT_NEAR(vector.angle(),  0.75 * M_PI, ALLOWED_ERROR);

  vector.x = -1; vector.y =  0;
  EXPECT_NEAR(vector.angle(),  1.00 * M_PI, ALLOWED_ERROR);

  vector.x = -1; vector.y = -1;
  EXPECT_NEAR(vector.angle(), -0.75 * M_PI, ALLOWED_ERROR);

  vector.x =  0; vector.y = -1;
  EXPECT_NEAR(vector.angle(), -0.50 * M_PI, ALLOWED_ERROR);

  vector.x =  1; vector.y = -1;
  EXPECT_NEAR(vector.angle(), -0.25 * M_PI, ALLOWED_ERROR);
}

TEST(Vector2d, normalize) {
  openlib::Vector2d vector(3, 4);

  vector.normalize();

  EXPECT_NEAR(vector.x, 3.0/5.0, ALLOWED_ERROR);
  EXPECT_NEAR(vector.y, 4.0/5.0, ALLOWED_ERROR);

  EXPECT_NEAR(vector.magnitude(), 1, ALLOWED_ERROR);
}

TEST(Vector2d, scale) {
  openlib::Vector2d vector(3, 2);

  vector.scale(2);

  EXPECT_NEAR(vector.x, 6, ALLOWED_ERROR);
  EXPECT_NEAR(vector.y, 4, ALLOWED_ERROR);
}

TEST(Vector2d, operatorPlus) {
  openlib::Vector2d a(4, 3);
  openlib::Vector2d b(2, 2);

  openlib::Vector2d c = a + b;

  EXPECT_NEAR(c.x, 6, ALLOWED_ERROR);
  EXPECT_NEAR(c.y, 5, ALLOWED_ERROR);
}

TEST(Vector2d, operatorMinus) {
  openlib::Vector2d a(4, 3);
  openlib::Vector2d b(2, 2);

  openlib::Vector2d c = a - b;

  EXPECT_NEAR(c.x, 2, ALLOWED_ERROR);
  EXPECT_NEAR(c.y, 1, ALLOWED_ERROR);
}

TEST(Vector2d, operatorEqual) {
  openlib::Vector2d a(1, 2);
  openlib::Vector2d b(1, 2);
  openlib::Vector2d c(2, 2);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
}

TEST(Vector2d, operatorEqualWithEpsilon) {
  openlib::Vector2d a(1, 2);
  openlib::Vector2d b(1.1, 2.1);
  openlib::Vector2d c(2, 2);

  openlib::Vector2d::comparison_epsilon = 0.5;

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);

  // reset global values
  openlib::Vector2d::comparison_epsilon = openlib::Vector2d::DEFAULT_COMPARISON_EPSILON;
}


TEST(Vector2d, operatorNotEqual) {
  openlib::Vector2d a(1, 2);
  openlib::Vector2d b(1, 2);
  openlib::Vector2d c(2, 2);

  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
}

TEST(Angle, isConstructible) {
  openlib::Angle angle;

  EXPECT_NEAR(angle, 0, ALLOWED_ERROR);
}

TEST(Angle, isConstructibleWithParameter) {
  openlib::Angle angle(1);

  EXPECT_NEAR(angle, 1, ALLOWED_ERROR);
}

TEST(Angle, isCopyable) {
  openlib::Angle angle1(1);
  openlib::Angle angle2(angle1);

  EXPECT_NEAR(angle1, angle2, ALLOWED_ERROR);
}

TEST(Angle, static_radianToDegree) {
  EXPECT_NEAR(180.0, openlib::Angle::radiansToDegrees(M_PI), ALLOWED_ERROR);
}

TEST(Angle, static_degreeToRadian) {
  EXPECT_NEAR(M_PI, openlib::Angle::degreesToRadians(180.0), ALLOWED_ERROR);
}

TEST(Angle, static_unwind) {
  double angle1( 5 * M_PI);
  double angle2(-5 * M_PI);

  EXPECT_NEAR(openlib::Angle::unwind(angle1),  M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(openlib::Angle::unwind(angle2), -M_PI, ALLOWED_ERROR);
}

TEST(Angle, static_fullRotations) {
  double angle1( 5 * M_PI);
  double angle2(-5 * M_PI);

  EXPECT_NEAR(openlib::Angle::fullRotations(angle1),  2, ALLOWED_ERROR);
  EXPECT_NEAR(openlib::Angle::fullRotations(angle2), -2, ALLOWED_ERROR);
}

TEST(Angle, static_halfRotations) {
  double angle1( 5 * M_PI);
  double angle2(-5 * M_PI);

  EXPECT_NEAR(openlib::Angle::halfRotations(angle1),  5, ALLOWED_ERROR);
  EXPECT_NEAR(openlib::Angle::halfRotations(angle2), -5, ALLOWED_ERROR);
}

TEST(Angle, piEqualsM_PI) {
  EXPECT_EQ(openlib::Angle::PI, M_PI);
}

TEST(Angle, unwind) {
  openlib::Angle angle1( 5 * M_PI);
  openlib::Angle angle2(-5 * M_PI);

  EXPECT_NEAR(angle1.unwind(),  M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(angle2.unwind(), -M_PI, ALLOWED_ERROR);

  EXPECT_NEAR(angle1,  5 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(angle2, -5 * M_PI, ALLOWED_ERROR);
}

TEST(Angle, truncate) {
  openlib::Angle angle1( 5 * M_PI);
  openlib::Angle angle2(-5 * M_PI);

  EXPECT_NEAR(angle1.truncate(),  4 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(angle2.truncate(), -4 * M_PI, ALLOWED_ERROR);

  EXPECT_NEAR(angle1,  5 * M_PI, ALLOWED_ERROR);
  EXPECT_NEAR(angle2, -5 * M_PI, ALLOWED_ERROR);
}

TEST(Angle, fullRotations) {
  openlib::Angle angle1( 5 * M_PI);
  openlib::Angle angle2(-5 * M_PI);

  EXPECT_NEAR(angle1.fullRotations(),  2, ALLOWED_ERROR);
  EXPECT_NEAR(angle2.fullRotations(), -2, ALLOWED_ERROR);
}

TEST(Angle, halflRotations) {
  openlib::Angle angle1( 5 * M_PI);
  openlib::Angle angle2(-5 * M_PI);

  EXPECT_NEAR(angle1.halfRotations(),  5, ALLOWED_ERROR);
  EXPECT_NEAR(angle2.halfRotations(), -5, ALLOWED_ERROR);
}

TEST(Angle, operatorDouble) {
  openlib::Angle angle(3);

  EXPECT_NEAR(angle, 3, ALLOWED_ERROR);
}

TEST(Angle, operatorAssign) {
  openlib::Angle angle;

  angle = 3;
  EXPECT_NEAR(angle, 3, ALLOWED_ERROR);
}

TEST(Angle, operatorPlus) {
  openlib::Angle angle(4);

  angle = 1 + angle;

  EXPECT_NEAR(angle, 5, ALLOWED_ERROR);
}

TEST(Angle, operatorMinus) {
  openlib::Angle angle(4);

  angle = 7 - angle;

  EXPECT_NEAR(angle, 3, ALLOWED_ERROR);
}

TEST(Angle, operatorPlusAssign) {
  openlib::Angle angle(4);

  angle += 1;

  EXPECT_NEAR(angle, 5, ALLOWED_ERROR);
}

TEST(Angle, operatorMinusAssign) {
  openlib::Angle angle(4);

  angle -= 1;

  EXPECT_NEAR(angle, 3, ALLOWED_ERROR);
}

TEST(Angle, operatorEquals) {
  openlib::Angle angle1(1);
  openlib::Angle angle2(1);
  openlib::Angle angle3(2);

  EXPECT_TRUE( angle1 == angle2);
  EXPECT_FALSE(angle1 == angle3);
}

TEST(Angle, operatorNotEquals) {
  openlib::Angle angle1(1);
  openlib::Angle angle2(1);
  openlib::Angle angle3(2);

  EXPECT_FALSE(angle1 != angle2);
  EXPECT_TRUE( angle1 != angle3);
}

TEST(Angle, operatorLessThan) {
  openlib::Angle angle1(1);
  openlib::Angle angle2(1);
  openlib::Angle angle3(2);

  EXPECT_TRUE( angle1 < angle3);
  EXPECT_FALSE(angle1 < angle2);
}

TEST(Angle, operatorGreaterThan) {
  openlib::Angle angle1(1);
  openlib::Angle angle2(1);
  openlib::Angle angle3(2);

  EXPECT_TRUE( angle3 > angle2);
  EXPECT_FALSE(angle1 > angle2);
}

TEST(Angle, operatorLessThanEquals) {
  openlib::Angle angle1(1);
  openlib::Angle angle2(1);
  openlib::Angle angle3(2);

  EXPECT_TRUE( angle1 <= angle3);
  EXPECT_TRUE( angle1 <= angle2);
  EXPECT_FALSE(angle3 <= angle2);
}

TEST(Angle, operatorGreaterThanEquals) {
  openlib::Angle angle1(1);
  openlib::Angle angle2(1);
  openlib::Angle angle3(2);

  EXPECT_TRUE( angle3 >= angle2);
  EXPECT_TRUE( angle1 >= angle2);
  EXPECT_FALSE(angle1 >= angle3);
}

TEST(Range, isConstructible) {
  openlib::Range range;
  // if this test compiles is passes
}

TEST(Range, isConstructibleWithParameters) {
  openlib::Range range(-1, 1);
  // if this test compiles is passes
}

TEST(Range, lowerBound) {
  openlib::Range rangeA( 1, -1);
  openlib::Range rangeB(-1,  1);

  EXPECT_NEAR(rangeA.lowerBound(), -1, ALLOWED_ERROR);
  EXPECT_NEAR(rangeB.lowerBound(), -1, ALLOWED_ERROR);
}

TEST(Range, upperBound) {
  openlib::Range rangeA( 1, -1);
  openlib::Range rangeB(-1,  1);

  EXPECT_NEAR(rangeA.upperBound(), 1, ALLOWED_ERROR);
  EXPECT_NEAR(rangeB.upperBound(), 1, ALLOWED_ERROR);
}

TEST(Range, limits) {
  openlib::Range rangeA;
  openlib::Range rangeB;

  rangeA.limits(-1,  1);
  rangeB.limits( 1, -1);

  EXPECT_NEAR(rangeA.lowerBound(), -1, ALLOWED_ERROR);
  EXPECT_NEAR(rangeB.lowerBound(), -1, ALLOWED_ERROR);

  EXPECT_NEAR(rangeA.upperBound(), 1, ALLOWED_ERROR);
  EXPECT_NEAR(rangeB.upperBound(), 1, ALLOWED_ERROR);
}

TEST(Range, withinRange) {
  openlib::Range range(1, 2);

  EXPECT_TRUE(range.withinRange(1.0));
  EXPECT_TRUE(range.withinRange(1.5));
  EXPECT_TRUE(range.withinRange(2.0));

  EXPECT_FALSE(range.withinRange(0.5));
  EXPECT_FALSE(range.withinRange(2.5));
}

TEST(Range, scale) {
  openlib::Range input(0, 5);
  openlib::Range output(0, 100);

  EXPECT_NEAR(  0, output.scale(0, input), ALLOWED_ERROR);
  EXPECT_NEAR( 20, output.scale(1, input), ALLOWED_ERROR);
  EXPECT_NEAR( 40, output.scale(2, input), ALLOWED_ERROR);
  EXPECT_NEAR( 60, output.scale(3, input), ALLOWED_ERROR);
  EXPECT_NEAR( 80, output.scale(4, input), ALLOWED_ERROR);
  EXPECT_NEAR(100, output.scale(5, input), ALLOWED_ERROR);
}
