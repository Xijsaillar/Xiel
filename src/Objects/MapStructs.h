//
// Created by xijezu on 16.02.17.
//

#ifndef POKEMON_XICI_MAPSTRUCTS_H
#define POKEMON_XICI_MAPSTRUCTS_H

#define VERSION2_MAP

#include <SFML/Graphics.hpp>

constexpr int g_nScale = 16;

#pragma pack(push, 1)
typedef struct {
	int nWidth;
	int nHeight;
	int nScale;
	int nCount;
#ifdef VERSION2_MAP
	char md5[32];
#endif
} XMapHeader;

typedef struct {
	int nTileID;
	int nCollisionLayer;
#ifndef VERSION2_MAP
	int EventID;
#endif
} XTile;
#pragma pack(pop)

typedef struct {
	sf::Sprite tileSprite;
	XTile xTile;
	sf::Vector2i vBasePosition;
} XMapTile;

#endif //POKEMON_XICI_MAPSTRUCTS_H
