#pragma once
#ifndef _XENGINE_H_
#define _XENGINE_H_

#include <SFML/Graphics.hpp>
#include "XMap.h"
#include "XPlayer.h"
#include "XBattle.h"
#include "Texture/XSprite.h"
#include "TypeWriter.h"

class XEngine
{
public:
	static XEngine& GetInstance()
	{
		static XEngine    instance; // Guaranteed to be destroyed.
							  // Instantiated on first use.
		return instance;
	}


	void Go();					//Starts the engine
	bool GetAbsoluteCoordinates(sf::Vector2f);
	// Constructor
	XEngine() : m_pSprites() { };
	// Get Sprite class
	XSprite* GetXSprite() { return &m_pSprites; }
private:
	// Map
	XMap m_pMap;
	// Views
	sf::View m_pView, m_pBattleView;

	//SFML Render Window
	sf::RenderWindow* window;
	//Render Window (and Camera) size
	sf::Vector2f videoSize;

	//Initializes the engine
	bool Init();
	//Main Game Loop
	void MainLoop();
	//Renders one frame
	void RenderFrame();
	//Processes user input
	void ProcessInput();
	//Updates all Engine internals
	void Update();
private:
	sf::Font m_pFont;
	Typewriter m_pWriter;
	sf::Clock m_pClock;
	float deltaTime;

	XPlayer m_pPlayer;
	XSprite m_pSprites;
	XBattle m_pBattle;


							  // C++ 11
							  // =======
							  // We can use the better technique of deleting the methods
							  // we don't want.
public:
	XEngine(XEngine const&) = delete;
	void operator=(XEngine const&) = delete;

	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
};
#endif