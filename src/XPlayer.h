#pragma once
#ifndef _XPLAYER_H_
#define  _XPLAYER_H_

#include <SFML/Graphics.hpp>
#include "Objects/Characters.h"
#include "Texture/AnimatedSprite.hpp"
#include "Interfaces/States.h"

#define TILESIZE 16


class XEngine;

class XPlayer : public Interfaces::States, public Objects::Characters {
public:
	XPlayer() {};

	~XPlayer() {};

	void Init(sf::Vector2f, sf::View);

	void SetRelativePosition(sf::Vector2i pos) {
		vPosition.x += (pos.x * TILESIZE);
		vPosition.y += (pos.y * TILESIZE);
	}

	// For the stack
	void Update(float deltaTime) override;

	void Render(sf::RenderWindow *renderWindow, float deltaTime) override;

	void Input(float deltaTime) override;

	sf::Vector2f GetRelativePosition();

private:
	sf::View m_pPlayerView;
};

#endif