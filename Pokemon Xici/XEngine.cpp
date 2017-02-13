#include "XEngine.h"
#include <random>

bool XEngine::Init() {
	videoSize = sf::Vector2u(512, 384);
	window = new sf::RenderWindow({videoSize.x, videoSize.y}, "Pokemon Xici");
	window->setFramerateLimit(60);

	if (!m_pFont.loadFromFile("data/pkmnfl.ttf"))
		return false;

	if (!m_pBattle.Init(window->getDefaultView()))
		return false;

	if (!m_pSprites.LoadPokemon())
		return false;

	m_pWriter.init("Init...", m_pFont, 16, 0.025);
	m_pWriter.setPosition(sf::Vector2f(17, 316));
	
	if (!window)
		return false;

	m_pSprites.LoadTexture("data/textskin.png", MENU_FRAME);

	// Init the other classes
	m_pMap->Init(*this);
	m_pMap->LoadMapFromFile("data/xiel_test.prmp");
	m_pPlayer.Init(sf::Vector2f(videoSize.x / 2, videoSize.y / 2), window->getDefaultView());
	m_pPlayer.Step(sf::Vector2i(-4, 0));

	PushState(std::make_unique<XPlayer>(m_pPlayer));
	srand((uint) time(NULL));

	return true;
}

bool XEngine::GetAbsoluteCoordinates(sf::Vector2f vector) {
	return m_pMap->isCollision(vector);
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
		window->clear(sf::Color::Black);
		m_sStack.top()->Input(deltaTime);
		m_sStack.top()->Render(window, deltaTime);
		m_sStack.top()->Update(deltaTime);

		WindowEvents();
		deltaTime = m_pClock.restart().asSeconds();
		window->display();
	}
}

int XEngine::rdmtest(int i) {
	switch (i) {
		case 0:
			return POKEMON_BEGIN;
		case 1:
			return POKEMON_SHINY_BEGIN;
		case 2:
			return POKEMON_BACK_BEGIN;
		case 3:
			return POKEMON_SHINY_BACK_BEGIN;
		default:
			return POKEMON_BACK_BEGIN;
	}
}

void XEngine::WindowEvents()
{
	sf::Event evt;
	while (window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			window->close();

		if (evt.type == sf::Event::KeyPressed) {
			if (evt.key.code == sf::Keyboard::C) {
				Objects::Pokemon player(rand() % 151 + 1, rdmtest(rand() % 2 + 2));
				Objects::Pokemon enemy(rand() % 151 + 1, rdmtest(rand() % 2));
				m_pBattle.InitBattle(player, enemy);
				PushState(std::make_unique<XBattle>(m_pBattle));
			}
			if (evt.key.code == sf::Keyboard::W) {
				PopState();
			}
		}
	}


}