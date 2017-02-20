//
// Created by xijezu on 17.02.17.
//

#include "Characters.h"
#include "XEngine.h"

void Objects::Characters::UpdateCharacter(float deltaTime) {
	// Do the actual movement
	if (isMoving) {
		switch (nDirection) {
			case UP: {
				vPosition.y += nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.y >= vNextPos.y) {
					vPosition = vNextPos;
					vCurrentPos = vPosition;
					isMoving = false;
					isRunning = false;
				}
			}
				break;
			case DOWN:
				vPosition.y -= nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.y <= vNextPos.y) {
					vPosition = vNextPos;
					vCurrentPos = vPosition;
					isMoving = false;
					isRunning = false;
				}
				break;
			case LEFT:
				vPosition.x += nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.x >= vNextPos.x) {
					vPosition = vNextPos;
					vCurrentPos = vPosition;
					isMoving = false;
					isRunning = false;
				}
				break;
			case RIGHT:
				vPosition.x -= nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.x <= vNextPos.x) {
					vPosition = vNextPos;
					vCurrentPos = vPosition;
					isMoving = false;
					isRunning = false;
				}
				break;
			default:
				break;
		}
	} else {
		isRunning = false;
		currentAnimation = &walkingAnimation[nDirection];
		animatedSprite.stop();
	}
}

void Objects::Characters::Move(XDirection pDirection) {
	nDirection = pDirection;
	switch (nDirection) {
		case UP:
			vNextPos = {vPosition.x, vPosition.y + nTileSize};
			break;
		case DOWN:
			vNextPos = {vPosition.x, vPosition.y - nTileSize};
			break;
		case LEFT:
			vNextPos = {vPosition.x + nTileSize, vPosition.y};
			break;
		case RIGHT:
			vNextPos = {vPosition.x - nTileSize, vPosition.y};
			break;
		default:
			break;
	}
	SetCurrentAnimation(nDirection);
	if (g_XEngine.GetXMap()->isCollision(sf::Vector2i{vStartPos.x - vNextPos.x, vStartPos.y + 4 - vNextPos.y})) {
		vNextPos = vPosition;
	}
	isMoving = true;
}

void Objects::Characters::SetCurrentAnimation(XDirection direction) {
	currentAnimation = &walkingAnimation[isRunning ? direction + 4 : direction];
}