#include <sfmlutils/spriteutils.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace sfmlutils
{
	bool isFlipped(sf::Sprite * sprite)
	{
		if (sprite)
		{
			return sprite->getTextureRect().width < 0;
		}
		else
		{
			return false;
		}
	}

	void flipHorizontal(sf::Sprite * sprite)
	{
		if (sprite)
		{
			sf::Vector2u size = sprite->getTexture()->getSize();
			sf::IntRect rect = sprite->getTextureRect();

			sf::IntRect res = rect;
			res.left += res.width;
			res.width *= -1;
			sprite->setTextureRect(res);
		}
	}
	void setFlipHorizontal(sf::Sprite* sprite, bool flip)
	{
		if (sprite)
		{
			if (isFlipped(sprite) != flip)
			{
				flipHorizontal(sprite);
			}
		}
	}
}
