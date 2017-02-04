#include "XPlayer.h"
#include "XEngine.h"

const float movespeed = 40;

//************************************
// Method:    Init
// FullName:  XPlayer::Init
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: sf::Vector2f pos
//************************************
void XPlayer::Init(sf::Vector2f pos) {
	if (!texture.loadFromFile("data/player_male.png"))
	{
		throw "Could not load player sprite!";
	}

	for (int i = 0; i < 4; ++i) {
		walkingAnimation[i].setSpriteSheet(texture);
		walkingAnimation[i].addFrame(sf::IntRect(16, i * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(0, i * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(16, i * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(32, i * 20, 16, 20));
	}
	for (int i = 4, y = 0; i < 8; ++i, ++y) {
		walkingAnimation[i].setSpriteSheet(texture);
		walkingAnimation[i].addFrame(sf::IntRect(64, y * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(48, y * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(64, y * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(80, y * 20, 16, 20));
	}

	currentAnimation = &walkingAnimation[DOWN];
	animatedSprite = AnimatedSprite(sf::seconds(WALKING_SPEED), true, false);
	animatedSprite.setPosition(pos);
	vPosition = vStartPos = pos;
	vPosition.y -= 28;
}

//************************************
// Method:    Render
// FullName:  XPlayer::Render
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: sf::RenderWindow * window
// Parameter: float dt
//************************************
void XPlayer::Render(sf::RenderWindow* window, float dt) {
	window->draw(animatedSprite);
	animatedSprite.play(*currentAnimation);
	animatedSprite.update(sf::seconds(dt));
}

//************************************
// Method:    Move
// FullName:  XPlayer::Move
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: float dt
//************************************
void XPlayer::Move(float dt)
{
	// Check for all the buttons pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		isRunning = true;
		animatedSprite.setFrameTime(sf::seconds(RUNNING_SPEED / 2));
	}
	else {
		isRunning = false;
		animatedSprite.setFrameTime(sf::seconds(WALKING_SPEED));
	}

	if (!isMoving) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			fNextSpot = vPosition.y + TILESIZE;
			nDirection = UP;
			currentAnimation = &walkingAnimation[isRunning ? UP + 4 : UP];
			if (XEngine::GetInstance().GetAbsoluteCoordinates(sf::Vector2f(vStartPos.x - vPosition.x, vStartPos.y+4 - fNextSpot))) {
				return;
			}
			isMoving = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			fNextSpot = vPosition.y - TILESIZE;
			nDirection = DOWN;
			currentAnimation = &walkingAnimation[isRunning ? DOWN + 4 : DOWN];
			if (XEngine::GetInstance().GetAbsoluteCoordinates(sf::Vector2f(vStartPos.x - vPosition.x, vStartPos.y+4 - fNextSpot))) {
				return;
			}
			isMoving = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			fNextSpot = vPosition.x + TILESIZE;
			nDirection = LEFT;
			currentAnimation = &walkingAnimation[isRunning ? LEFT + 4 : LEFT];
			if (XEngine::GetInstance().GetAbsoluteCoordinates(sf::Vector2f(vStartPos.x - fNextSpot, vStartPos.y +4- vPosition.y))) {
				return;
			}
			isMoving = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			fNextSpot = vPosition.x - TILESIZE;
			nDirection = RIGHT;
			currentAnimation = &walkingAnimation[isRunning ? RIGHT + 4 : RIGHT];
			if (XEngine::GetInstance().GetAbsoluteCoordinates(sf::Vector2f(vStartPos.x - fNextSpot, vStartPos.y+4 - vPosition.y))) {
				return;
			}
			isMoving = true;
		}
	}

	// Do the actual movement
	if (isMoving)
	{
		switch (nDirection) {
		case UP: {
			vPosition.y += movespeed * (isRunning ? 2 : 1) *dt;
			if (vPosition.y >= fNextSpot) {
				vPosition.y = fNextSpot;
				isMoving = false;
				isRunning = false;
			}
		}
			break;
		case DOWN:
			vPosition.y -= movespeed * (isRunning ? 2 : 1) *dt;
			if (vPosition.y <= fNextSpot) {
				vPosition.y = fNextSpot;
				isMoving = false;
				isRunning = false;
			}
			break;
		case LEFT:
			vPosition.x += movespeed * (isRunning ? 2 : 1) *dt;
			if (vPosition.x >= fNextSpot) {
				vPosition.x = fNextSpot;
				isMoving = false;
				isRunning = false;
			}
			break;
		case RIGHT:
			vPosition.x -= movespeed * (isRunning ? 2 : 1) *dt;
			if (vPosition.x <= fNextSpot) {
				vPosition.x = fNextSpot;
				isMoving = false;
				isRunning = false;
			}
			break;
		default:
			break;
		}
	}
	else {
		isRunning = false;
		currentAnimation = &walkingAnimation[nDirection];
		animatedSprite.stop();
	}
}