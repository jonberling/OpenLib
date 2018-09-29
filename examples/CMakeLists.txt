cmake_minimum_required(VERSION 3.2)

include(GoogleTest)

project(OpenLibExamples)

file(GLOB OpenLibExamples_SRC *.cpp)

add_executable(
  OpenLibExamples
  ${OpenLibExamples_SRC}
)

target_link_libraries(OpenLibExamples ${GTEST_LIBRARIES} OpenLib gtest pthread)

