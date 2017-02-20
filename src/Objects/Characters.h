//
// Created by xijezu on 17.02.17.
//

#ifndef POKEMON_XICI_CHARACTERS_H
#define POKEMON_XICI_CHARACTERS_H

#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

constexpr float fWalkSpeed = 0.25f;
constexpr float fRunSpeed = 0.2f;
constexpr int nMoveSpeed = 40;
constexpr int nTileSize = 16;

namespace Objects {

	typedef enum : int {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	} XDirection;

	class Characters {

	public:
		// Don't remove the NPC tag because our Player class is gonna inherit from this one
		Characters() {};

		~Characters() {};

		virtual void UpdateCharacter(float);

		void Move(XDirection);

	public:
		//
		void SetCurrentAnimation(XDirection);

		// Moving relevant
		float fNextSpot;
		sf::Vector2f vPosition, vStartPos, vCurrentPos, vNextPos;
		bool isRunning{false};
		bool isMoving{false};
		Objects::XDirection nDirection{Objects::DOWN};

		// Animations
		AnimatedSprite animatedSprite;
		Animation walkingAnimation[8];
		Animation *currentAnimation;
		sf::Texture m_sfTexture;
	};
}


#endif //POKEMON_XICI_CHARACTERS_H
