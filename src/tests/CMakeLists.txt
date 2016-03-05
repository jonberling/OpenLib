project (OpenLibTests C CXX)

add_subdirectory(gtest/googletest/)

include_directories(${OPENLIB_INCLUDE_DIR})

add_executable(
  runTests
  tests.cpp
  arraytest.cpp
  logtest.cpp
  mathtest.cpp
  timetest.cpp
)

target_link_libraries(runTests ${GTEST_LIBRARIES} openlib gtest pthread)
