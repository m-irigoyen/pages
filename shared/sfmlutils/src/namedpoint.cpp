#include <sfmlutils/namedpoint.hpp>

namespace sfmlutils
{
	NamedPoint::NamedPoint(sf::String n, const sf::Font & font, sf::Color fill, sf::Color out)
	{
		circle.setRadius(10);
		circle.setOutlineColor(out);
		circle.setOutlineThickness(1.f);
		circle.setFillColor(fill);

		name.setFont(font);
		name.setString(n);
		name.setFillColor(out);
		name.setCharacterSize(20);

		sfmlutils::setOriginToCenter(circle);
		sfmlutils::setOriginToCenter(name);
	}
	void NamedPoint::setPosition(const sf::Vector2f & pos)
	{
		circle.setPosition(pos);
		name.setPosition(pos);
	}
	void NamedPoint::draw(sf::RenderWindow * window)
	{
		window->draw(circle);
		window->draw(name);
	}
}