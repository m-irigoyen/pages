#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

#include <sfmlutils/shapeutils.hpp>

namespace sfmlutils
{
	class NamedPoint
	{
	public:
		NamedPoint(sf::String n, const sf::Font& font, sf::Color fill, sf::Color out);

		void setPosition(const sf::Vector2f& pos);

		void draw(sf::RenderWindow* window);

		sf::CircleShape circle;
		sf::Text name;
	};
}