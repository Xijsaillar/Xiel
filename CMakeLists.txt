cmake_minimum_required(VERSION 3.7)
project(Pokemon_Xici)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_compile_options(-Wno-deprecated-declarations)

set(SOURCE_FILES
    "src/Texture/AnimatedSprite.cpp"
    "src/Texture/AnimatedSprite.hpp"
    "src/Texture/Animation.cpp"
    "src/Texture/Animation.hpp"
    "src/Texture/XSprite.cpp"
    "src/Texture/XSprite.h"
    "src/main.cpp"
    "src/TypeWriter.cpp"
    "src/TypeWriter.h"
    "src/XBattle.cpp"
    "src/XBattle.h"
    "src/XEngine.cpp"
    "src/XEngine.h"
    "src/XMap.cpp"
    "src/XMap.h"
    "src/XPlayer.cpp"
    "src/XPlayer.h"
    "src/Interfaces/States.h" "src/Objects/Pokemon.cpp" "src/Objects/Pokemon.h" "src/Objects/Objects.h")

add_executable(Pokemon_Xici ${SOURCE_FILES})
