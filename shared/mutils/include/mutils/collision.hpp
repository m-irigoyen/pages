#pragma once

#include <mutils/vec2.hpp>

namespace mutils
{
	bool isInAABB(Vec2 p, float left, float top, float width, float height);
	bool isInAABB(Vec2 p, Vec2 aabbTopLeft, Vec2 aabbBottomRight);

	bool isInCircle(Vec2 p, Vec2 center, float radius);
}
