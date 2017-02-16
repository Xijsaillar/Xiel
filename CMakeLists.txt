cmake_minimum_required(VERSION 3.7)
project(Pokemon_Xici)

# we're using C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")

# Output to a bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# No deprecated warnings
add_compile_options(-Wno-deprecated-declarations)

# set macro-directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

# find the SFML 2 lib, without it nothing works
find_package(SFML 2 REQUIRED system window graphics audio)

# include directories, no need to use #include "FOLDER/File.h"
include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/Interfaces
        ${CMAKE_SOURCE_DIR}/src/Objects
        ${CMAKE_SOURCE_DIR}/src/Texture
        ${SFML_INCLUDE_DIR})

# Add all the source files to our project...
file(GLOB_RECURSE sources
     src/*.cpp
     src/*.h
     src/*.hpp)

# ...link them to the executable
add_executable(Pokemon_Xici ${sources})

# and finally link the libraries
target_link_libraries(Pokemon_Xici ${SFML_LIBRARIES})


