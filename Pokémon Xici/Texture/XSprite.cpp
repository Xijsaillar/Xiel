#include "XSprite.h"
#include <iomanip>

bool XSprite::LoadTileSet(std::string szFile, int scale, int idx) {
	
	sf::Texture texture;
	if (!texture.loadFromFile(szFile))
		return false;

	m_pTextures[idx] = texture;

	for (int x = 0; x < texture.getSize().x; x += scale) {
		for (int y = 0; y < texture.getSize().y; y += scale) {
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(x, y, scale, scale));
			m_pSprites[idx] = sprite;
			idx++;
		}
	}

	return true;
}

bool XSprite::LoadPokemon() {
	for (int i = 0; i < NUM_POKEMON; i++) {
		std::string buffer  = "data/Battlers/" + std::string(3 - std::to_string(i).length(), '0') + std::to_string(i) + ".png";

		if (!LoadTexture(buffer, POKEMON_BEGIN + i))
			throw buffer;
		m_pSprites[POKEMON_BEGIN + i].setPosition(300, 0);
	}

	for (int i = 0; i < NUM_POKEMON; i++) {
		std::string buffer =  "data/Battlers/" + std::string(3 - std::to_string(i).length(), '0') + std::to_string(i) + "b.png";

		if (!LoadTexture(buffer, POKEMON_BACK_BEGIN + i))
			throw buffer;
		m_pSprites[POKEMON_BACK_BEGIN + i].setPosition(72, 128);
	}

	for (int i = 0; i < NUM_POKEMON; i++) {
		std::string buffer = "data/Battlers/" + std::string(3 - std::to_string(i).length(), '0') + std::to_string(i) + "s.png";

		if (!LoadTexture(buffer, POKEMON_SHINY_BEGIN + i))
			throw buffer;
		m_pSprites[POKEMON_SHINY_BEGIN + i].setPosition(300, 0);
	}

	for (int i = 0; i < NUM_POKEMON; i++) {
		std::string buffer = "data/Battlers/" + std::string(3 - std::to_string(i).length(), '0') + std::to_string(i) + "sb.png";

		if (!LoadTexture(buffer, POKEMON_SHINY_BACK_BEGIN + i))
			throw buffer;
		m_pSprites[POKEMON_SHINY_BACK_BEGIN + i].setPosition(72, 128);
	}
	return true;
}

bool XSprite::LoadTexture(std::string szFile, int idx) {
	sf::Texture texture;
	if (!texture.loadFromFile(szFile))
		return false;

	m_pTextures[(int)idx] = texture;

	sf::Sprite sprite;
	sprite.setTexture(m_pTextures[idx]);
	sprite.setPosition(0, 304);
	m_pSprites[idx] = sprite;
	return true;
}

sf::Sprite* XSprite::GetSprite(int idx) {
	return &m_pSprites[idx];
}