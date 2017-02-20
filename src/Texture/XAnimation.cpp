//
// Created by xijezu on 17.02.17.
//

#include "XAnimation.h"

Textures::XAnimation::XAnimation(sf::Texture texture, sf::Vector2f pos) {
	SetTexture(texture, pos);
}

void Textures::XAnimation::SetTexture(sf::Texture texture, sf::Vector2f pos) {
	m_sfTexture = texture;
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setTextureRect({0, 0, 16, 16});
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

void Textures::XAnimation::InitPlay(std::vector<int> frames, sf::Time frameTime) {
	m_sfCurrentTime = sf::Time::Zero;
	m_sfFrameTime = frameTime;
	m_vAniFrames = frames;
	m_bIsPlaying = true;
}

void Textures::XAnimation::Update(sf::Time deltaTime) {
	m_sfCurrentTime += deltaTime;

	// if current time is bigger then the frame time advance one frame
	if (m_sfCurrentTime >= m_sfFrameTime && m_bIsPlaying) {
		// reset time, but keep the remainder
		m_sfCurrentTime = sf::microseconds(m_sfCurrentTime.asMicroseconds() % m_sfFrameTime.asMicroseconds());

		if (nCurrentFrame + 1 < m_vAniFrames.size())
			nCurrentFrame++;
		else
			// animation has ended
			nCurrentFrame = 0;

		SetCurrentFrame(m_vAniFrames[nCurrentFrame]);
	}
}