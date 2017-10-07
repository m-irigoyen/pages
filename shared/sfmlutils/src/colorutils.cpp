#include <sfmlutils/colorutils.hpp>


namespace sfmlutils
{
	sf::Color toSfColor(const mutils::Color & mutilsColor)
	{
		sf::Color c;
		int r, g, b, a;
		mutilsColor.getIntValues(r, g, b, a);
		c.r = r;
		c.g = g;
		c.b = b;
		c.a = a;
		return c;
	}
	mutils::Color fromSfColor(const sf::Color & sfmlColor)
	{
		return mutils::Color(sfmlColor.r, sfmlColor.g, sfmlColor.b, sfmlColor.a);
	}
}