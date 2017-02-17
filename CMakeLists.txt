project(Pokemon_Xici)
cmake_minimum_required(VERSION 2.8.9)

# we're using C++14
add_definitions(-std=c++14)

# No deprecated warnings
add_compile_options(-Wno-deprecated-declarations)

# set macro-directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

# find the SFML 2 lib, without it nothing works
find_package(SFML 2 REQUIRED system window graphics audio)
find_package(LUA REQUIRED)

# include directories, no need to use
include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/Interfaces
        ${CMAKE_SOURCE_DIR}/src/Objects
        ${CMAKE_SOURCE_DIR}/src/Texture
        ${CMAKE_SOURCE_DIR}/src/Script
        ${SFML_INCLUDE_DIR})

# Add all the source files to our project...
file(GLOB_RECURSE xici_sources
     src/*.cpp
     src/*.h
     src/*.hpp)

# ...link them to the executable
add_executable(Xici ${xici_sources})

# and finally link the libraries
target_link_libraries(Xici ${SFML_LIBRARIES} ${LUA_LIBRARIES})


