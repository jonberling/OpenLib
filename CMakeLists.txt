cmake_minimum_required(VERSION 3.2)

include(CheckCXXCompilerFlag)
ENABLE_LANGUAGE(CXX)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

project(OpenLib VERSION 2.0)

file(GLOB_RECURSE OpenLib_SRC src/*.cpp)

add_library(OpenLib SHARED ${OpenLib_SRC})
target_include_directories(OpenLib PUBLIC include/)

add_subdirectory(tests)
add_subdirectory(examples)
