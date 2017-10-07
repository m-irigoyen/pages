#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace sfmlutils
{
	class ScopedViewContext
	{
	public :
		ScopedViewContext(sf::RenderWindow& window, const sf::View& view);
		~ScopedViewContext();

		ScopedViewContext(const ScopedViewContext&) = delete;
		void operator=(const ScopedViewContext&) = delete;
	private:
		sf::RenderWindow& window_;
		const sf::View previousView_;
	};
}