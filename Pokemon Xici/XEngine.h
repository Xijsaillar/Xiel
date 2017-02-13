#pragma once
#ifndef _XENGINE_H_
#define _XENGINE_H_

#include <SFML/Graphics.hpp>

#include <stack>
#include <memory>

#include "XMap.h"
#include "XPlayer.h"
#include "XBattle.h"
#include "Texture/XSprite.h"
#include "Interfaces/States.h"
#include "TypeWriter.h"

using namespace Interfaces;

class XEngine
{
public:
	static XEngine& GetInstance()
	{
		static XEngine    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}

	// De-constructor
	XEngine(XEngine const &) = delete;

	void operator=(XEngine const &) = delete;


	void Go();					//Starts the engine
	bool GetAbsoluteCoordinates(sf::Vector2f);

	int rdmtest(int);
	// Constructor
	XEngine() : m_pSprites(), m_pMap(new XMap) {};
	// Get Sprite class
	XSprite* GetXSprite() { return &m_pSprites; }

	const std::unique_ptr<XMap> &GetXMap() { return m_pMap; }

	Typewriter *GetTypewriter() { return &m_pWriter; }

	// Stuff used for states
	void PushState(std::unique_ptr<Interfaces::States> pState) { m_sStack.push(std::move(pState)); }

	void PopState() { m_sStack.pop(); }

private:
	//SFML Render Window
	sf::RenderWindow* window;
	//Render Window (and Camera) size
	sf::Vector2u videoSize;

	// Stuff used for states
	std::stack<std::unique_ptr<Interfaces::States>> m_sStack;

	//Initializes the engine
	bool Init();
	//Main Game Loop
	void MainLoop();
	//Processes user input
	void WindowEvents();

	// Everything necessary for the typewriter
	sf::Font m_pFont;
	Typewriter m_pWriter;
	sf::Clock m_pClock;
	float deltaTime;

	// semi-static members
	XPlayer m_pPlayer;
	XSprite m_pSprites;
	XBattle m_pBattle;
	std::unique_ptr<XMap> m_pMap;
};
#endif