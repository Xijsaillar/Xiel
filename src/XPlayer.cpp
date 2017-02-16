#include "XPlayer.h"
#include "XEngine.h"

//************************************
// Method:    Init
// FullName:  XPlayer::Init
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: sf::Vector2f pos
//************************************
//
void XPlayer::Init(sf::Vector2f pos, sf::View pView) {
	m_pPlayerView = pView;
	m_pPlayerView.zoom(0.5);
	if (!texture.loadFromFile("data/player_male.png")) {
		throw "Could not load player tileSprite!";
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
	animatedSprite = AnimatedSprite(sf::seconds(fWalkSpeed), true, false);
	animatedSprite.setPosition(pos);
	vPosition = vStartPos = vCurrentPos = pos;
	vPosition.y += 4;
	vCurrentPos.y += 4;
}

sf::Vector2f XPlayer::GetRelativePosition() {
	return {vStartPos.x - vCurrentPos.x, vStartPos.y - vCurrentPos.y + 4};
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
void XPlayer::Render(sf::RenderWindow *renderWindow, float deltaTime) {

	renderWindow->setView(m_pPlayerView);
	XEngine::GetInstance().GetXMap()->Render(renderWindow, vPosition);

	renderWindow->draw(animatedSprite);
	animatedSprite.play(*currentAnimation);
	animatedSprite.update(sf::seconds(deltaTime));
}

//************************************
// Method:    Move
// FullName:  XPlayer::Input
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: float dt
//************************************
void XPlayer::Input(float deltaTime) {
	// Check for all the buttons pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		isRunning = true;
		animatedSprite.setFrameTime(sf::seconds(fRunSpeed / 2));
	} else {
		isRunning = false;
		animatedSprite.setFrameTime(sf::seconds(fWalkSpeed));
	}

	if (!isMoving) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			fNextSpot = vPosition.y + TILESIZE;
			nDirection = UP;
			currentAnimation = &walkingAnimation[isRunning ? UP + 4 : UP];
			if (g_XEngine.GetXMap()->isCollision(
					{(int) (vStartPos.x - vPosition.x), (int) (vStartPos.y + 4 - fNextSpot)})) {
				return;
			}
			isMoving = true;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			fNextSpot = vPosition.y - TILESIZE;
			nDirection = DOWN;
			currentAnimation = &walkingAnimation[isRunning ? DOWN + 4 : DOWN];
			if (g_XEngine.GetXMap()->isCollision(
					{(int) (vStartPos.x - vPosition.x), (int) (vStartPos.y + 4 - fNextSpot)})) {
				return;
			}
			isMoving = true;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			fNextSpot = vPosition.x + TILESIZE;
			nDirection = LEFT;
			currentAnimation = &walkingAnimation[isRunning ? LEFT + 4 : LEFT];
			if (g_XEngine.GetXMap()->isCollision(
					{(int) (vStartPos.x - fNextSpot), (int) (vStartPos.y + 4 - vPosition.y)})) {
				return;
			}
			isMoving = true;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			fNextSpot = vPosition.x - TILESIZE;
			nDirection = RIGHT;
			currentAnimation = &walkingAnimation[isRunning ? RIGHT + 4 : RIGHT];
			if (g_XEngine.GetXMap()->isCollision(
					{(int) (vStartPos.x - fNextSpot), (int) (vStartPos.y + 4 - vPosition.y)})) {
				return;
			}
			isMoving = true;
		}
	}

	// Do the actual movement
	if (isMoving) {
		switch (nDirection) {
			case UP: {
				vPosition.y += nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.y >= fNextSpot) {
					vPosition.y = fNextSpot;
					vCurrentPos = vPosition;
					isMoving = false;
					isRunning = false;
				}
			}
				break;
			case DOWN:
				vPosition.y -= nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.y <= fNextSpot) {
					vPosition.y = fNextSpot;
					vCurrentPos = vPosition;
					isMoving = false;
					isRunning = false;
				}
				break;
			case LEFT:
				vPosition.x += nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.x >= fNextSpot) {
					vPosition.x = fNextSpot;
					vCurrentPos = vPosition;
					isMoving = false;
					isRunning = false;
				}
				break;
			case RIGHT:
				vPosition.x -= nMoveSpeed * (isRunning ? 2 : 1) * deltaTime;
				if (vPosition.x <= fNextSpot) {
					vPosition.x = fNextSpot;
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

void XPlayer::Update(float deltaTime) {
	g_XEngine.GetXMap()->Update();
}