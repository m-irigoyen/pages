#include <mutils/collision.hpp>

namespace mutils
{
	bool isInAABB(Vec2 p, float left, float top, float width, float height)
	{
		return isInAABB(p, Vec2(left, top), Vec2(left + width, top + height));
	}
	bool isInAABB(Vec2 p, Vec2 aabbTopLeft, Vec2 aabbBottomRight)
	{
		// Changing coordinates so that aabtopleft is 0,0
		aabbBottomRight -= aabbTopLeft;
		p -= aabbTopLeft;
		return (p.x >= 0) && (p.y >= 0) && (p.x <= aabbBottomRight.x) && (p.y <= aabbBottomRight.y);
	}

	bool isInCircle(Vec2 p, Vec2 center, float radius)
	{
		// TODO : assert radius >= 0
		return (center - p).length() <= radius;
	}
}
