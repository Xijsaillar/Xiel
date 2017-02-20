//
// Created by xijezu on 17.02.17.
//

#include "XAnimation.h"

Textures::XAnimation::XAnimation(sf::Texture texture, sf::Vector2i pos) {
	m_sfTexture = texture;
	m_sfSprite.setTexture(texture);
	m_sfSprite.setPosition(pos);
}

void Textures::XAnimation::AddFrame(int idx, std::vector<sf::IntRect> vList) {
	for(auto it : vList) {
		m_vFrames[idx++] = it;
	}
}

void Textures::XAnimation::AddFrame(int idx, sf::IntRect rect) {
	m_vFrames[idx] = rect;
}

void Textures::XAnimation::SetBaseFrame(BaseFrame frame) {
	m_bBaseFrame = frame;
}

void Textures::XAnimation::SetCurrentFrame(int idx) {
	if(idx >= m_vFrames.size())
		return;
	m_sfSprite.setTextureRect(m_vFrames[idx]);
}