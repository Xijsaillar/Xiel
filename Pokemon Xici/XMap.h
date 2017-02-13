#pragma once
#ifndef _XMAP_H_
#define _XMAP_H_
#define VERSION2_MAP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>

class XEngine;

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
	int currAni{0};
};
#pragma pack(pop)

struct TileAnimation {
	sf::Texture texture;
	sf::Sprite sprite;
	int nFrames{0};
};

class XMap
{
public:
	XMap() { };
	~XMap() { };

	bool Init();
	bool LoadMapFromFile(std::string filename);

	void SetDebug() { bIsDebug = !bIsDebug; }

	void Render(sf::RenderWindow *window, sf::Vector2f position);

	bool isCollision(sf::Vector2f);
private:
	int CoordinateToID(int width, int x, int y);

	// Animations
	void LoadAnimationTiles();

	float lastUpdated{0};
	sf::Clock clock;

	sf::Vector2i CoordinateFromID(int width, int index);
	// Debug Only
	void DrawGrid(sf::RenderWindow*);

	bool bIsDebug{false};
	// Texture & sprites
	sf::Texture texture, tileset;
	MAPHEADER mapHeader;
	std::vector<MapTile> m_vTiles;
	std::unordered_map<int, std::unique_ptr<TileAnimation>> m_vAnimations;
};
#endif // _XMAP_H_