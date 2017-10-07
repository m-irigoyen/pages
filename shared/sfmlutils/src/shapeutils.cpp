#include <sfmlutils/shapeutils.hpp>
#include <math.h>

namespace sfmlutils
{
	void setOriginToCenter(sf::Shape& shape)
	{
		sf::FloatRect bounds = shape.getLocalBounds();
		shape.setOrigin(bounds.left + bounds.width / 2
			, bounds.top + bounds.height / 2);
	}

	void setOriginToCenter(sf::Text& text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + (bounds.width / 2.0f)
			, bounds.top + (bounds.height /2.0f));
	}

	void setOriginToCenter(sf::Sprite & sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.left + (bounds.width / 2.0f)
			, bounds.top + (bounds.height / 2.0f));
	}

	float length(const sf::Vector2f& v)
	{
		return sqrt(v.x*v.x + v.y*v.y);
	}

	sf::Vector2f normalized(const sf::Vector2f& v)
	{
		float l = length(v);
		return sf::Vector2f(v.x / l, v.y / l);
	}
}