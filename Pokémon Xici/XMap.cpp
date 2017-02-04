#include "XMap.h"
#include <fstream>
#include <math.h>

bool XMap::Init(XEngine& pEngine) {
	m_vTiles.clear();
	return true;
}

void XMap::Render(sf::RenderWindow* window, sf::Vector2f position) {
	for (int i = 0; i < m_vTiles.size(); i++) {
		auto s = m_vTiles[i];
		s.sprite.setPosition(s.sprite.getPosition().x  + position.x, s.sprite.getPosition().y  + position.y);
		window->draw(s.sprite);

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
	int test = this->CoordinateToID(mapHeader.Width, (int) pos.x / 16, (int) pos.y / 16);
	// Safety first
	return m_vTiles.size() <= test || m_vTiles[test].info.CollissionLayer > 0;
	// Return real data
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
	for (float x = 0; x < 1000; x += 16) {
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
	// ----------------------------------- > DEBUG ONLY
	mapHeader.Scale = 16;

	if (!tileset.loadFromFile("data/tileset.png"))
		return false;

	float x = 0, y = 0;
	// Read X tiles and proceed them
	for (int i = 0; i < mapHeader.Count; i++) {

		TILE tile;
		sf::Sprite tilesprite;
		MapTile t;

		file.read((char*)&tile, sizeof(TILE));
		auto vector = CoordinateFromID(tileset.getSize().x / mapHeader.Scale, tileset.getSize().y / mapHeader.Scale, tile.tileID);

		tilesprite.setTexture(tileset);
		tilesprite.setTextureRect(sf::IntRect(vector.x * mapHeader.Scale, vector.y * mapHeader.Scale, mapHeader.Scale, mapHeader.Scale));
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
sf::Vector2i XMap::CoordinateFromID(int width, int height, int index)
{
	sf::Vector2i p;
	float n = float(index / width);

	p.y = (int)floor(n);
	p.x = -p.y * width + index;
	return sf::Vector2i(p.x, p.y);
}
