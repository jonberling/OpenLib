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
#pragma once

#include <string>
#include <openlib/Array.h>

namespace openlib {

class Serializer
{
public:

  static const std::size_t MAX_STRING_LENGTH;

  /**
   * @breif construct a Serializer with size bytes of available storage
   * @param capacity max bytes available to serialize
   */
  explicit Serializer(const std::size_t& capacity);

  /**
   * @brief get the current size, in bytes
   * @return size, in bytes
   */
  virtual std::size_t size() const;

  /** 
   * @brief get the total capacity, in bytes
   * @return capacity, in bytes
   */
  virtual std::size_t capacity() const;

  /**
   * @brief get the remaining capacity, in bytes
   * @return remaining capacity, in bytes
   */
  virtual std::size_t remaining() const;

  /**
   * @brief put a char into the buffer
   * @param data data
   */
  virtual void putChar(char data);

  /**
   * @brief put a int8_t into the buffer
   * @param data data
   */
  virtual void putInt8(int8_t data);

  /**
   * @brief put a uint8_t into the buffer
   * @param data data
   */
  virtual void putUInt8(uint8_t data);

  /**
   * @brief put a int16_t into the buffer
   * @param data data
   */
  virtual void putInt16(int16_t data);

  /**
   * @brief put a uint16_t into the buffer
   * @param data data
   */
  virtual void putUInt16(uint16_t data);

  /**
   * @brief put a int32_t into the buffer
   * @param data data
   */
  virtual void putInt32(int32_t data);

  /**
   * @brief put a uint32_t into the buffer
   * @param data data
   */
  virtual void putUInt32(uint32_t data);

  /**
   * @brief put a int64_t into the buffer
   * @param data data
   */
  virtual void putInt64(int64_t data);

  /**
   * @brief put a uint64_t into the buffer
   * @param data data
   */
  virtual void putUInt64(uint64_t data);

  /**
   * @brief put a float into the buffer
   * @param data data
   *
   * Assumes an IEEE 754 compliant machine.
   * See: https://en.wikipedia.org/wiki/IEEE_75
   */
  virtual void putFloat(float data);

  /**
   * @brief put a double into the buffer
   * @param data data
   *
   * Assumes an IEEE 754 compliant machine.
   * See: https://en.wikipedia.org/wiki/IEEE_75
   */
  virtual void putDouble(double data);

  /**
   * @brief put a std::string into the buffer
   * @param data data
   * 
   * String will be packaged as an uint16_t length, followed b
   * a character array. Assumes string is UTF-
   * See: https://en.wikipedia.org/wiki/UTF-
   */
  virtual void putString(const std::string& data);

	/**
	 * @brief put an void* into the buffer
	 * @param data data
	 */
	virtual void put(const void* data, std::size_t size);

	/**
	 * @brief get the raw buffer
	 * @return pointer to the buffer
	 */
	virtual uint8_t* data() const;

private:

  Array<uint8_t> buffer;
  uint8_t *position;
};

} // namespace openlib
