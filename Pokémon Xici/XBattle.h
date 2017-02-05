#pragma once
#include <SFML/Graphics.hpp>
#include "Interfaces/States.h"
#include "Objects/Pokemon.h"
#include <iostream>

class XBattle : public Interfaces::States
{
public:
	XBattle() { bIsInit = false; };
	~XBattle();

	bool Init(sf::View);

	void Render(sf::RenderWindow *, float) override;

	void Input(float) override;

	void Update(float) override;

	void InitBattle(Objects::Pokemon player, Objects::Pokemon enemy);

private:
	sf::View m_pBattleView;
	bool bIsInit;

	Objects::Pokemon m_pPlayer, m_pEnemy;

	sf::Sprite *GetSprite(int id);
};
