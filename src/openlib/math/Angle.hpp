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
 * Angle, in radians
 */
class Angle {
public:

  const static double PI; //<! pi

  /**
   * @brief convert radians to degrees
   * @param radians angle in radians
   * @return angle in degrees
   */
  static double radiansToDegrees(double radian);

  /**
   * @brief convert degrees to radians
   * @param degree angle in degrees
   * @return angle in radians
   */
  static double degreesToRadians(double degree);

  /**
   * @brief unwind an angle so that it is between -2 pi and 2 pi
   * @param radians angle
   * @return same angle, but between -2 pi and pi
   */
  static double unwind(double radians);

  /**
   * @brief count the number of full rotations in a given angle
   * @param radians angle
   * @return number of rations; -number of ratations if angle is negative
   */
  static int fullRotations(double radians);

  /**
   * @brief count the number of half rotations in a given angle
   * @param radians angle
   * @return number of half rations; -number of ratations if angle is negative
   */
  static int halfRotations(double radians);

  /**
   * @brief construct an angle at zero
   */
  Angle();

  /**
   * @brief construct an angle
   * @param radian
   */
  Angle(double radian);

  Angle(const Angle& other);

  virtual ~Angle() = default;

  /**
   * @brief get a copy of this angle that has been unwound
   * @return a copy of this angle, but unwound
   */
  Angle unwind() const;

  /**
   * @brief get a copy of this angle that has been truncated to the nearest 2pi
   * @return a copy of this angle, but truncated
   */
  Angle truncate() const;

  /**
   * @brief get a copy of this angle that has been floored to the nearest 2pi
   * @return a copy of this angle, but floored
   */
  Angle floor() const;

  /**
   * @brief count the number of full rotations of this angle
   * @return number of rations; -number of ratations if angle is negative
   */
  int fullRotations() const;

  /**
   * @brief count the number of half rotations of this angle
   * @return number of half rations; -number of ratations if angle is negative
   */
  int halfRotations() const;

  /**
   * @brief allow conversion between Angle and double
   */
  operator double() const;

  Angle& operator=(const Angle& other);

  Angle& operator+=(const Angle& other);
  Angle& operator-=(const Angle& other);

private:
  double radians;
};

}
