#pragma once
#ifndef _XPLAYER_H_
#define  _XPLAYER_H_

#include <SFML/Graphics.hpp>
#include "Texture/AnimatedSprite.hpp"
#include "Interfaces/States.h"

#define TILESIZE 16

enum ENUM_DIRECTION {
	UP, DOWN, LEFT, RIGHT
};
constexpr float fWalkSpeed = 0.25f;
constexpr float fRunSpeed = 0.2f;
constexpr int nMoveSpeed = 40;


class XEngine;

class XPlayer : public Interfaces::States {
public:
	XPlayer() : nDirection(DOWN), isMoving(false), isRunning(false) {};

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

	sf::Vector2f GetAbsolutePosition();

	sf::Vector2f vCurrentPos;

private:
	// Animation relevant
	AnimatedSprite animatedSprite;
	Animation walkingAnimation[8];
	Animation *currentAnimation;
	sf::Texture texture;
	// Moving relevant
	bool isRunning;
	bool isMoving;
	ENUM_DIRECTION nDirection;

	sf::View m_pPlayerView;
	float fNextSpot;
	sf::Vector2f vPosition, vStartPos;
};

#endif