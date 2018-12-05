cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2018)
set (YEAR "2018")

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_COMPILER /media/narnia/glasnak/pure-llvm/llvm-7.0.0.src/build/bin/clang)
set(CMAKE_CXX_COMPILER /media/narnia/glasnak/pure-llvm/llvm-7.0.0.src/build/bin/clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB MyCSources *.cpp)
ADD_EXECUTABLE(aoc2018.out ${MyCSources})




