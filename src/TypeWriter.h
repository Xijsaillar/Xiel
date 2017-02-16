#ifndef TYPEWRITER_HPP
#define TYPEWRITER_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics/Color.hpp>

namespace sf {
	class Font;

	class RenderTarget;

	class RenderStates;
}

class Typewriter : public sf::Drawable, sf::Transformable {
public:
	explicit Typewriter();

	~Typewriter();

	void init(std::string s, sf::Font &f, sf::Uint32 charSize, float timeOffset);

	void write();

	void reset();

	void setString(std::string s);

	void setCharSize(sf::Uint32 size);

	void setColor(sf::Color color);

	std::string const getString() const;

	void setPosition(sf::Vector2f position);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	class impl;

	std::unique_ptr<impl> m_impl;
};

#endif // TYPEWRITER_HPP
