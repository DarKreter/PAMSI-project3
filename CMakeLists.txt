cmake_minimum_required(VERSION 3.10)

project(PAMSI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPU_OPTIONS -Werror -Wall -Wextra -pedantic -ffunction-sections -fdata-sections -Os)
add_compile_options(${CPU_OPTIONS})

# Threads
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_subdirectory(SFML)
add_subdirectory(Tile)
add_subdirectory(Figure)
add_subdirectory(Pawn)
add_subdirectory(Board)
add_subdirectory(firmware)