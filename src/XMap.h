#pragma once
#ifndef _XMAP_H_
#define _XMAP_H_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include "MapStructs.h"
#include "Objects.h"

class XEngine;

struct TileAnimation {
	sf::Texture texture;
	sf::Sprite sprite;
	int nFrames{0};
};

class XMap {
public:
	XMap() {};

	~XMap() {};

	bool Init();

	bool LoadMapFromFile(std::string filename, int nOffsetX, int nOffsetY);

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
	void DrawGrid(sf::RenderWindow *);

	bool bIsDebug{false};
	// Texture & sprites
	sf::Texture texture, tileset;
	MAPHEADER mapHeader;
	std::vector<MapTile> m_vTiles;
	std::unordered_map<int, std::unique_ptr<TileAnimation>> m_vAnimations;
	std::unordered_map<sf::Vector2i, std::unique_ptr<MapTile>, KeyHasher> m_vMap;
};

#endif // _XMAP_H_