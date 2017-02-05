#include "TypeWriter.h"

#include <SFML/Graphics.hpp>

class Typewriter::impl
{
public:

	explicit impl() { };
	void _init(std::string s, sf::Font& f, sf::Uint32 charSize, float timeOffset);
	~impl();

public:

	std::string m_string;
	sf::Text m_text;
	float m_offset;
	sf::Vector2f m_position;
	std::size_t m_itr;
	sf::Clock m_timer;
};

void Typewriter::impl::_init(std::string s, sf::Font& f, sf::Uint32 charSize, float timeOffset) {
	m_text.setString(s);
	m_text.setFont(f);
	m_text.setCharacterSize(charSize);
	m_text.setColor(sf::Color::Black);
	m_string = s;
	m_offset = timeOffset;
	m_itr = 0;
}

Typewriter::impl::~impl()
{

}

void Typewriter::init(std::string s, sf::Font& f, sf::Uint32 charSize, float timeOffset) {
	//m_impl-> new impl();
	m_impl->_init(s, f, charSize, timeOffset);
}

Typewriter::Typewriter() : m_impl(new impl())
{

}

Typewriter::~Typewriter()
{

}

void Typewriter::setCharSize(sf::Uint32 size) {
	m_impl->m_text.setCharacterSize(size);
}

void Typewriter::setColor(sf::Color color) {
	m_impl->m_text.setColor(color);
}

void Typewriter::setString(std::string s)
{
	m_impl->m_string = s;
};

std::string const Typewriter::getString() const
{
	return m_impl->m_string;
};

void Typewriter::setPosition(sf::Vector2f position)
{
	m_impl->m_text.setPosition(position);
};

void Typewriter::reset()
{
	m_impl->m_timer.restart();
	m_impl->m_itr = 0;
	m_impl->m_text.setString("");
};

void Typewriter::write()
{
	//std::cout<<"Writing...."<<std::endl;
	if (m_impl->m_timer.getElapsedTime().asSeconds() > m_impl->m_offset && m_impl->m_itr < m_impl->m_string.size())
	{
		m_impl->m_timer.restart();
		m_impl->m_itr++;

		m_impl->m_text.setString(sf::String(m_impl->m_string.substr(0, m_impl->m_itr)));

		m_impl->m_text.setOrigin(0, 0.f);

		//std::cout<<m_impl->m_string.substr(0, m_impl->m_itr)<<std::endl;
	}
}

void Typewriter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_impl->m_text, states);
}
