#include "XEngine.h"

bool XEngine::Init() {
	videoSize = sf::Vector2f(512, 384);
	window = new sf::RenderWindow(sf::VideoMode((unsigned int) videoSize.x, (unsigned int) videoSize.y),
								  "Pokemon Xici");
	window->setFramerateLimit(60);

	if (!m_pFont.loadFromFile("data/test.ttf"))
		return false;

	if (!m_pBattle.Init())
		return false;

	if (!m_pSprites.LoadPokemon())
		return false;

	m_pWriter.init("Init...", m_pFont, 16, 0.05);
	m_pWriter.setPosition(sf::Vector2f(17, 316));
	
	if (!window)
		return false;

	// Setup the view we're using
	m_pView = m_pBattleView = window->getDefaultView();
	m_pView.zoom(0.5);
	window->setView(m_pView);

	m_pSprites.LoadTexture("data/textskin.png", MENU_FRAME);

	// Init the other classes
	m_pMap.Init(*this);
	m_pMap.LoadMapFromFile("data/xiel_test.prmp");
	m_pPlayer.Init(sf::Vector2f(videoSize.x / 2, videoSize.y / 2));
	m_pPlayer.Step(sf::Vector2i(-5, 0));

	return true;
}

bool XEngine::GetAbsoluteCoordinates(sf::Vector2f vector) {
	return m_pMap.isCollision(vector);
}

void XEngine::RenderFrame() {
	// Clear the window so we can draw on a blank screen
	window->clear();

	// Do all the rendering
	if (m_pPlayer.GetScreen() == GAME) {
		window->setView(m_pView);
		m_pMap.Render(window, m_pPlayer.GetPosition());
		m_pPlayer.Render(window, deltaTime);
	}
	
	if (m_pPlayer.GetScreen() == MENU) {
		window->setView(window->getDefaultView());
		window->draw(*m_pSprites.GetSprite(MENU_FRAME));
		m_pWriter.setString("You've been to the wrong gitbourhood, motherfucker!");
		m_pWriter.write();
		m_pWriter.draw(*window, sf::RenderStates::Default);
	}

	if (m_pPlayer.GetScreen() == BATTLE) {
		window->setView(m_pBattleView);
		m_pBattle.Render(window);
	}
	// Display final results
	window->display();
}

void XEngine::Go()
{
	if (!Init())
		throw "Could not initialize Engine";

	MainLoop();
}

void XEngine::MainLoop()
{
	//Loop until our window is closed
	while (window->isOpen())
	{
		ProcessInput();
		RenderFrame();
		// Reset Clock
		deltaTime = m_pClock.restart().asSeconds();
	}
}

void XEngine::ProcessInput()
{
	sf::Event evt;
	while (window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			window->close();
		if (evt.type == sf::Event::KeyPressed) {
			if (evt.key.code == sf::Keyboard::C) {
				if (m_pPlayer.GetScreen() == MENU)
					m_pPlayer.SetScreen(GAME);
				else
					m_pPlayer.SetScreen(MENU);
			}
		}
	}

	if(m_pPlayer.GetScreen() == GAME)
		m_pPlayer.Move(deltaTime);

}