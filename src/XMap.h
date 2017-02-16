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
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	int nFrames{0};
	int nCurrentAnimation{0};
};

class XMap {
public:
	XMap() {};

	~XMap() {};

	bool Init();
	void SetDebug() { bIsDebug = !bIsDebug; }

	bool LoadMapFromFile(std::string filename, int nOffsetX, int nOffsetY);

	bool isCollision(sf::Vector2i);

	void Update();
	void Render(sf::RenderWindow *window, sf::Vector2f position);

	int CoordinateToID(int width, int x, int y);
	sf::Vector2i CoordinateFromID(int width, int index);

private:
	bool LoadAnimationTiles();
	void DrawGrid(sf::RenderWindow *);

	float lastUpdated{0};
	sf::Clock clock;

	bool bIsDebug{false};
	sf::Texture texture, tileset;

	int nWidth{0}, nHeight{0};

	std::unordered_map<int, std::unique_ptr<TileAnimation>> m_vAnimations;
	std::unordered_map<sf::Vector2i, std::unique_ptr<XMapTile>, KeyHasher> m_vMap;
};

#endif // _XMAP_H_