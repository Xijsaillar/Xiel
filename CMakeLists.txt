cmake_minimum_required(VERSION 3.7)
project(Pokemon_Xici)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_compile_options(-Wno-deprecated-declarations)

set(SOURCE_FILES
    "Pokemon Xici/Texture/AnimatedSprite.cpp"
    "Pokemon Xici/Texture/AnimatedSprite.hpp"
    "Pokemon Xici/Texture/Animation.cpp"
    "Pokemon Xici/Texture/Animation.hpp"
    "Pokemon Xici/Texture/XSprite.cpp"
    "Pokemon Xici/Texture/XSprite.h"
    "Pokemon Xici/main.cpp"
    "Pokemon Xici/TypeWriter.cpp"
    "Pokemon Xici/TypeWriter.h"
    "Pokemon Xici/XBattle.cpp"
    "Pokemon Xici/XBattle.h"
    "Pokemon Xici/XEngine.cpp"
    "Pokemon Xici/XEngine.h"
    "Pokemon Xici/XMap.cpp"
    "Pokemon Xici/XMap.h"
    "Pokemon Xici/XPlayer.cpp"
    "Pokemon Xici/XPlayer.h"
    "Pokemon Xici/Interfaces/States.h" "Pokemon Xici/Objects/Pokemon.cpp" "Pokemon Xici/Objects/Pokemon.h" "Pokemon Xici/Objects/Objects.h")

add_executable(Pokemon_Xici ${SOURCE_FILES})
