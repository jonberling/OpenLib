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
#include <endian.h>

#include <stdexcept>

#include "BufferArray.hpp"

using namespace openlib;

BufferArray::BufferArray(const std::size_t& size):
    Array<uint8_t>(size) {
  position = data();
}

std::size_t BufferArray::offset() const {
  return position - data();
}

std::size_t BufferArray::remaining() const {
  return size() - offset();
}

void BufferArray::clear() {
  Array<uint8_t>::clear();
  position = data();
}

void BufferArray::putChar(char data) {
  put((uint8_t*)(&data), sizeof(data));
}

char BufferArray::getChar() {
  char data;
  get((uint8_t*)(&data), sizeof(data));
  return data;
}

void BufferArray::putInt8(int8_t data) {
  put((uint8_t*)(&data), sizeof(data));
}

int8_t BufferArray::getInt8() {
  int8_t data;
  get((uint8_t*)(&data), sizeof(data));
  return data;
}

void BufferArray::putUInt8(uint8_t data) {
  put((uint8_t*)(&data), sizeof(data));
}

uint8_t BufferArray::getUInt8() {
  uint8_t data;
  get((uint8_t*)(&data), sizeof(data));
  return data;
}

void BufferArray::putInt16(int16_t data) {
  data = htobe16(data);
  put((uint8_t*)(&data), sizeof(data));
}

int16_t BufferArray::getInt16() {
  int16_t data;
  get((uint8_t*)(&data), sizeof(data));
  return be16toh(data);
}

void BufferArray::putUInt16(uint16_t data) {
  data = htobe16(data);
  put((uint8_t*)(&data), sizeof(data));
}

uint16_t BufferArray::getUInt16() {
  uint16_t data;
  get((uint8_t*)(&data), sizeof(data));
  return be16toh(data);
}

void BufferArray::putInt32(int32_t data) {
  data = htobe32(data);
  put((uint8_t*)(&data), sizeof(data));
}

int32_t BufferArray::getInt32() {
  int32_t data;
  get((uint8_t*)(&data), sizeof(data));
  return be32toh(data);
}

void BufferArray::putUInt32(uint32_t data) {
  data = htobe32(data);
  put((uint8_t*)(&data), sizeof(data));
}

uint32_t BufferArray::getUInt32() {
  uint32_t data;
  get((uint8_t*)(&data), sizeof(data));
  return be32toh(data);
}

void BufferArray::putInt64(int64_t data) {
  data = htobe64(data);
  put((uint8_t*)(&data), sizeof(data));
}

int64_t BufferArray::getInt64() {
  int64_t data;
  get((uint8_t*)(&data), sizeof(data));
  return be64toh(data);
}

void BufferArray::putUInt64(uint64_t data) {
  data = htobe64(data);
  put((uint8_t*)(&data), sizeof(data));
}

uint64_t BufferArray::getUInt64() {
  uint64_t data;
  get((uint8_t*)(&data), sizeof(data));
  return be64toh(data);
}

void BufferArray::putFloat(float data) {
  if (sizeof(float) != sizeof(uint32_t)) throw std::runtime_error("sizeof(float) returned unexpected size");
  union FloatBytes {
    float f;
    uint32_t i;
  };

  FloatBytes bytes = { data };
  bytes.i = htobe32(bytes.i);
  put((uint8_t*)(&bytes.i), sizeof(bytes.i));
}

float BufferArray::getFloat() {
  if (sizeof(float) != sizeof(uint32_t)) throw std::runtime_error("sizeof(float) returned unexpected size");

  union FloatBytes {
    float f;
    uint32_t i;
  };

  float data;
  get((uint8_t*)(&data), sizeof(data));

  FloatBytes bytes = { data };
  bytes.i = be32toh(bytes.i);
  return bytes.f;
}

void BufferArray::putDouble(double data) {
  if (sizeof(double) != sizeof(uint64_t)) throw std::runtime_error("sizeof(double) returned unexpected size");

  union DoubleBytes {
    double d;
    uint64_t i;
  };

  DoubleBytes bytes = { data };
  bytes.i = htobe64(bytes.i);
  put((uint8_t*)(&bytes.i), sizeof(bytes.i));
}

double BufferArray::getDouble() {
  if (sizeof(double) != sizeof(uint64_t)) throw std::runtime_error("sizeof(double) returned unexpected size");

  union DoubleBytes {
    double d;
    uint64_t i;
  };

  double data;
  get((uint8_t*)(&data), sizeof(data));

  DoubleBytes bytes = { data };
  bytes.i = be64toh(bytes.i);
  return bytes.d;
}

void BufferArray::put(const Array<uint8_t>& data) {
  put(data.data(), data.size() * sizeof(uint8_t));
}

void BufferArray::get(Array<uint8_t>& data) {
  get(data.data(), data.size() * sizeof(uint8_t));
}

void BufferArray::put(const uint8_t* data, std::size_t size) {
  if (remaining() < size) { throw std::length_error("not enough space left in BufferArray"); }
  std::memcpy(position, data, size);
  position += size;
}

void BufferArray::get(uint8_t* data, std::size_t size) {
  if (offset() < size) { throw std::length_error("not enough data left in BufferArray"); }
  position -= size;
  std::memcpy(data, position, size);
}
