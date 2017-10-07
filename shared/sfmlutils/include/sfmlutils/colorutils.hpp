#pragma once

#include <mutils/color.hpp>
#include <SFML/Graphics/Color.hpp>

namespace sfmlutils
{
	sf::Color toSfColor(const mutils::Color& mutilsColor);
	mutils::Color fromSfColor(const sf::Color& sfmlColor);
}