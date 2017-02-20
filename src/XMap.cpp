#include "XMap.h"
#include <fstream>
#include <math.h>
#include <Objects/MapStructs.h>
#include "XEngine.h"

// TODO
// Done rewriting for only visible tiles
// Now check if it actually works

/**
 * XMap::Init
 * Initialize the map
 * @return true if successful, false if failed
 */
bool XMap::Init() {
	// Load the animation textures
/*	if (!this->LoadAnimationTiles())
		return false;*/
	// Load the default tileset we're using
	return tileset.loadFromFile("data/dawn.png");
}

/**
 * XMap::Update
 * Update the tile animations
 */
void XMap::Update(float deltaTime) {

	sf::Vector2f pos = g_XEngine.GetPlayer()->GetRelativePosition();
	// Loop through x and y, 192 being half the size of the viewport
	for (int y = -192; y < 192; y += 16) {
		for (int x = -192; x < 192; x += 16) {

			// Add the current x/y value to the relative position
			sf::Vector2i p{(int) pos.x + x, (int) pos.y + y};
			if (m_vNPC.count(p) == 1) {

				g_XEngine.m_vNPC[m_vNPC[p]]->UpdateCharacter(deltaTime);
			}
		}
	}

	// Get our own deltaTime
	float elapsed = clock.getElapsedTime().asSeconds();

	// If the last update was over 0.25 seconds ago...
	if ((elapsed - lastUpdated) > .25f) {
		// ...loop through our animations...
		for (auto &it : m_vAnimations) {
			//for (auto it = m_vAnimations.begin(); it != m_vAnimations.end(); it++) {

			// ...set the tileTexture rect to the next frame...
			it.second->tileSprite.setTextureRect({16 * it.second->nCurrentAnimation++,
												  0,
												  g_nScale,
												  g_nScale});

			// ... reset the current animation index to zero if it's the same as the actual frames...
			if (it.second->nCurrentAnimation == it.second->nFrames) {
				it.second->nCurrentAnimation = 0;
			}
		}
		// ... and finally update our lastUpdated
		lastUpdated = elapsed;
	}

}

/**
 * XMap::Render
 * Render the map
 * @param window - the Render Window
 * @param position - the players position, needed to calculate the actual position for drawing
 */
void XMap::Render(sf::RenderWindow *window, sf::Vector2f position, float deltaTime) {

	// Get the elapsed time as seconds (deltaTime)
	float elapsed = clock.getElapsedTime().asSeconds();
	// use a temp bool for checking if the animations were rendered
	bool tmp{false};

	// Get the position relative to the map (e.g. player is on tile X: 0, Y: 64
	sf::Vector2f pos = g_XEngine.GetPlayer()->GetRelativePosition();

	// Loop through x and y, 192 being half the size of the viewport
	for (int y = -192; y < 192; y += 16) {
		for (int x = -192; x < 192; x += 16) {

			// Add the current x/y value to the relative position
			sf::Vector2i p{(int) pos.x + x, (int) pos.y + y};

			// If the map contains a tile for the calculated position
			if (m_vMap.count(p) == 1) {

				// If the current tile is linked to an animation...
				if (m_vAnimations.count(m_vMap[p]->xTile.nTileID) == 1) {
					// ... Set the position of the animation tileSprite ...
					m_vAnimations[m_vMap[p]->xTile.nTileID]->tileSprite.setPosition(
							m_vMap[p]->vBasePosition.x + position.x,
							m_vMap[p]->vBasePosition.y + position.y);

					// ... and finally draw the animation tileSprite
					window->draw(m_vAnimations[m_vMap[p]->xTile.nTileID]->tileSprite);

				} else {
#if VERSION >= 3
					for (auto &it : m_vMap[p]->tileSprite) {
						// set the position of the current tile
						it.setPosition(m_vMap[p]->vBasePosition.x + position.x,
									   m_vMap[p]->vBasePosition.y + position.y);
						// Draw the actual tileSprite
						window->draw(it);
					}
#else
					// set the position of the current tile
					m_vMap[p]->tileSprite.setPosition(m_vMap[p]->vBasePosition.x + position.x,
													  m_vMap[p]->vBasePosition.y + position.y);
					// Draw the actual tileSprite
					window->draw(m_vMap[p]->tileSprite);
#endif
				}
			}
			if (m_vNPC.count(p) == 1) {
				g_XEngine.m_vNPC[m_vNPC[p]]->Render(window, deltaTime, {position.x, position.y - 4});
			}
		}
	}

	// If there was a frame update set the last update to the current time
	if (tmp) {
		lastUpdated = elapsed;
	}

	// And if we enabled debugging (pressing D ingame) draw a grid over the window
	if (bIsDebug)
		DrawGrid(window);
}


/**
 * XMap::isCollision
 * @param pos - the next tile the player is about to enter
 * @return true on colission, false on passable
 */
bool XMap::isCollision(sf::Vector2i pos) {
	// If generally out of map
	if (pos.x < 0 || pos.y < 0 || pos.x >= nWidth * 16 || pos.y >= nHeight * 16)
		return true;
	// return out of map |or| layer-id not 0
	return m_vMap.count(pos) == 0 || m_vMap[pos]->xTile.nCollisionLayer > 0;
}

/**
 * XMap::DrawGrid
 * @param window - the render window
 */
void XMap::DrawGrid(sf::RenderWindow *window) {

	// Draw vertical grid lines
	for (float x = 0; x < 512; x += 16) {
		sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x, 0)),
				sf::Vertex(sf::Vector2f(x, 512))
		};
		window->draw(line, 2, sf::Lines);
	}
	// Draw horizontal grid lines
	for (float x = 4; x < 388; x += 16) {
		sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(0, x)),
				sf::Vertex(sf::Vector2f(384, x))
		};
		window->draw(line, 2, sf::Lines);
	}
}

/**
 * XMap::LoadAnimationTiles
 * Load the animation tiles from the .lnk file
 * @return true on success, false on error
 */
bool XMap::LoadAnimationTiles() {

	// Open the file for reading
	std::fstream finAnimations("data/animation/animation.lnk", std::ios::in | std::ios::binary);
	if (!finAnimations.is_open())
		return false;

	// While the file is readable
	while (finAnimations.good()) {

		// declaration of temp variables
		int nID{0};
		std::string fileName{0};
		// declaration of the struct
		std::unique_ptr<TileAnimation> tileAnimation{new TileAnimation};
		// Read the contens
		finAnimations >> nID >> tileAnimation->nFrames >> fileName;

		// Load the matching tileTexture
		if (!tileAnimation->tileTexture.loadFromFile("data/animation/" + fileName))
			return false;

		// Assign the tileTexture to the tileSprite
		tileAnimation->tileSprite.setTexture(tileAnimation->tileTexture);
		tileAnimation->tileSprite.setTextureRect({0, 0, 16, 16});
		// Insert the unique_ptr<TileAnimation> into our unordered_map
		m_vAnimations.insert(std::make_pair(nID, std::move(tileAnimation)));
	}
	// Close the file and return true
	finAnimations.close();
	return true;
}


/**
 * XMap::LoadMapFromFile
 * @param filename
 * @param nOffsetX
 * @param nOffsetY
 * @return true on success, false on error
 */
bool XMap::LoadMapFromFile(std::string filename, int nOffsetX = 0, int nOffsetY = 0) {

	// Open the map finMap for reading
	std::ifstream finMap(filename, std::ios::binary);
	if (!finMap.is_open())
		return false;


	XMapHeader mapHeader;
	// Read Map header struct

	// TODO
	// No pure C reading here
	finMap.read((char *) &mapHeader, sizeof(XMapHeader));
#if VERSION >= 3
	for (int loop = 0; loop < mapHeader.nLayer; loop++) {
#endif
		int x = 0, y = 0;
		// Read X tiles and proceed them
		for (int i = 0; i < mapHeader.nCount; i++) {

			// Declare variables
			XTile tile;
			sf::Sprite tilesprite;
			XMapTile t;

			// Read Tile struct
			finMap.read((char *) &tile, sizeof(XTile));

			// Get the Coordinates in the tileset from the Tile ID
			auto vector = CoordinateFromID(tileset.getSize().x / mapHeader.nScale, tile.nTileID);

			// Set the tileTexture of the tileSprite
			tilesprite.setTexture(tileset);
			tilesprite.setTextureRect({vector.x * mapHeader.nScale,
									   vector.y * mapHeader.nScale,
									   mapHeader.nScale,
									   mapHeader.nScale});
			// Set the base position of the tileSprite
			tilesprite.setPosition(x + nOffsetX, y + nOffsetY);
			t.vBasePosition = {x + nOffsetX, y + nOffsetY};
			// Assign variables to the XMapTile
			t.xTile = tile;
#if VERSION >= 3
			t.tileSprite.push_back(tilesprite);
#else
			t.tileSprite = tilesprite;
#endif

#if VERSION >= 3
			// And add it to our unordered_map
			if (loop == 0) {
				m_vMap[{x + nOffsetX, y + nOffsetY}] = std::make_unique<XMapTile>(t);
			} else {
				if (t.xTile.nTileID != -1)
					m_vMap[{x + nOffsetX, y + nOffsetY}]->xTile.nCollisionLayer = t.xTile.nCollisionLayer;

				m_vMap[{x + nOffsetX, y + nOffsetY}]->tileSprite.push_back(tilesprite);
			}
#else
			m_vMap[{x + nOffsetX, y + nOffsetY}] = std::make_unique<XMapTile>(t);
#endif
			// Manual check to keep the x and y coordinates in range
			if (x + mapHeader.nScale == mapHeader.nWidth * mapHeader.nScale) {
				y += mapHeader.nScale;
				x = 0;
			} else {
				x += mapHeader.nScale;
			}
		}
#if VERSION >= 3
	}
#endif

	// Add the width + height of the loaded map to our global map width + height
	nWidth += mapHeader.nWidth;
	nHeight += mapHeader.nHeight;

	// Close the file and return true
	finMap.close();

	return true;
}

/**
 * XMap::CoordinateToID
 * @param width
 * @param x
 * @param y
 * @return Index based on the given coordinates
 */
int XMap::CoordinateToID(int width, int x, int y) {
	return y * width + x;
}


/**
 * XMap::CoordinateFromID
 * @param width
 * @param index
 * @return sf::Vector2i containing the x and y coordinates based on the ID
 * Note: I have no idea how this works
 */
sf::Vector2i XMap::CoordinateFromID(int width, int index) {
	sf::Vector2i p;
	float n = float(index / width);

	p.y = (int) floor(n);
	p.x = -p.y * width + index;
	return sf::Vector2i(p.x, p.y);
}
