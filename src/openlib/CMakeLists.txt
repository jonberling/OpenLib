project (OpenLib C CXX)

set(OPENLIB_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/.. CACHE STRING "OpenLib include files")

add_library(
  openlib
  array/Array.cpp
  array/BufferArray.cpp
  log/Log.cpp
  log/LogHandler.cpp
  log/LogLevel.hpp
  math/Angle.cpp
  math/Vector2d.cpp
  math/Range.cpp
  time/ElapsedTime.cpp
)
