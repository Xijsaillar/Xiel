#pragma once
#ifndef _XMAP_H_
#define _XMAP_H_
#define VERSION2_MAP

#include <SFML/Graphics.hpp>
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

class XMap
{
public:
	XMap() { };
	~XMap() { };

	bool Init(XEngine&);
	bool LoadMapFromFile(std::string filename);

	void Render(sf::RenderWindow *window, sf::Vector2f position, float deltaTime);
	bool isCollision(sf::Vector2f);
private:
	int CoordinateToID(int width, int x, int y);

	bool flipped{false};
	float delta{0}, lastUpdated{0};
	sf::Clock clock;

	sf::Vector2i CoordinateFromID(int width, int index);
	// Debug Only
	void DrawGrid(sf::RenderWindow*);
	// Texture & sprites
	sf::Texture texture, tileset, flowers, water, wcr;
	sf::Sprite sprite;
	MAPHEADER mapHeader;
	std::vector<MapTile> m_vTiles;
};
#endif // _XMAP_H_