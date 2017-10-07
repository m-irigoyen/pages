#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sfmlutils
{
	void setOriginToCenter(sf::Shape& shape);
	void setOriginToCenter(sf::Text& text);
	void setOriginToCenter(sf::Sprite& sprite);
	float length(const sf::Vector2f& v);
	sf::Vector2f normalized(const sf::Vector2f& v);
}