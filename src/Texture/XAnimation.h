//
// Created by xijezu on 17.02.17.
//

#ifndef POKEMON_XICI_XANIMATION_H
#define POKEMON_XICI_XANIMATION_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace Textures {
	typedef struct {
		int nUp;
		int nDown;
		int nLeft;
		int nRight;

		void BaseFrame(int u, int d, int l, int r) {
			nUp = u;
			nDown = d;
			nLeft = l;
			nRight = r;
		}

	} BaseFrame;

	class XAnimation {
	public:
		XAnimation(sf::Texture, sf::Vector2i);

		void SetBaseFrame(BaseFrame);
		void AddFrame(int idx, std::vector<sf::IntRect>);
		void AddFrame(int,sf::IntRect);
		void AddFrame(int idx,int u,int d,int l,int r) { AddFrame(idx, {u, d, l, r}); }
		void SetCurrentFrame(int);

		sf::Sprite* GetSprite() { return &m_sfSprite; }
	private:
		sf::Texture m_sfTexture;
		sf::Sprite m_sfSprite;
		std::unordered_map<int,sf::IntRect> m_vFrames;
		int nCurrentFrame{0};
		BaseFrame m_bBaseFrame;

	};
}


#endif //POKEMON_XICI_XANIMATION_H
