/****************************************************************************
Copyright (c) 2016, 2018, OpenLib Project
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
#include <cstdio>

#include <string>

#include <gtest/gtest.h>

#include <openlib/Array.h>

TEST(ArrayExample, Example1) {
  /*
   * Example 1: create an array, fill it with elements
   */

  // create an int array with 3 elements
  openlib::Array<int> array(3);

  // place 0, 1, 2 into the array
  for (std::size_t i = 0; i < array.size(); i++) {
    array[i] = i;
  }

  // we expect the array will hold 0, 1, 2
  int check = 0;
  for (const auto& i : array) {
    EXPECT_EQ(i, check++);
  }
}

TEST(ArrayExample, Example2) {
  /*
   * Example 2: create an array from an initializer list
   */

  // create an string array with 2 elements
  openlib::Array<std::string> array = {"hello", "world"};

  // we expect the array will hold "hello", "world"
  EXPECT_EQ("hello", array[0]);
  EXPECT_EQ("world", array[1]);
}

TEST(ArrayExample, Example3) {
  /*
   * Example 3: pass array as a c-style array
   */

  // create a byte array with 10 elements
  openlib::Array<uint8_t> array(10);

  // pass the array into memset
  memset(array, 42, array.size());

  // check that all values are 42
  for (const auto& i : array) {
    EXPECT_EQ(i, 42);
  }
}

