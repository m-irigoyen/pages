#pragma once

#include <SFML/Graphics/Sprite.hpp>

namespace sfmlutils
{
	//! Returns true if sprite is flipped
	bool isFlipped(sf::Sprite* sprite);

	//! Flips given sprite horizontally
	void flipHorizontal(sf::Sprite* sprite);

	void setFlipHorizontal(sf::Sprite* sprite, bool flip);
}