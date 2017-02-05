
#include <unordered_map>
#include <SFML/Graphics.hpp>

#define MENU_FRAME 0
#define BATTLE_FRAME 16

#define BATTLE_MENU_BIG 0 
#define BATTLE_MENU_SMALL 1
#define BATTLE_BACK_STANDARD 2

#define NUM_POKEMON 152
#define POKEMON_BEGIN 20
#define POKEMON_SHINY_BEGIN int(POKEMON_BEGIN + NUM_POKEMON)
#define POKEMON_BACK_BEGIN POKEMON_SHINY_BEGIN + NUM_POKEMON
#define POKEMON_SHINY_BACK_BEGIN POKEMON_BACK_BEGIN + NUM_POKEMON

#pragma once
class XSprite
{
public:
	XSprite() : m_pSprites(), m_pTextures() { m_pSprites.clear(); m_pTextures.clear(); }
	~XSprite() { }
public:
	bool LoadTileSet(std::string szFile, int scale, int idx);
	bool LoadTexture(std::string szFile, int idx);
	bool LoadPokemon();
	void SetPosition(int idx, float x, float y) { m_pSprites[idx].setPosition(sf::Vector2f(x, y)); }
	sf::Sprite* GetSprite(int idx);

private:
	std::unordered_map<int, sf::Sprite> m_pSprites;
	std::unordered_map<int, sf::Texture> m_pTextures;
};

