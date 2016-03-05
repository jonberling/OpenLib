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

#include "Angle.hpp"

using namespace openlib;

const double Angle::PI = M_PI;

double Angle::radiansToDegrees(double radian) {
  return radian * 180.0 / PI;
}

double Angle::degreesToRadians(double degree) {
  return degree * PI / 180.0;
}

double Angle::unwind(double radians) {
  auto rolls = fullRotations(radians);
  return radians - (rolls * 2.0 * PI);
}

int Angle::fullRotations(double radians) {
  return std::trunc(radians / (2.0 * PI));
}

int Angle::halfRotations(double radians) {
  return std::trunc(radians / PI);
}

Angle::Angle(): radians(0) { }

Angle::Angle(double radian): radians(radian) { }

Angle::Angle(const Angle& other): radians(other.radians) { }

Angle Angle::unwind() const {
  return unwind(radians);
}

Angle Angle::truncate() const {
  return radians - unwind(radians);
}

Angle Angle::floor() const {
  return std::floor(radians / (2.0 * PI)) * 2.0 * PI;
}

int Angle::fullRotations() const {
  return fullRotations(radians);
}

int Angle::halfRotations() const {
  return halfRotations(radians);
}

Angle::operator double() const {
  return radians;
}

Angle& Angle::operator=(const Angle& other) {
  radians = other.radians;
  return *this;
}

Angle& Angle::operator+=(const Angle& other) {
  radians += other.radians;
  return *this;
}

Angle& Angle::operator-=(const Angle& other) {
  radians -= other.radians;
  return *this;
}
