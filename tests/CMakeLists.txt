cmake_minimum_required(VERSION 3.2)

include(GoogleTest)

project(OpenLibTests)

file(GLOB OpenLibTests_SRC *.cpp)

add_executable(
  testOpenLib
  ${OpenLibTests_SRC}
)

target_link_libraries(testOpenLib ${GTEST_LIBRARIES} OpenLib gtest pthread)

