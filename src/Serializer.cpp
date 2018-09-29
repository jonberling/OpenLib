/****************************************************************************
Copyright (c) 2016, 2018 OpenLib Proje
All rights reserved.

Redistribution and use in source and binary forms, with or witho
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, th
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentati
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, T
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE A
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIAB
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTI
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEV
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE U
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/

#include <cstdint>
#include <cstring>

#include "openlib/Serializer.h"


const std::size_t openlib::Serializer::MAX_STRING_LENGTH = UINT16_MAX;

openlib::Serializer::Serializer(const std::size_t& capacity):
    buffer(capacity), position(buffer.data()){

}

std::size_t openlib::Serializer::size() const {
  return position - data();
}

std::size_t openlib::Serializer::capacity() const {
  return buffer.size();
}

std::size_t openlib::Serializer::remaining() const {
  return capacity() - size();
}

void openlib::Serializer::putChar(char data) {
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putInt8(int8_t data) {
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putUInt8(uint8_t data) {
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putInt16(int16_t data) {
  data = htobe16(data);
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putUInt16(uint16_t data) {
  data = htobe16(data);
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putInt32(int32_t data) {
  data = htobe32(data);
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putUInt32(uint32_t data) {
  data = htobe32(data);
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putInt64(int64_t data) {
  data = htobe64(data);
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putUInt64(uint64_t data) {
  data = htobe64(data);
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putFloat(float data) {
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putDouble(double data) {
  put(reinterpret_cast<const uint8_t*>(&data), sizeof(data));
}

void openlib::Serializer::putString(const std::string& data) {
  if (Serializer::MAX_STRING_LENGTH < data.length()) {
    throw std::length_error("string cannot exceed MAX_STRING_LENGTH");
  }

  putUInt16(data.length());
  put(reinterpret_cast<const uint8_t*>(data.c_str()), data.length());
}

void openlib::Serializer::put(const void* data, std::size_t size) {
  if (remaining() < size) {
    throw std::length_error("not enough capacity left in Serializer");
  }

  std::memcpy(position, data, size);
  position += size;
}

uint8_t* openlib::Serializer::data() const {
  return buffer.data();
}

