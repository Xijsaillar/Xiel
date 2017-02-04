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
};
#pragma pack(pop)

class XMap
{
public:
	XMap() { };
	~XMap() { };

	bool Init(XEngine&);
	bool LoadMapFromFile(std::string filename);
	void Render(sf::RenderWindow* window, sf::Vector2f position);
	bool isCollision(sf::Vector2f);
private:
	int CoordinateToID(int width, int height, int x, int y);
	sf::Vector2i CoordinateFromID(int width, int height, int index);
	// Debug Only
	void DrawGrid(sf::RenderWindow*);
	// Texture & sprites
	sf::Texture texture, tileset;
	sf::Sprite sprite;
	MAPHEADER mapHeader;
	std::vector<MapTile> m_vTiles;
	// Pointer to our Engine
	XEngine* m_pEngine;
};
#endif // _XMAP_H_