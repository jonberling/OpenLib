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
#pragma once

namespace openlib {

/**
 * Vector 2D
 */
class Vector2d {
public:

  /**
   * @brief DEFAULT_COMPARISON_EPSILON default value for comparison_epsilon
   * The default value is 0
   */
  const static double DEFAULT_COMPARISON_EPSILON;

  /**
   * @brief comparison_epsilon
   * When comparing for equality, the x and y values of the vectors must be
   * within this epsilon value to be considered equal. This value defaults
   * to 0 so only exact matches are equal.
   *
   * This value is global.
   */
  static double comparison_epsilon;

  double x;
  double y;

  static Vector2d fromPolarCoordinates(double magnitude, double angle);

  static double magnitude(double x, double y);

  static double angle(double x, double y);

  Vector2d();

  Vector2d(double x, double y);

  Vector2d(const Vector2d& copy);

  virtual ~Vector2d() = default;

  virtual void normalize();

  virtual void scale(double value);

  virtual double magnitude() const;

  virtual double angle() const;

  const Vector2d operator+(const Vector2d& other) const;

  const Vector2d operator-(const Vector2d& other) const;

  bool operator==(const Vector2d& other) const;

  bool operator!=(const Vector2d& other) const;

private:
  void init(double x, double y);
};

}
