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

#include <memory>
#include <initializer_list>

namespace openlib {

/**
 * Dynamically allocated array data structure
 *
 * Elements are guaranteed to stay in the same location in memory.
 */
template <class type>
class Array {
public:

  /**
   * @brief constructor
   * @param size size of array
   */
  explicit Array(const std::size_t& size);

  /**
   * @brief constructor
   * Array will be initialized based off of the list.
   * Array will be the size of the list.
   * @param list an initializer list
   */
  Array(const std::initializer_list<type>& list);

  /**
   * @brief copy constructor
   * Array will be initialized based off the other array. Values will
   * be copied.
   */
  Array(const Array& other);

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
  virtual type& at(const std::size_t& position);

  /**
   * @brief Access const element at a given position
   * @return a const reference to the element at the given position
   */
  virtual const type& at(const std::size_t& position) const;

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
   * @brief auto cast to pointer to base type
   */
  virtual operator type*() const;

  /**
   * @brief operator[]
   */
  virtual type& operator[](std::size_t position);

  /**
   * @brief operator[] const
   */
  virtual const type& operator[](std::size_t position) const;

private:
  std::unique_ptr<type[]> buffer;
  const std::size_t bufferSize;
  
  // no assignment operator
  Array& operator=(const Array& other) = delete;
};

} // namespace openlib

///////////////////////////////////////////////////////////////////////////////
// Definition complete, implemention below
///////////////////////////////////////////////////////////////////////////////

template <class type>
openlib::Array<type>::Array(const std::size_t& size):
    buffer(std::make_unique<type[]>(size)),
    bufferSize(size) {

  // no action needed
}

template <class type>
openlib::Array<type>::Array(const std::initializer_list<type>& list):
    buffer(std::make_unique<type[]>(list.size())),
    bufferSize(list.size()) {

  std::size_t i = 0;
  for (const auto& e : list) {
    buffer[i++] = e;
  }
}

template <class type>
openlib::Array<type>::Array(const openlib::Array<type>& other):
    buffer(std::make_unique<type[]>(other.bufferSize)),
    bufferSize(other.bufferSize) {

  std::size_t i = 0;
  for (const auto& e : other) {
    buffer[i++] = e;
  }
}

template <class type>
openlib::Array<type>::Array(openlib::Array<type>&& other):
    buffer(nullptr),
    bufferSize(other.bufferSize) {
  buffer.swap(other.buffer);
}

template <class type>
openlib::Array<type>::~Array() {
  // no action needed
}

template <class type>
std::size_t openlib::Array<type>::size() const {
  return bufferSize;
}

template <class type>
type& openlib::Array<type>::at(const std::size_t& position) {
  return buffer.get()[position];
}

template <class type>
const type& openlib::Array<type>::at(const std::size_t& position) const {
  return buffer.get()[position];
}

template <class type>
type& openlib::Array<type>::front() const {
  return buffer.get()[0];
}

template <class type>
type& openlib::Array<type>::back() const {
  return buffer.get()[bufferSize - 1];
}

template <class type>
type* openlib::Array<type>::data() const {
  return buffer.get();
}

template <class type>
type* openlib::Array<type>::begin() const {
  return buffer.get();
}

template <class type>
type* openlib::Array<type>::end() const {
  return buffer.get() + bufferSize;
}

template <class type>
void openlib::Array<type>::fill(const type& value) {
  for (std::size_t i = 0; i < bufferSize; i++) {
    buffer.get()[i] = value;
  }
}

template <class type>
openlib::Array<type>::operator type*() const {
  return data();
}

template <class type>
type& openlib::Array<type>::operator[](std::size_t position) {
  return at(position);
}

template <class type>
const type& openlib::Array<type>::operator[](std::size_t position) const {
  return at(position);
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
