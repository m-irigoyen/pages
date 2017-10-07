#pragma once

#include <mutils/vec2.hpp>

#include <SFML/System/Vector2.hpp>

namespace sfmlutils
{
	// Convert a sfml vector to a mutils vector
	mutils::Vec2 sfToVec2(const sf::Vector2f& v);
	mutils::Vec2 sfToVec2(const sf::Vector2i& v);
	mutils::Vec2 sfToVec2(const sf::Vector2u& v);
	// Convert a mutils vector to a sfml vector
	sf::Vector2f vec2ToSf(const mutils::Vec2& v);
}