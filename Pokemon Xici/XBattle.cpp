#include "XBattle.h"
#include "XEngine.h"

XBattle::~XBattle()
{
}

sf::Sprite *XBattle::GetSprite(int id) {
	return XEngine::GetInstance().GetXSprite()->GetSprite(id);
}

bool XBattle::Init(sf::View pView) {
	m_pBattleView = pView;
	XEngine::GetInstance().GetXSprite()->LoadTexture("data/battlemenu1.png", BATTLE_FRAME + BATTLE_MENU_BIG);
	XEngine::GetInstance().GetXSprite()->SetPosition(BATTLE_FRAME + BATTLE_MENU_BIG, 0, 288);
	XEngine::GetInstance().GetXSprite()->LoadTexture("data/battlemenu2.png", BATTLE_FRAME + BATTLE_MENU_SMALL);
	XEngine::GetInstance().GetXSprite()->SetPosition(BATTLE_FRAME + BATTLE_MENU_SMALL, 275, 290);
	XEngine::GetInstance().GetXSprite()->LoadTexture("data/bm.png", BATTLE_FRAME + BATTLE_BACK_STANDARD);
	XEngine::GetInstance().GetXSprite()->SetPosition(BATTLE_FRAME + BATTLE_BACK_STANDARD, 0, 0);

	return true;
}

void XBattle::InitBattle(Objects::Pokemon player, Objects::Pokemon enemy) {
	m_pPlayer = player;
	m_pEnemy = enemy;

	m_pEnemy.GetSprite()->move(250, 0);
	m_pPlayer.GetSprite()->move(-250, 0);
	bIsInit = true;
}

void XBattle::Render(sf::RenderWindow *renderWindow, float deltaTime) {
	renderWindow->setView(m_pBattleView);
	renderWindow->draw(*GetSprite(BATTLE_FRAME + BATTLE_BACK_STANDARD));
	renderWindow->draw(*GetSprite(BATTLE_FRAME + BATTLE_MENU_BIG));
	renderWindow->draw(*GetSprite(BATTLE_FRAME + BATTLE_MENU_SMALL));

	renderWindow->draw(*m_pPlayer.GetSprite());
	renderWindow->draw(*m_pEnemy.GetSprite());

	if (bIsText) {
		XEngine::GetInstance().GetTypewriter()->write();
		XEngine::GetInstance().GetTypewriter()->draw(*renderWindow, sf::RenderStates::Default);
	}
}

void XBattle::Update(float deltaTime) {
	if (bIsInit) {
		m_pPlayer.GetSprite()->move(175 * deltaTime, 0);
		m_pEnemy.GetSprite()->move(-175 * deltaTime, 0);

		if (m_pEnemy.GetSprite()->getPosition().x <= 300) {
			m_pEnemy.GetSprite()->setPosition(300, 0);
			m_pPlayer.GetSprite()->setPosition(72, 128);
			bIsInit = false;
			SetContactText("A wild Xiel appeared!");
		}
	}
}

void XBattle::Input(float deltaTime) {}

void XBattle::SetContactText(std::string szText) {
	XEngine::GetInstance().GetTypewriter()->reset();

	XEngine::GetInstance().GetTypewriter()->setCharSize(19);
	XEngine::GetInstance().GetTypewriter()->setColor(sf::Color(248, 248, 248));
	XEngine::GetInstance().GetTypewriter()->setPosition(sf::Vector2f(21, 305));
	XEngine::GetInstance().GetTypewriter()->setString(szText);
	bIsText = true;
}