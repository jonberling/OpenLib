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
#include <time.h>

#include "ElapsedTime.hpp"

using namespace openlib;

const static int CLOCK = CLOCK_MONOTONIC;
const static double NANOSECONDS_PER_SECOND = 1000000000.0;

ElapsedTime ElapsedTime::createElapsedTime() {
  ElapsedTime time;
  time.reset();
  return time;
}

ElapsedTime::ElapsedTime():
    start(0.0) { }

double ElapsedTime::time() const {
  return now() - start;
}

void ElapsedTime::reset() {
  start = now();
}

double ElapsedTime::startTime() const {
  return start;
}

double ElapsedTime::now() const {
  timespec ts;
  clock_gettime(CLOCK, &ts);
  return (ts.tv_sec + (ts.tv_nsec / NANOSECONDS_PER_SECOND));
}
