#include <sfmlutils/vectorutils.hpp>

namespace sfmlutils
{
	mutils::Vec2 sfToVec2(const sf::Vector2f & v)
	{
		return mutils::Vec2(v.x, v.y);
	}
	mutils::Vec2 sfToVec2(const sf::Vector2i & v)
	{
		return mutils::Vec2((float)v.x, (float)v.y);
	}
	mutils::Vec2 sfToVec2(const sf::Vector2u & v)
	{
		return mutils::Vec2((float)v.x, (float)v.y);
	}
	sf::Vector2f vec2ToSf(const mutils::Vec2 & v)
	{
		return sf::Vector2f(v.x, v.y);
	}
}