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
	if (!m_sfTexture.loadFromFile("data/player_male.png")) {
		throw "Could not load player tileSprite!";
	}

	for (int i = 0; i < 4; ++i) {
		walkingAnimation[i].setSpriteSheet(m_sfTexture);
		walkingAnimation[i].addFrame(sf::IntRect(16, i * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(0, i * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(16, i * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(32, i * 20, 16, 20));

	}
	for (int i = 4, y = 0; i < 8; ++i, ++y) {
		walkingAnimation[i].setSpriteSheet(m_sfTexture);
		walkingAnimation[i].addFrame(sf::IntRect(64, y * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(48, y * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(64, y * 20, 16, 20));
		walkingAnimation[i].addFrame(sf::IntRect(80, y * 20, 16, 20));
	}

	currentAnimation = &walkingAnimation[Objects::DOWN];
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
	XEngine::GetInstance().GetXMap()->Render(renderWindow, vPosition, deltaTime);

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
			Move(Objects::UP);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			Move(Objects::DOWN);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			Move(Objects::LEFT);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			Move(Objects::RIGHT);
		}
	}
}

void XPlayer::Update(float deltaTime) {
	// Do the actual movement
	UpdateCharacter(deltaTime);
	g_XEngine.GetXMap()->Update(deltaTime);
}