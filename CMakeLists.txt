cmake_minimum_required(VERSION 3.7)
project(Pokemon_Xici)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system")

set(SOURCE_FILES
    "Pokémon Xici/Texture/AnimatedSprite.cpp"
    "Pokémon Xici/Texture/AnimatedSprite.hpp"
    "Pokémon Xici/Texture/Animation.cpp"
    "Pokémon Xici/Texture/Animation.hpp"
    "Pokémon Xici/Texture/XSprite.cpp"
    "Pokémon Xici/Texture/XSprite.h"
    "Pokémon Xici/main.cpp"
    "Pokémon Xici/TypeWriter.cpp"
    "Pokémon Xici/TypeWriter.h"
    "Pokémon Xici/XBattle.cpp"
    "Pokémon Xici/XBattle.h"
    "Pokémon Xici/XEngine.cpp"
    "Pokémon Xici/XEngine.h"
    "Pokémon Xici/XMap.cpp"
    "Pokémon Xici/XMap.h"
    "Pokémon Xici/XPlayer.cpp"
    "Pokémon Xici/XPlayer.h")

add_executable(Pokemon_Xici ${SOURCE_FILES})