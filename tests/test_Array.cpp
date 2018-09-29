/****************************************************************************
Copyright (c) 2016, 2018, OpenLib Projec
All rights reserved.

Redistribution and use in source and binary forms, with or withou
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, thi
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentatio
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, TH
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AR
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABL
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIA
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS O
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVE
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE US
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/

#include <gtest/gtest.h>

#include <openlib/Array.h>

TEST(Array, isConstructable) {
  openlib::Array<int> array(0);
  // if the test gets this far it passe
}

TEST(Array, isConstructableViaInitList) {
  openlib::Array<int> array = {1, 2, 3};
  // if the test gets this far it passe
}

TEST(Array, getSize) {
  openlib::Array<int> array(3);
  EXPECT_EQ(array.size(), 3);
}

TEST(Array, getSizeViaInitList) {
  openlib::Array<int> array = {1, 2, 3, 4};
  EXPECT_EQ(array.size(), 4);
}

TEST(Array, atReturnCorrectValue) {
  openlib::Array<int> array = {1, 2, 3, 4};

  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array.at(i), i + 1);
  }
}

TEST(Array, atReturnCorrectValueConst) {
  const openlib::Array<int> array = {1, 2, 3, 4};

  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array.at(i), i + 1);
  }
}

TEST(Array, operatorBracketReturnCorrectValue) {
  openlib::Array<int> array = {1, 2, 3, 4};

  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array[i], i + 1);
  }
}

TEST(Array, operatorBracketReturnCorrectValueConst) {
  const openlib::Array<char> array = {'a', 'b', 'c', 'd'};

  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array[i], 'a' + i);
  }
}

TEST(Array, frontReturnsFirstElement) {
  openlib::Array<char> array = {'a', 'b', 'c'};
  EXPECT_EQ(array.front(), 'a');
}

TEST(Array, backReturnsLastElement) {
  openlib::Array<char> array = {'a', 'b', 'c'};
  EXPECT_EQ(array.back(), 'c');
}

TEST(Array, dataReturnsPointerToData) {
  openlib::Array<char> array = {1, 2, 3, 4};
  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array.data()[i], i + 1);
  }
}

TEST(Array, rangeBasedForLoop) {
  openlib::Array<int> array = {1, 2, 3, 4};

  int expectedValue = 0;
  for (const auto& value : array) {
    EXPECT_EQ(value, ++expectedValue);
    EXPECT_LE(expectedValue, array.size());
  }

  EXPECT_EQ(expectedValue, array.size());
}

TEST(Array, fill) {
  openlib::Array<int> array = {1, 2, 3, 4};

  array.fill(99);

  for (const auto& value : array) {
    EXPECT_EQ(value, 99);
  }
}

TEST(Array, autoCastToPointer) {
  openlib::Array<int> array = { 1, 2, 3 };
  int *p = array;
  EXPECT_EQ(p, array.data());
  EXPECT_EQ(p[0], 1);
  EXPECT_EQ(p[1], 2);
  EXPECT_EQ(p[2], 3);
}

TEST(Array, operatorEquality) {
  openlib::Array<uint8_t> array = {1, 2, 3, 4};

  EXPECT_TRUE(array == array);
}

TEST(Array, operatorNotEqual) {
  openlib::Array<int> array1 = {1, 2, 3, 4};
  openlib::Array<int> array2 = {1, 2, 3, 4};

  EXPECT_FALSE(array1 == array2);
  EXPECT_TRUE(array1 != array2);
}

TEST(Array, operatorLessThan) {
  openlib::Array<int> array1 = {1, 2, 3, 4};
  openlib::Array<int> array2 = {1, 2, 3, 4};

  if (array1.data() < array2.data()) {
    EXPECT_TRUE(array1 < array2);
  } else {
    EXPECT_TRUE(array2 < array1);
  }
}

TEST(Array, moveConstructor) {
  openlib::Array<char> array1 = {'a', 'b', 'c'};
  openlib::Array<char> array2 = std::move(array1);

  EXPECT_EQ(3, array2.size());
  EXPECT_EQ('a', array2[0]);
  EXPECT_EQ('b', array2[1]);
  EXPECT_EQ('c', array2[2]);
}

TEST(Array, copyConstructor) {
  openlib::Array<char> array1 = {'a', 'b', 'c'};
  openlib::Array<char> array2(array1);

  EXPECT_EQ(array1.size(), array2.size());
  EXPECT_EQ(array1[0], array2[0]);
  EXPECT_EQ(array1[1], array2[1]);
  EXPECT_EQ(array1[2], array2[2]);
}

