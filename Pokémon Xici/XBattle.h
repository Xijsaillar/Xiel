#pragma once
#include <SFML/Graphics.hpp>

class XBattle
{
public:
	XBattle();
	~XBattle();
	bool Init();
	void Render(sf::RenderWindow*);

	void InitBattle();

};
