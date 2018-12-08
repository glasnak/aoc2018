cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2018)
set (YEAR "2018")

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include )

set(CMAKE_CXX_STANDARD 17)


find_program(LSB_RELEASE_EXEC lsb_release)
execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
    OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

if (${LSB_RELEASE_ID_SHORT} STREQUAL Ubuntu)
  message("-- Running on Ubuntu")
else ()
  set(CMAKE_C_COMPILER /media/narnia/glasnak/pure-llvm/llvm-7.0.0.src/build/bin/clang)
  set(CMAKE_CXX_COMPILER /media/narnia/glasnak/pure-llvm/llvm-7.0.0.src/build/bin/clang++)
endif ()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O3")


# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB MyCSources src/*.cpp)
ADD_EXECUTABLE(aoc2018.out ${MyCSources} )




