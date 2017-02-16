#include "XEngine.h"
#include <random>

bool XEngine::Init() {
	videoSize = sf::Vector2u{512, 384};
	window = new sf::RenderWindow{{videoSize.x, videoSize.y}, "Xici"};

	if (!m_pFont.loadFromFile("data/pkmnfl.ttf"))
		return false;

	if (!m_pBattle->Init(window->getDefaultView()))
		return false;

	if (!m_pSprites.LoadPokemon())
		return false;

	m_pWriter.init("Init...", m_pFont, 16, 0.025);
	m_pWriter.setPosition({17, 316});

	if (!window)
		return false;

	m_pSprites.LoadTexture("data/textskin.png", MENU_FRAME);

	// Init the other classes
	m_pMap->Init();
	m_pMap->LoadMapFromFile("data/xiel_test.prmp", 0, 0);
	m_pMap->LoadMapFromFile("data/xiel_test.prmp", 640, 0);
	m_pPlayer->Init({videoSize.x / 2.0f, videoSize.y / 2.0f}, window->getDefaultView());
	m_pPlayer->SetRelativePosition({-4, 0});

	m_pState = m_pPlayer.get();
	srand((uint) time(NULL));

	return true;
}

void XEngine::Go() {
	if (!Init())
		throw "Could not initialize Engine";

	MainLoop();
}

void XEngine::MainLoop() {
	//Loop until our window is closed
	while (window->isOpen()) {
		window->clear(sf::Color::Black);
		m_pState->Input(deltaTime);
		m_pState->Render(window, deltaTime);
		m_pState->Update(deltaTime);

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

void XEngine::WindowEvents() {
	sf::Event evt;
	while (window->pollEvent(evt)) {
		if (evt.type == sf::Event::Closed)
			window->close();

		if (evt.type == sf::Event::KeyPressed) {
			if (evt.key.code == sf::Keyboard::C) {
				Objects::Pokemon player(rand() % 151 + 1, rdmtest(rand() % 2 + 2));
				Objects::Pokemon enemy(rand() % 151 + 1, rdmtest(rand() % 2));
				m_pBattle->InitBattle(player, enemy);
				m_pState = m_pBattle.get();
			}
			if (evt.key.code == sf::Keyboard::W) {
				m_pState = m_pPlayer.get();
			}
			if (evt.key.code == sf::Keyboard::P) {
				std::cout << "Currently at absolute " << m_pPlayer->GetRelativePosition().x << "X : "
						  << m_pPlayer->GetRelativePosition().y << "Y" << std::endl;
			}
			if (evt.key.code == sf::Keyboard::D) {
				m_pMap->SetDebug();
			}
		}
	}


}