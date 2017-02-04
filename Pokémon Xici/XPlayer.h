#pragma once
#ifndef _XPLAYER_H_
#define  _XPLAYER_H_

#include <SFML/Graphics.hpp>
#include "Texture/AnimatedSprite.hpp"
#include "Interfaces/States.h"

#define WALKING_SPEED 0.25f
#define RUNNING_SPEED 0.2f
#define TILESIZE 16

enum ENUM_DIRECTION { UP, DOWN, LEFT, RIGHT };
enum ENUM_SCREEN { GAME, MENU, BATTLE };

class XEngine;

class XPlayer : public Interfaces::States
{
public:
	XPlayer() : nDirection(DOWN), isMoving(false), isRunning(false), nScreen(GAME) { };
	~XPlayer() { };
	void Init(sf::Vector2f);

	void Step(sf::Vector2i pos) {
		vPosition.x += (pos.x * TILESIZE);
		vPosition.y = (pos.y * TILESIZE);
	}

	// For the stack
	void Update(float deltaTime) override;

	void Render(sf::RenderWindow *renderWindow, float deltaTime) override;

	void Input(float deltaTime) override;

	sf::Vector2f GetPosition() const { return vPosition; }
	sf::Vector2f GetAbsolutePosition() const { return sf::Vector2f(vStartPos.x - vPosition.x, (vStartPos.y - vPosition.y)); }
	ENUM_SCREEN GetScreen() { return nScreen; }
	void SetScreen(ENUM_SCREEN screen) { nScreen = screen; }
private:
	// Animation relevant
	AnimatedSprite animatedSprite;
	Animation walkingAnimation[8];
	Animation* currentAnimation;
	sf::Texture texture;
	// Moving relevant
	bool isRunning;
	bool isMoving;
	ENUM_DIRECTION nDirection;
	ENUM_SCREEN nScreen;
	float fNextSpot;
	sf::Vector2f vPosition, vStartPos;
};
#endif