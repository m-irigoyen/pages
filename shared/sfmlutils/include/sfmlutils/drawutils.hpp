#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace sfmlutils
{
	void drawFullScreenQuad(sf::RenderWindow& window
		, const sf::Shader& shader);
}
