#pragma once

#include <SFML/Graphics.hpp>
#include "Interfaces/States.h"
#include "Objects/Pokemon.h"

class Typewriter;

class XBattle : public Interfaces::States {
public:
	XBattle() { bIsInit = false; };

	~XBattle();

	bool Init(sf::View);

	void Render(sf::RenderWindow *, float) override;

	void Input(float) override;

	void Update(float) override;

	void InitBattle(Objects::Pokemon player, Objects::Pokemon enemy);

	void SetContactText(std::string);

private:
	sf::View m_pBattleView;
	bool bIsInit;
	bool bIsText;

	Objects::Pokemon m_pPlayer, m_pEnemy;

	sf::Sprite *GetSprite(int id);
};
