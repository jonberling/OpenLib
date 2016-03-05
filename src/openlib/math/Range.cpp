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

#include "Range.hpp"

using namespace openlib;

Range::Range(): lower(0), upper(0) { }

Range::Range(double limit_a, double limit_b) {
  limits(limit_a, limit_b);
}

void Range::limits(double limit_a, double limit_b) {
  this->lower = std::fmin(limit_a, limit_b);
  this->upper = std::fmax(limit_a, limit_b);
}

double Range::lowerBound() const {
  return lower;
}

double Range::upperBound() const {
  return upper;
}

bool Range::withinRange(double scalar) const {
  return (scalar >= lower && scalar <= upper);
}

double Range::scale(double scalar, Range scalarsRange) const {
  double b = (lower - upper) / (scalarsRange.lower - scalarsRange.upper);
  double c = lower - scalarsRange.lower * (lower - upper) / (scalarsRange.lower - scalarsRange.upper);
  double x = scalar;

  return b*x+c;
}
