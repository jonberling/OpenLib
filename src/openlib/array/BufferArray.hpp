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

#include "Array.hpp"

namespace openlib {

class BufferArray : public Array<uint8_t>
{
public:

  /**
   * @brief construct a BufferArray with size bytes of available space
   * @param size size of buffer, in bytes
   */
  explicit BufferArray(const std::size_t& size);

  /**
   * @brief Get the current offset from the start position
   * @return offset
   */
  virtual std::size_t offset() const;

  /**
   * @brief Remaining space in the BufferArray
   * @return number of bytes remaining
   */
  virtual std::size_t remaining() const;

  /**
   * @brief clear the buffer array
   * All values are set to 0, and the buffer is emptied.
   */
  virtual void clear();

  /**
   * @brief put a char into the buffer
   * @param data data
   */
  virtual void putChar(char data);

  /**
   * @brief get a char from the buffer
   * @return a char
   */
  virtual char getChar();

  /**
   * @brief put a int8_t into the buffer
   * @param data data
   */
  virtual void putInt8(int8_t data);

  /**
   * @brief get a int8_t from the buffer
   * @return a int8_t
   */
  virtual int8_t getInt8();

  /**
   * @brief put a uint8_t into the buffer
   * @param data data
   */
  virtual void putUInt8(uint8_t data);

  /**
   * @brief get a uint8_t from the buffer
   * @return a uint8_t
   */
  virtual uint8_t getUInt8();

  /**
   * @brief put a int16_t into the buffer
   * @param data data
   */
  virtual void putInt16(int16_t data);

  /**
   * @brief get a int16_t from the buffer
   * @return a int16_t
   */
  virtual int16_t getInt16();

  /**
   * @brief put a uint16_t into the buffer
   * @param data data
   */
  virtual void putUInt16(uint16_t data);

  /**
   * @brief get a uint16_t from the buffer
   * @return a uint16_t
   */
  virtual uint16_t getUInt16();

  /**
   * @brief put a int32_t into the buffer
   * @param data data
   */
  virtual void putInt32(int32_t data);

  /**
   * @brief get a int32_t from the buffer
   * @return a int32_t
   */
  virtual int32_t getInt32();

  /**
   * @brief put a uint32_t into the buffer
   * @param data data
   */
  virtual void putUInt32(uint32_t data);

  /**
   * @brief get a uint32_t from the buffer
   * @return a uint32_t
   */
  virtual uint32_t getUInt32();

  /**
   * @brief put a int64_t into the buffer
   * @param data data
   */
  virtual void putInt64(int64_t data);

  /**
   * @brief get a int64_t from the buffer
   * @return a int64_t
   */
  virtual int64_t getInt64();

  /**
   * @brief put a uint64_t into the buffer
   * @param data data
   */
  virtual void putUInt64(uint64_t data);

  /**
   * @brief get a uint64_t from the buffer
   * @return a uint64_t
   */
  virtual uint64_t getUInt64();

  /**
   * @brief put a float into the buffer
   * @param data data
   */
  virtual void putFloat(float data);

  /**
   * @brief get a float from the buffer
   * @return a float
   */
  virtual float getFloat();

  /**
   * @brief put a double into the buffer
   * @param data data
   */
  virtual void putDouble(double data);

  /**
   * @brief get a double from the buffer
   * @return a double
   */
  virtual double getDouble();

  /**
   * @brief put an Array<uint8_t> into the buffer
   * @param data data
   */
  virtual void put(const Array<uint8_t>&data);

  /**
   * @brief get an Array<uint8_t> from the buffer
   * @return an Array<uint8_t>
   */
  virtual void get(Array<uint8_t>&data);

  /**
   * @brief put an uint8_t[] into the buffer
   * @param data data
   */
  virtual void put(const uint8_t* data, std::size_t size);

  /**
   * @brief get an uint8_t[] from the buffer
   * @return an uint8_t[]
   */
  virtual void get(uint8_t* data, std::size_t size);


private:
  uint8_t *position;
};

}
