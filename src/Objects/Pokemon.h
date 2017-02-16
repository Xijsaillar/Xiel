//
// Created by xijezu on 05.02.17.
//

#ifndef POKEMON_XICI_POKEMON_H
#define POKEMON_XICI_POKEMON_H

#include <SFML/Graphics.hpp>
#include "Objects.h"

namespace Objects {
	class Pokemon {
	public:
		// DO. NOT. USE.
		Pokemon() : m_nID(0), m_dType(NORMAL) {};

		Pokemon(int nID, int type) : m_nID(nID), m_dType(type) {};

		~Pokemon() {}

		const int GetID() { return m_nID; }

		static sf::Sprite *GetSprite(int, int);

		sf::Sprite *GetSprite();

	private:
		int m_nID;
		sf::Sprite *m_pSprite;

		int m_dType;
	};
}


#endif //POKEMON_XICI_POKEMON_H
