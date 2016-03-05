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
 * Ranges
 */
class Range {
public:

  /**
   * @brief constructs a range, with the limits being set to 0
   */
  Range();

  /**
   * @brief constructs a range with the given limits
   * @param limit_a
   * @param limit_b
   */
  Range(double limit_a, double limit_b);

  virtual ~Range() = default;

  /**
   * @brief set the limits for this range
   * @param limit_a one extreme for this range
   * @param limit_b another extreme for this range
   */
  virtual void limits(double limit_a, double limit_b);

  /**
   * @brief get the lower bound of this range
   * @return lower bound of this range
   */
  virtual double lowerBound() const;

  /**
   * @brief get the upper bound of this range
   * @return upper bound of this range
   */
  virtual double upperBound() const;

  /**
   * @brief returns true if the given scalar is within (inclusive) the lower and upper bounds of this range
   * @param scalar a single value to test
   * @return true if within range; otherwise false
   */
  virtual bool withinRange(double scalar) const;

  /**
   * @brief scale a given scalar with a given range into a new scalar within the range of this range
   * @param scalar value to scale
   * @param scalarsRange the range of the scalar to scale
   * @return a scalar, in the range of this scalar
   */
  double scale(double scalar, Range scalarsRange) const;

private:

  double lower;
  double upper;
};

}
