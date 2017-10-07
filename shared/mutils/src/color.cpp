#include <mutils/color.hpp>

#include <cmath>

namespace mutils
{
	Color::Color(float r, float g, float b, float a)
	{
		setFromFloat(r, g, b, a);
	}
	Color::Color(int r, int g, int b, int a)
	{
		setFromInt(r, g, b, a);
	}
	void Color::setFromFloat(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	void Color::setFromInt(int red, int green, int blue, int alpha)
	{
		r = red / 255.f;
		g = green / 255.f;
		b = blue / 255.f;
		a = alpha / 255.f;
	}
	void Color::getIntValues(int & red, int & green, int & blue, int & alpha) const
	{
		red = (int)round(r * 255.f);
		green = (int)round(g * 255.f);
		blue = (int)round(b * 255.f);
		alpha = (int)round(a * 255.f);
	}
}