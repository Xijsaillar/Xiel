//
// Created by xijezu on 05.02.17.
//

#ifndef POKEMON_XICI_OBJECTS_H
#define POKEMON_XICI_OBJECTS_H

#include "../Texture/XSprite.h"

namespace Objects {
	enum APPEARANCE_TYPE : int {
		NORMAL = POKEMON_BEGIN,
		NORMAL_BACK = POKEMON_BACK_BEGIN,
		SHINY = POKEMON_SHINY_BEGIN,
		SHINY_BACK = POKEMON_SHINY_BACK_BEGIN
	};
}


struct KeyHasher {
	std::size_t operator()(const sf::Vector2i &k) const {
		using std::size_t;
		using std::hash;
		using std::string;

		return ((hash<int>()(k.x)
				 ^ (hash<int>()(k.y) << 1)) >> 1);
	}
};


#endif //POKEMON_XICI_OBJECTS_H
