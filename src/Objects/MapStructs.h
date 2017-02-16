//
// Created by xijezu on 16.02.17.
//

#ifndef POKEMON_XICI_MAPSTRUCTS_H
#define POKEMON_XICI_MAPSTRUCTS_H

#define VERSION2_MAP

#include <SFML/Graphics.hpp>

#pragma pack(push, 1)
struct MAPHEADER {
	int Width;
	int Height;
	int Scale;
	int Count;
#ifdef VERSION2_MAP
	char md5[32];
#endif
};

struct TILE {
	int tileID;
	int CollissionLayer;
#ifndef VERSION2_MAP
	int EventID;
#endif
};

struct MapTile {
	sf::Sprite sprite;
	TILE info;
	sf::Vector2i vBasePosition;
	int currAni{0};
};
#pragma pack(pop)

#endif //POKEMON_XICI_MAPSTRUCTS_H
