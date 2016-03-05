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

#include <memory>

#include <gtest/gtest.h>

#include <openlib/array.hpp>

TEST(Array, isConstructable) {
  openlib::Array<int> array(0);
  // if the test gets this far it passes
}

TEST(Array, isConstructableViaInitList) {
  openlib::Array<int> array = {1, 2, 3};
  // if the test gets this far it passes
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

TEST(Array, isZeroInitializedForPod) {
  openlib::Array<char> array(3);

  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array.at(i), '\0');
  }
}

TEST(Array, isNotZeroInitializedForNonPod) {
  struct NotPod {
    int canary;
    NotPod(): canary(-1) {}
  };

  openlib::Array<NotPod> array(3);

  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_NE(array.at(i).canary, 0);
  }
}

TEST(Array, operatorBracketReturnCorrectValue) {
  openlib::Array<int> array = {1, 2, 3, 4};

  for (std::size_t i = 0; i < array.size(); i++) {
    EXPECT_EQ(array[i], i + 1);
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

TEST(Array, clear) {
  openlib::Array<int> array = {1, 2, 3, 4};

  array.clear();

  for (const auto& value : array) {
    EXPECT_EQ(value, 0);
  }
}

TEST(Array, strChar) {
  openlib::Array<char> array = { 'a', 'b', 'c' };
  EXPECT_EQ(array.str(), "Array: a b c");
}

TEST(Array, strByte) {
  openlib::Array<uint8_t> array = { 1, 2, 3 };
  EXPECT_EQ(array.str(), "Array: 0x01 0x02 0x03");
}

TEST(Array, strInt) {
  openlib::Array<int> array = { 1, 2, 3 };
  EXPECT_EQ(array.str(), "Array: 1 2 3");
}

TEST(Array, strDouble) {
  openlib::Array<double> array = { 1.1, 2.2, 3.3 };
  EXPECT_EQ(array.str().substr(0, 14), "Array: data @ ");
}

TEST(Array, strString) {
  openlib::Array<std::string> array(1);
  array[0] = "test";
  EXPECT_FALSE(array.str().empty());
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

TEST(BufferArray, isConstructable) {
  openlib::BufferArray buffer(0);
  // if this test compiles it passes
}

TEST(BufferArray, offsetInitalized) {
  openlib::BufferArray buffer(0);

  EXPECT_EQ(buffer.offset(), 0);
}

TEST(BufferArray, remainderInitialized) {
  openlib::BufferArray buffer(10);

  EXPECT_EQ(buffer.remaining(), 10);
}

TEST(BufferArray, putRawArray) {
  openlib::BufferArray buffer(10);

  uint8_t rawArray[] = { 4, 3, 2, 1 };
  buffer.put(rawArray, sizeof(rawArray));

  EXPECT_EQ(memcmp(rawArray, buffer.data(), sizeof(rawArray)), 0);
}

TEST(BufferArray, putIncreasesOffset) {
  openlib::BufferArray buffer(10);

  uint8_t rawArray[] = { 4, 3, 2, 1 };
  buffer.put(rawArray, sizeof(rawArray));

  EXPECT_EQ(buffer.offset(), sizeof(rawArray));
}

TEST(BufferArray, putDecreasesRemaining) {
  openlib::BufferArray buffer(10);

  uint8_t rawArray[] = { 4, 3, 2, 1 };
  buffer.put(rawArray, sizeof(rawArray));

  EXPECT_EQ(buffer.remaining(), buffer.size() - sizeof(rawArray));
}

TEST(BufferArray, putSequentialRawArray) {
  openlib::BufferArray buffer(10);

  uint8_t rawArray1[] = { 4, 3, 2, 1 };
  uint8_t rawArray2[] = { 8, 7, 5, 4 };
  buffer.put(rawArray1, sizeof(rawArray1));
  buffer.put(rawArray2, sizeof(rawArray2));

  EXPECT_EQ(memcmp(rawArray2, buffer.data() + sizeof(rawArray1), sizeof(rawArray2)), 0);
}

TEST(BufferArray, putThrowsWhenOutOfRange) {
  openlib::BufferArray buffer(6);

  uint8_t rawArray1[] = { 4, 3, 2, 1 };
  uint8_t rawArray2[] = { 8, 7, 5, 4 };
  buffer.put(rawArray1, sizeof(rawArray1));
  try {
    buffer.put(rawArray2, sizeof(rawArray2));
    FAIL() << "expected exception to be thrown";
  } catch(std::length_error const& err) {
    EXPECT_EQ(err.what(), std::string("not enough space left in BufferArray"));
  } catch(...) {
    FAIL() << "expected std::out_of_range";
  }
}

TEST(BufferArray, putChar) {
  openlib::BufferArray buffer(10);

  char value = 0xff;
  buffer.putChar(value);
  EXPECT_EQ(*((char*)(buffer.data())), value);
}

TEST(BufferArray, putInt8) {
  openlib::BufferArray buffer(10);

  int8_t value = 0xff;
  buffer.putInt8(value);
  EXPECT_EQ(*((int8_t*)(buffer.data())), value);
}

TEST(BufferArray, putUint8) {
  openlib::BufferArray buffer(10);

  uint8_t value = 0xff;
  buffer.putUInt8(value);
  EXPECT_EQ(*((uint8_t*)(buffer.data())), value);
}

TEST(BufferArray, putInt16) {
  openlib::BufferArray buffer(10);

  int16_t value = 0x0102;
  buffer.putInt16(value);

  EXPECT_EQ(buffer.data()[0], 0x01);
  EXPECT_EQ(buffer.data()[1], 0x02);
}

TEST(BufferArray, putUint16) {
  openlib::BufferArray buffer(10);

  uint16_t value = 0x0102;
  buffer.putUInt16(value);

  EXPECT_EQ(buffer.data()[0], 0x01);
  EXPECT_EQ(buffer.data()[1], 0x02);
}

TEST(BufferArray, putInt32) {
  openlib::BufferArray buffer(10);

  int32_t value = 0x01020304;
  buffer.putInt32(value);

  EXPECT_EQ(buffer.data()[0], 0x01);
  EXPECT_EQ(buffer.data()[1], 0x02);
  EXPECT_EQ(buffer.data()[2], 0x03);
  EXPECT_EQ(buffer.data()[3], 0x04);
}

TEST(BufferArray, putUint32) {
  openlib::BufferArray buffer(10);

  int32_t value = 0x01020304;
  buffer.putUInt32(value);

  EXPECT_EQ(buffer.data()[0], 0x01);
  EXPECT_EQ(buffer.data()[1], 0x02);
  EXPECT_EQ(buffer.data()[2], 0x03);
  EXPECT_EQ(buffer.data()[3], 0x04);
}

TEST(BufferArray, putInt64) {
  openlib::BufferArray buffer(10);

  int64_t value = 0x0102030405060708;
  buffer.putInt64(value);

  EXPECT_EQ(buffer.data()[0], 0x01);
  EXPECT_EQ(buffer.data()[1], 0x02);
  EXPECT_EQ(buffer.data()[2], 0x03);
  EXPECT_EQ(buffer.data()[3], 0x04);
  EXPECT_EQ(buffer.data()[4], 0x05);
  EXPECT_EQ(buffer.data()[5], 0x06);
  EXPECT_EQ(buffer.data()[6], 0x07);
  EXPECT_EQ(buffer.data()[7], 0x08);
}

TEST(BufferArray, putUint64) {
  openlib::BufferArray buffer(10);

  uint64_t value = 0x0102030405060708;
  buffer.putUInt64(value);

  EXPECT_EQ(buffer.data()[0], 0x01);
  EXPECT_EQ(buffer.data()[1], 0x02);
  EXPECT_EQ(buffer.data()[2], 0x03);
  EXPECT_EQ(buffer.data()[3], 0x04);
  EXPECT_EQ(buffer.data()[4], 0x05);
  EXPECT_EQ(buffer.data()[5], 0x06);
  EXPECT_EQ(buffer.data()[6], 0x07);
  EXPECT_EQ(buffer.data()[7], 0x08);
}

TEST(BufferArray, putArray) {
  openlib::BufferArray buffer(10);

  openlib::Array<uint8_t> array = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(array);

  EXPECT_EQ(buffer.data()[0], 0x01);
  EXPECT_EQ(buffer.data()[1], 0x02);
  EXPECT_EQ(buffer.data()[2], 0x03);
  EXPECT_EQ(buffer.data()[3], 0x04);
  EXPECT_EQ(buffer.data()[4], 0x05);
  EXPECT_EQ(buffer.data()[5], 0x06);
  EXPECT_EQ(buffer.data()[6], 0x07);
  EXPECT_EQ(buffer.data()[7], 0x08);
}

TEST(BufferArray, getRawArray) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> initValues = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(initValues);

  uint8_t array[8] = { 0 };
  buffer.get(array, sizeof(array));
  EXPECT_EQ(memcmp(array, buffer.data(), sizeof(array)), 0);
}

TEST(BufferArray, getDecreasesOffset) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> initValues = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(initValues);

  uint8_t array[8] = { 0 };
  buffer.get(array, sizeof(array));
  EXPECT_EQ(buffer.offset(), 0);
}

TEST(BufferArray, getIncreasesRemaining) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> initValues = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(initValues);

  uint8_t array[8] = { 0 };
  buffer.get(array, sizeof(array));
  EXPECT_EQ(buffer.remaining(), 10);
}

TEST(BufferArray, getSequentialRawArray) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> initValues = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(initValues);

  uint8_t array1[4] = { 0 };
  uint8_t array2[4] = { 0 };

  buffer.get(array2, sizeof(array2));
  buffer.get(array1, sizeof(array1));

  EXPECT_EQ(memcmp(array2, buffer.data() + sizeof(array1), sizeof(array2)), 0);
}

TEST(BufferArray, getThrowsWhenOutOfRange) {
  openlib::BufferArray buffer(6);
  uint8_t array[8] = { 0 };

  try {
    buffer.get(array, sizeof(array));
    FAIL() << "expected exception to be thrown";
  } catch(std::length_error const& err) {
    EXPECT_EQ(err.what(), std::string("not enough data left in BufferArray"));
  } catch(...) {
    FAIL() << "expected std::out_of_range";
  }
}

TEST(BufferArray, getChar) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01 };
  buffer.put(init);

  char value = 0;
  value = buffer.getChar();
  EXPECT_EQ(value, 0x01);
}

TEST(BufferArray, getInt8) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01 };
  buffer.put(init);

  int8_t value = 0;
  value = buffer.getInt8();
  EXPECT_EQ(value, 0x01);
}

TEST(BufferArray, getUint8) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01 };
  buffer.put(init);

  uint8_t value = 0;
  value = buffer.getUInt8();
  EXPECT_EQ(value, 0x01);
}

TEST(BufferArray, getInt16) {
   openlib::BufferArray buffer(10);
   openlib::Array<uint8_t> init = { 0x01, 0x02 };
   buffer.put(init);

   int16_t value = 0;
   value = buffer.getInt16();
   EXPECT_EQ(value, 0x0102);
}

TEST(BufferArray, getUInt16) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01, 0x02 };
  buffer.put(init);

  uint16_t value = 0;
  value = buffer.getUInt16();
  EXPECT_EQ(value, 0x0102);
}

TEST(BufferArray, getInt32) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01, 0x02, 0x03, 0x04 };
  buffer.put(init);

  int32_t value = 0;
  value = buffer.getInt32();
  EXPECT_EQ(value, 0x01020304);
}

TEST(BufferArray, getUInt32) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01, 0x02, 0x03, 0x04 };
  buffer.put(init);

  uint32_t value = 0;
  value = buffer.getUInt32();
  EXPECT_EQ(value, 0x01020304);
}

TEST(BufferArray, getInt64) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(init);

  int64_t value = 0;
  value = buffer.getInt64();
  EXPECT_EQ(value, 0x0102030405060708);
}

TEST(BufferArray, getUInt64) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(init);

  uint64_t value = 0;
  value = buffer.getUInt64();
  EXPECT_EQ(value, 0x0102030405060708);
}

TEST(BufferArray, getArray) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.put(init);

  openlib::Array<uint8_t> value(8);
  buffer.get(value);
  EXPECT_EQ(memcmp(value.data(), init.data(), value.size()), 0);
}

TEST(BufferArray, putGetFloat) {
  openlib::BufferArray buffer(10);

  float put = 1234.5678;
  buffer.putFloat(put);
  float get = buffer.getFloat();
  EXPECT_EQ(put, get);
}

TEST(BufferArray, putGetDouble) {
  openlib::BufferArray buffer(10);

  double put = 1234.5678;
  buffer.putDouble(put);
  double get = buffer.getDouble();
  EXPECT_EQ(put, get);
}

TEST(BufferArray, clear) {
  openlib::BufferArray buffer(10);
  openlib::Array<uint8_t> init = { 0x01, 0x02, 0x03, 0x04 };
  buffer.put(init);

  buffer.clear();
  EXPECT_EQ(buffer.offset(), 0);
  EXPECT_EQ(buffer.remaining(), 10);
}
