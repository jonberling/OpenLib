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

#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <sstream>
#include <initializer_list>
#include <type_traits>

namespace openlib {

/**
 * Array data structure
 *
 * Elements are guaranteed to stay in the same location in memory.
 */
template <class type>
class Array {
public:

  /**
   * @brief constructor
   * Array will be zero initialized.
   * @param size size of array
   */
  explicit Array(const std::size_t& size);

  /**
   * @brief constructor
   * Array will be initialized based off of list. Array will be the size of
   * list.
   * @param list an initializer list
   */
  Array(const std::initializer_list<type>& list);

  /**
   * @brief move constructor
   * Array will be initialized based off of the other array. This is a
   * destructive move constructor, the old Array object will no longer be
   * valid.
   */
  Array(Array&& other);

  /**
   * @brief destructor
   */
  virtual ~Array();

  /**
   * @brief Number of elements in the array
   * @return the number of elements in the array
   */
  virtual std::size_t size() const;

  /**
   * @brief Access element at a given position
   * @return a reference to the element at the given position
   */
  virtual type& at(const std::size_t& position) const;

  /**
   * @brief The first element
   * @return a reference to the first element
   */
  virtual type& front() const;

  /**
   * @brief The last element
   * @return a reference to the last element
   */
  virtual type& back() const;

  /**
   * @brief Returns a pointer to the underlying array
   * @returns a pointer to the underlying array
   */
  virtual type* data() const;

  /**
   * @brief Get a pointer to the first element
   * @return a pointer to the first element
   */
  virtual type* begin() const;

  /**
   * @brief Get a pointer to one past the last element
   * @return a pointer to one past the last element
   */
  virtual type* end() const;

  /**
   * @brief fill each element of the array with the same value
   * @param value a value to fill the array with
   */
  virtual void fill(const type& value);

  /**
   * @brief clear the array, setting all values to 0
   */
  virtual void clear();

  /**
   * @brief display this array as a string
   * @return a std::string containing information about this array
   */
  virtual std::string str() const;

  /**
   * @brief auto cast to pointer to base type
   */
  virtual operator type*() const;

private:
  type *buffer;
  std::size_t bufferSize;

  Array(const Array&) = delete;
  Array& operator=(const Array&) = delete;
};

/*
 * Forward declare explicit templated methods
 */

template<>
std::string openlib::Array<char>::str() const;

template<>
std::string openlib::Array<uint8_t>::str() const;

template<>
std::string openlib::Array<int>::str() const;

}

template <class type>
openlib::Array<type>::Array(const std::size_t& size):
    buffer(new type[size]),
    bufferSize(size) {

  if (std::is_pod<type>::value) {
    // zero initialize POD types
    clear();
  }
}

template <class type>
openlib::Array<type>::Array(const std::initializer_list<type>& list):
    buffer(new type[list.size()]),
    bufferSize(list.size()) {
  std::memcpy(buffer, list.begin(), bufferSize * sizeof(type));
}

template <class type>
openlib::Array<type>::Array(openlib::Array<type>&& other):
    buffer(other.buffer),
    bufferSize(other.bufferSize) {
  other.buffer = nullptr;
  other.bufferSize = 0;
}

template <class type>
openlib::Array<type>::~Array() {
  delete[] buffer;
}

template <class type>
std::size_t openlib::Array<type>::size() const {
  return bufferSize;
}

template <class type>
type& openlib::Array<type>::at(const std::size_t& position) const {
  return buffer[position];
}

template <class type>
type& openlib::Array<type>::front() const {
  return buffer[0];
}

template <class type>
type& openlib::Array<type>::back() const {
  return buffer[bufferSize - 1];
}

template <class type>
type* openlib::Array<type>::data() const {
  return buffer;
}

template <class type>
type* openlib::Array<type>::begin() const {
  return buffer;
}

template <class type>
type* openlib::Array<type>::end() const {
  return buffer + bufferSize;
}

template <class type>
void openlib::Array<type>::fill(const type& value) {
  for (std::size_t i = 0; i < bufferSize; i++) {
    buffer[i] = value;
  }
}

template <class type>
void openlib::Array<type>::clear() {
  memset(buffer, 0, sizeof(type) * bufferSize);
}

template <class type>
std::string openlib::Array<type>::str() const {
  char output[64];
  sprintf(output, "Array: data @ %p", buffer);
  return std::string(output);
}

template <class type>
openlib::Array<type>::operator type*() const {
  return data();
}

/**
 * @brief equality
 * Determined by looking at the location of the underling data's memory location
 */
template <class type>
inline bool operator==(const openlib::Array<type> &lhs, const openlib::Array<type> &rhs) {
  return lhs.data() == rhs.data();
}

/**
 * @brief inequality
 * Determined by looking at the location of the underling data's memory location
 */
template <class type>
inline bool operator!=(const openlib::Array<type> &lhs, const openlib::Array<type> &rhs) {
  return lhs.data() != rhs.data();
}

/**
 * @brief less than
 * Determined by looking at the location of the underling data's memory location
 */
template <class type>
inline bool operator<(const openlib::Array<type> &lhs, const openlib::Array<type> &rhs) {
  return lhs.data() < rhs.data();
}
