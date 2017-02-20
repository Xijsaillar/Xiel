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
		XAnimation() {}

		XAnimation(sf::Texture, sf::Vector2f);

		~XAnimation() {};

		void SetBaseFrame(BaseFrame);
		void AddFrame(int idx, std::vector<sf::IntRect>);
		void AddFrame(int,sf::IntRect);
		void AddFrame(int idx,int u,int d,int l,int r) { AddFrame(idx, {u, d, l, r}); }
		void SetCurrentFrame(int);

		void SetTexture(sf::Texture, sf::Vector2f);

		void Update(sf::Time);

		void InitPlay(std::vector<int>, sf::Time);

		void Stop() { m_bIsPlaying = false; }

		sf::Sprite* GetSprite() { return &m_sfSprite; }
	private:
		sf::Texture m_sfTexture;
		sf::Sprite m_sfSprite;

		std::unordered_map<int,sf::IntRect> m_vFrames;
		std::vector<int> m_vAniFrames;

		int nCurrentFrame{0};
		bool m_bIsPlaying{false};
		BaseFrame m_bBaseFrame;

		sf::Time m_sfCurrentTime, m_sfFrameTime;

	};
}


#endif //POKEMON_XICI_XANIMATION_H
