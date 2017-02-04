#pragma once
#include <SFML/Graphics.hpp>
#include "Interfaces/States.h"


class XBattle : public Interfaces::States
{
public:
	XBattle();
	~XBattle();

	bool Init(sf::View);

	void Render(sf::RenderWindow *, float) override;

	void Input(float) override;

	void Update(float) override;

	void InitBattle();

private:
	sf::View m_pBattleView;

};
