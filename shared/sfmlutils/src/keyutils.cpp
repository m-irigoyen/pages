#include <sfmlutils/keyutils.hpp>

namespace sfmlutils
{
	bool isAnyControlPressed()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
	}

	bool isAnyShiftPressed()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	}

	bool isAnyAltPressed()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
	}

	bool isLAltPressed()
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt);
	}
}