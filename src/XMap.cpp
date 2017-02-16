#include "XMap.h"
#include <fstream>
#include <math.h>

// TODO
// Rewrite because working with not-shown tiles is bullshit

bool XMap::Init() {
	m_vTiles.clear();

	// Load the animation textures
	this->LoadAnimationTiles();
	// Load the default tileset we're using
	return tileset.loadFromFile("data/tileset_firered.png");
}


void XMap::test(sf::RenderWindow *window, sf::Vector2f position) {

	for (int y{0}; y < mapHeader.Height; y += 16) {
		for (int x{0}; x < mapHeader.Width; x += 16) {
			if (m_vMap.count(std::to_string(x) + ":" + std::to_string(y)) >= 1) {
				m_vMap[std::to_string(x) + ":" + std::to_string(y)]->sprite.setPosition(
						m_vMap[std::to_string(x) + ":" + std::to_string(y)]->sprite.getPosition().x + position.x,
						m_vMap[std::to_string(x) + ":" + std::to_string(y)]->sprite.getPosition().y + position.y);
				window->draw(m_vMap[std::to_string(x) + ":" + std::to_string(y)]->sprite);
			}
		}
	}

}

/**
 * Render the map
 * @param window - the Render Window
 * @param position - the players position, needed to calculate the actual position for drawing
 */
void XMap::Render(sf::RenderWindow *window, sf::Vector2f position) {
	test(window, position);
	return;
	float elapsed = clock.getElapsedTime().asSeconds();

	bool tmp{false};

	for (auto it = m_vTiles.begin(); it != m_vTiles.end(); it++) {
		auto s = (*it);

		if (m_vAnimations.count(s.info.tileID) == 0) {
			s.sprite.setPosition(s.sprite.getPosition().x + position.x, s.sprite.getPosition().y + position.y);
			window->draw(s.sprite);
		} else {
			m_vAnimations[s.info.tileID]->sprite.setPosition(s.sprite.getPosition().x + position.x,
															 s.sprite.getPosition().y + position.y);

			if ((elapsed - lastUpdated) > .25f) {
				m_vAnimations[s.info.tileID]->sprite.setTextureRect(
						{16 * it->currAni++, 0, mapHeader.Scale, mapHeader.Scale});

				if (it->currAni == m_vAnimations[s.info.tileID]->nFrames)
					it->currAni = 0;
				tmp = true;
			}
			window->draw(m_vAnimations[s.info.tileID]->sprite);
		}
	}
	if (tmp) {
		lastUpdated = clock.getElapsedTime().asSeconds();
	}

	if (bIsDebug)
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

void XMap::DrawGrid(sf::RenderWindow *window) {
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

void XMap::LoadAnimationTiles() {

	std::fstream in("data/animation/animation.lnk", std::ios::in | std::ios::binary);
	if (!in.is_open())
		return;

	while (in.good()) {

		int id{0};
		std::string fileName{0};
		std::unique_ptr<TileAnimation> a{new TileAnimation};
		in >> id >> a->nFrames >> fileName;

		if (!a->texture.loadFromFile("data/animation/" + fileName))
			return;

		a->sprite.setTexture(a->texture);
		a->sprite.setTextureRect({0, 0, 16, 16});
		m_vAnimations.insert(std::make_pair(id, std::move(a)));
	}
	in.close();
}

bool XMap::LoadMapFromFile(std::string filename, int nOffsetX = 0, int nOffsetY = 0) {

	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
		return false;

	// Read file header
	file.read((char *) &mapHeader, sizeof(MAPHEADER));

	float x = nOffsetX, y = nOffsetY;
	// Read X tiles and proceed them
	for (int i = 0; i < mapHeader.Count; i++) {

		TILE tile;
		sf::Sprite tilesprite;
		MapTile t;

		file.read((char *) &tile, sizeof(TILE));
		auto vector = CoordinateFromID(tileset.getSize().x / mapHeader.Scale, tile.tileID);

		tilesprite.setTexture(tileset);
		tilesprite.setTextureRect(
				{vector.x * mapHeader.Scale, vector.y * mapHeader.Scale, mapHeader.Scale, mapHeader.Scale});
		tilesprite.setPosition(x, y);
		t.info = tile;
		t.sprite = tilesprite;
		//m_vTiles.push_back(t);
		m_vMap[std::to_string(x) + ":" + std::to_string(y)] = std::make_unique<MapTile>(t);

		if (x + mapHeader.Scale == mapHeader.Width * mapHeader.Scale) {
			y += mapHeader.Scale;
			x = 0;
		} else {
			x += mapHeader.Scale;
		}
	}

	file.close();

	return true;
}

int XMap::CoordinateToID(int width, int x, int y) {
	return y * width + x;
}


//************************************
// Method:    CoordinateFromID
// FullName:  XMap::CoordinateFromID
// Access:    private 
// Returns:   sf::Vector2i
// Qualifier: I HAVE NO IDEA WHAT THE FUCK THIS DOES - DO NOT TOUCH 
// Parameter: int width
// Parameter: int index
//************************************
sf::Vector2i XMap::CoordinateFromID(int width, int index) {
	sf::Vector2i p;
	float n = float(index / width);

	p.y = (int) floor(n);
	p.x = -p.y * width + index;
	return sf::Vector2i(p.x, p.y);
}
