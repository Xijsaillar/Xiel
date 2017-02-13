#include "XMap.h"
#include <fstream>
#include <math.h>
#include <iostream>

// TODO
// Rewrite because working with not-shown tiles is bullshit

bool XMap::Init(XEngine& pEngine) {
	m_vTiles.clear();
	return true;
}

void XMap::Render(sf::RenderWindow *window, sf::Vector2f position, float deltaTime) {

	deltaTime = clock.getElapsedTime().asSeconds();

	bool tmp{false};

	for (auto it = m_vTiles.begin(); it != m_vTiles.end(); it++) {
		auto s = (*it);
		s.sprite.setPosition(s.sprite.getPosition().x  + position.x, s.sprite.getPosition().y  + position.y);

		if ((deltaTime - lastUpdated) > .25f) {
			switch (s.info.tileID) {
				case 4:
					it->sprite.setTextureRect({16 * it->currAni++, 0, mapHeader.Scale, mapHeader.Scale});
					if (it->currAni == 5)
						it->currAni = 0;
					break;
				case 299:
				case 300:
					it->sprite.setTextureRect({16 * it->currAni++, 0, mapHeader.Scale, mapHeader.Scale});
					if (it->currAni == 8)
						it->currAni = 0;
					break;
				default:
					break;
			}
			tmp = true;
		}

		window->draw(s.sprite);
	}
	if (tmp) {
		lastUpdated = clock.getElapsedTime().asSeconds();
	}

	DrawGrid(window);
}


//************************************
// Method:    isCollision
// FullName:  XMap::isCollision
// Access:    public
// Returns:   bool
// Qualifier:
// Parameter: sf::Vector2f pos
//************************************
bool XMap::isCollision(sf::Vector2f pos) {
	// If generally out of map
	if (pos.x < 0 || pos.y < 0 || pos.x >= mapHeader.Width * 16 || pos.y >= mapHeader.Height * 16)
		return true;
	// Get position
	int nID = this->CoordinateToID(mapHeader.Width, (int) pos.x / 16, (int) pos.y / 16);
	return m_vTiles.size() <= nID || m_vTiles[nID].info.CollissionLayer > 0;
}

void XMap::DrawGrid(sf::RenderWindow* window) {
	for (float x = 0; x < 1000; x += 16) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x, 0)),
			sf::Vertex(sf::Vector2f(x, 1000))
		};

		window->draw(line, 2, sf::Lines);
	}
	for (float x = 4; x < 1000; x += 16) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0, x)),
			sf::Vertex(sf::Vector2f(1000, x))
		};

		window->draw(line, 2, sf::Lines);
	}
}

bool XMap::LoadMapFromFile(std::string filename) {

	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
		return false;

	// Read file header
	file.read((char*)&mapHeader, sizeof(MAPHEADER));

	if (!tileset.loadFromFile("data/tileset_firered.png"))
		return false;

	if (!flowers.loadFromFile("data/animation/flowers.png"))
		return false;

	if (!water.loadFromFile("data/animation/water.png"))
		return false;

	if (!wcr.loadFromFile("data/animation/wcr.png"))
		return false;

	float x = 0, y = 0;
	// Read X tiles and proceed them
	for (int i = 0; i < mapHeader.Count; i++) {

		TILE tile;
		sf::Sprite tilesprite;
		MapTile t;

		file.read((char*)&tile, sizeof(TILE));
		auto vector = CoordinateFromID(tileset.getSize().x / mapHeader.Scale, tile.tileID);

		if (tile.tileID == 4) {
			tilesprite.setTexture(flowers);
			tilesprite.setTextureRect({0, 0, mapHeader.Scale, mapHeader.Scale});
		} else if (tile.tileID == 299) {
			tilesprite.setTexture(water);
			tilesprite.setTextureRect({0, 0, mapHeader.Scale, mapHeader.Scale});
		} else if (tile.tileID == 300) {
			tilesprite.setTexture(wcr);
			tilesprite.setTextureRect({0, 0, mapHeader.Scale, mapHeader.Scale});
		} else {
			tilesprite.setTexture(tileset);
			tilesprite.setTextureRect(
					{vector.x * mapHeader.Scale, vector.y * mapHeader.Scale, mapHeader.Scale, mapHeader.Scale});
		}
		tilesprite.setPosition(x, y);
		t.info = tile;
		t.sprite = tilesprite;
		m_vTiles.push_back(t);

		if (x + mapHeader.Scale == mapHeader.Width * mapHeader.Scale) {
			y += mapHeader.Scale;
			x = 0;
		}
		else {
			x += mapHeader.Scale;
		}
	}

	file.close();

	return true;
}

int XMap::CoordinateToID(int width, int x, int y)
{
	return y * width + x;
}


//************************************
// Method:    CoordinateFromID
// FullName:  XMap::CoordinateFromID
// Access:    private 
// Returns:   sf::Vector2i
// Qualifier: I HAVE NO IDEA WHAT THE FUCK THIS DOES - DO NOT TOUCH 
// Parameter: int width
// Parameter: int height
// Parameter: int index
//************************************
sf::Vector2i XMap::CoordinateFromID(int width, int index)
{
	sf::Vector2i p;
	float n = float(index / width);

	p.y = (int)floor(n);
	p.x = -p.y * width + index;
	return sf::Vector2i(p.x, p.y);
}
