/****************************************************************************
Copyright (c) 2016, 2018 OpenLib Projec
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

#include <cstdint>

#include <gtest/gtest.h>

#include <openlib/Serializer.h>

TEST(Serializer, isConstructable) {
  openlib::Serializer serializer(0);
  // if this test compiles it passe
}

TEST(Serializer, sizeInitalized) {
  openlib::Serializer serializer(1);

  EXPECT_EQ(serializer.size(), 0);
}

TEST(Serializer, capacitySetCorrectly) {
  openlib::Serializer serializer(1);

  EXPECT_EQ(serializer.capacity(), 1);
}

TEST(Serializer, remainderInitialized) {
  openlib::Serializer serializer(10);

  EXPECT_EQ(serializer.remaining(), 10);
}

TEST(Serializer, putRawArray) {
  openlib::Serializer serializer(10);

  uint8_t rawArray[] = { 4, 3, 2, 1 };
  serializer.put(rawArray, sizeof(rawArray));

  EXPECT_EQ(memcmp(rawArray, serializer.data(), sizeof(rawArray)), 0);
}

TEST(Serializer, putIncreasesSize) {
  openlib::Serializer serializer(10);

  uint8_t rawArray[] = { 4, 3, 2, 1 };
  serializer.put(rawArray, sizeof(rawArray));

  EXPECT_EQ(serializer.size(), sizeof(rawArray));
}

TEST(Serializer, putDecreasesRemaining) {
  openlib::Serializer serializer(10);

  uint8_t rawArray[] = { 4, 3, 2, 1 };
  serializer.put(rawArray, sizeof(rawArray));

  EXPECT_EQ(serializer.remaining(), serializer.capacity() - sizeof(rawArray));
}

TEST(Serializer, putSequentialRawArray) {
  openlib::Serializer serializer(10);

  uint8_t rawArray1[] = { 4, 3, 2, 1 };
  uint8_t rawArray2[] = { 8, 7, 5, 4 };
  serializer.put(rawArray1, sizeof(rawArray1));
  serializer.put(rawArray2, sizeof(rawArray2));

  EXPECT_EQ(memcmp(rawArray2, serializer.data() + sizeof(rawArray1), sizeof(rawArray2)), 0);
}

TEST(Serializer, putThrowsWhenOutOfCapacity) {
  openlib::Serializer serializer(6);

  uint8_t rawArray1[] = { 4, 3, 2, 1 };
  uint8_t rawArray2[] = { 8, 7, 5, 4 };
  serializer.put(rawArray1, sizeof(rawArray1));
  try {
    serializer.put(rawArray2, sizeof(rawArray2));
    FAIL() << "expected exception to be thrown";
  } catch(std::length_error const& err) {
    EXPECT_EQ(err.what(), std::string("not enough capacity left in Serializer"));
  } catch(...) {
    FAIL() << "expected std::length_error";
  }
}

TEST(Serializer, putChar) {
  openlib::Serializer serializer(10);

  char value = 0xff;
  serializer.putChar(value);
  EXPECT_EQ(*((char*)(serializer.data())), value);
}

TEST(Serializer, putInt8) {
  openlib::Serializer serializer(10);

  int8_t value = 0xff;
  serializer.putInt8(value);
  EXPECT_EQ(*((int8_t*)(serializer.data())), value);
}

TEST(Serializer, putUint8) {
  openlib::Serializer serializer(10);

  uint8_t value = 0xff;
  serializer.putUInt8(value);
  EXPECT_EQ(*((uint8_t*)(serializer.data())), value);
}

TEST(Serializer, putInt16) {
  openlib::Serializer serializer(10);

  int16_t value = 0x0102;
  serializer.putInt16(value);

  EXPECT_EQ(serializer.data()[0], 0x01);
  EXPECT_EQ(serializer.data()[1], 0x02);
}

TEST(Serializer, putUint16) {
  openlib::Serializer serializer(10);

  uint16_t value = 0x0102;
  serializer.putUInt16(value);

  EXPECT_EQ(serializer.data()[0], 0x01);
  EXPECT_EQ(serializer.data()[1], 0x02);
}

TEST(Serializer, putInt32) {
  openlib::Serializer serializer(10);

  int32_t value = 0x01020304;
  serializer.putInt32(value);

  EXPECT_EQ(serializer.data()[0], 0x01);
  EXPECT_EQ(serializer.data()[1], 0x02);
  EXPECT_EQ(serializer.data()[2], 0x03);
  EXPECT_EQ(serializer.data()[3], 0x04);
}

TEST(Serializer, putUint32) {
  openlib::Serializer serializer(10);

  int32_t value = 0x01020304;
  serializer.putUInt32(value);

  EXPECT_EQ(serializer.data()[0], 0x01);
  EXPECT_EQ(serializer.data()[1], 0x02);
  EXPECT_EQ(serializer.data()[2], 0x03);
  EXPECT_EQ(serializer.data()[3], 0x04);
}

TEST(Serializer, putInt64) {
  openlib::Serializer serializer(10);

  int64_t value = 0x0102030405060708;
  serializer.putInt64(value);

  EXPECT_EQ(serializer.data()[0], 0x01);
  EXPECT_EQ(serializer.data()[1], 0x02);
  EXPECT_EQ(serializer.data()[2], 0x03);
  EXPECT_EQ(serializer.data()[3], 0x04);
  EXPECT_EQ(serializer.data()[4], 0x05);
  EXPECT_EQ(serializer.data()[5], 0x06);
  EXPECT_EQ(serializer.data()[6], 0x07);
  EXPECT_EQ(serializer.data()[7], 0x08);
}

TEST(Serializer, putUint64) {
  openlib::Serializer serializer(10);

  uint64_t value = 0x0102030405060708;
  serializer.putUInt64(value);

  EXPECT_EQ(serializer.data()[0], 0x01);
  EXPECT_EQ(serializer.data()[1], 0x02);
  EXPECT_EQ(serializer.data()[2], 0x03);
  EXPECT_EQ(serializer.data()[3], 0x04);
  EXPECT_EQ(serializer.data()[4], 0x05);
  EXPECT_EQ(serializer.data()[5], 0x06);
  EXPECT_EQ(serializer.data()[6], 0x07);
  EXPECT_EQ(serializer.data()[7], 0x08);
}

TEST(Serializer, putFloat) {
  openlib::Serializer serializer(sizeof(float));

  float value = 0.5;
  serializer.putFloat(value);

  EXPECT_EQ(*reinterpret_cast<float*>(serializer.data()), value);
}

TEST(Serializer, putDouble) {
  openlib::Serializer serializer(sizeof(double));

  double value = 0.5;
  serializer.putDouble(value);

  EXPECT_EQ(*reinterpret_cast<double*>(serializer.data()), value);
}

TEST(Serializer, putString) {
  openlib::Serializer serializer(16);

  std::string str = "hello";

  serializer.putString(str);

  EXPECT_EQ(serializer.data()[0], 0x00);
  EXPECT_EQ(serializer.data()[1], 0x05);
  EXPECT_EQ(serializer.data()[2], 'h');
  EXPECT_EQ(serializer.data()[3], 'e');
  EXPECT_EQ(serializer.data()[4], 'l');
  EXPECT_EQ(serializer.data()[5], 'l');
  EXPECT_EQ(serializer.data()[6], 'o');
}

TEST(Serializer, putTooLongStringThrows) {
  openlib::Serializer serializer(16);

  // create a string bigger than the max allowe
  std::string str(openlib::Serializer::MAX_STRING_LENGTH + 1, 'x');

  try {
    serializer.putString(str);
    FAIL() << "expected exception to be thrown";
  } catch(std::length_error const& err) {
    EXPECT_EQ(err.what(), std::string("string cannot exceed MAX_STRING_LENGTH"));
  } catch(...) {
    FAIL() << "expected std::out_of_range";
  }
}

