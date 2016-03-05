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

#include "Vector2d.hpp"

using namespace openlib;


const double Vector2d::DEFAULT_COMPARISON_EPSILON = 0.0;
double Vector2d::comparison_epsilon = Vector2d::DEFAULT_COMPARISON_EPSILON;

Vector2d::Vector2d() {
  init(0, 0);
}

Vector2d::Vector2d(double x, double y) {
  init(x, y);
}

Vector2d::Vector2d(const Vector2d& copy) {
  init(copy.x, copy.y);
}

void Vector2d::normalize() {
  double m = magnitude();
  x /= m;
  y /= m;
}

void Vector2d::scale(double value) {
  x *= value;
  y *= value;
}

double Vector2d::magnitude() const {
  return magnitude(x, y);
}

double Vector2d::angle() const {
 return angle(x, y);
}

Vector2d Vector2d::fromPolarCoordinates(double magnitude, double angle) {
  double x = magnitude * std::cos(angle);
  double y = magnitude * std::sin(angle);
  return Vector2d(x, y);
}

double Vector2d::magnitude(double x, double y) {
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

double Vector2d::angle(double x, double y) {
 return std::atan2(y, x);
}

void Vector2d::init(double x, double y) {
  this->x = x;
  this->y = y;
}

const Vector2d Vector2d::operator+(const Vector2d& other) const {
  return Vector2d(x + other.x, y + other.y);
}

const Vector2d Vector2d::operator-(const Vector2d& other) const {
  return Vector2d(x - other.x, y - other.y);
}

bool Vector2d::operator==(const Vector2d& other) const {
  return std::abs(x - other.x) <= comparison_epsilon && std::abs(y - other.y) <= comparison_epsilon;
}

bool Vector2d::operator!=(const Vector2d& other) const {
  return !(*this == other);
}
