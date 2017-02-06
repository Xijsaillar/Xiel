//
// Created by xijezu on 05.02.17.
//

#include "Pokemon.h"
#include "../XEngine.h"

namespace Objects {

	sf::Sprite *Pokemon::GetSprite(int type, int id) {
		return XEngine::GetInstance().GetXSprite()->GetSprite(type + id);
	}

	sf::Sprite *Pokemon::GetSprite() {
		return XEngine::GetInstance().GetXSprite()->GetSprite(m_dType + m_nID);
	}


}