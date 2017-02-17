//
// Created by xijezu on 16.02.17.
//

#ifndef POKEMON_XICI_MAPSTRUCTS_H
#define POKEMON_XICI_MAPSTRUCTS_H

#define VERSION 3

#include <SFML/Graphics.hpp>

constexpr int g_nScale = 16;

#pragma pack(push, 1)
typedef struct {
	int nWidth;
	int nHeight;
	int nScale;
	int nCount;
#if VERSION >= 3
	int nLayer;
#endif
	char md5[16];
} XMapHeader;

typedef struct {
	int nTileID;
	int nCollisionLayer;
} XTile;
#pragma pack(pop)

typedef struct {
#if VERSION >= 3
	std::vector<sf::Sprite> tileSprite;
#else
	sf::Sprite tileSprite;
#endif
	XTile xTile;
	sf::Vector2i vBasePosition;
} XMapTile;

#endif //POKEMON_XICI_MAPSTRUCTS_H
