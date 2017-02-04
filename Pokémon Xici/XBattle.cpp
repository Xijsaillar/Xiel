#include "XBattle.h"
#include "Texture/XSprite.h"
#include "XEngine.h"

XBattle::XBattle()
{
}


XBattle::~XBattle()
{
}

bool XBattle::Init() {
	XEngine::GetInstance().GetXSprite()->LoadTexture("data/battlemenu1.png", BATTLE_FRAME + BATTLE_MENU_BIG);
	XEngine::GetInstance().GetXSprite()->SetPosition(BATTLE_FRAME + BATTLE_MENU_BIG, 0, 288);
	XEngine::GetInstance().GetXSprite()->LoadTexture("data/battlemenu2.png", BATTLE_FRAME + BATTLE_MENU_SMALL);
	XEngine::GetInstance().GetXSprite()->SetPosition(BATTLE_FRAME + BATTLE_MENU_SMALL, 275, 290);
	XEngine::GetInstance().GetXSprite()->LoadTexture("data/bm.png", BATTLE_FRAME + BATTLE_BACK_STANDARD);
	XEngine::GetInstance().GetXSprite()->SetPosition(BATTLE_FRAME + BATTLE_BACK_STANDARD, 0, 0);

	return true;
}

void XBattle::Render(sf::RenderWindow* window) {
 	window->draw(*XEngine::GetInstance().GetXSprite()->GetSprite(BATTLE_FRAME + BATTLE_BACK_STANDARD));
 	window->draw(*XEngine::GetInstance().GetXSprite()->GetSprite(BATTLE_FRAME + BATTLE_MENU_BIG));
 	window->draw(*XEngine::GetInstance().GetXSprite()->GetSprite(BATTLE_FRAME + BATTLE_MENU_SMALL));

 	window->draw(*XEngine::GetInstance().GetXSprite()->GetSprite(POKEMON_SHINY_BEGIN + 38));
 	window->draw(*XEngine::GetInstance().GetXSprite()->GetSprite(POKEMON_SHINY_BACK_BEGIN + 38));
}