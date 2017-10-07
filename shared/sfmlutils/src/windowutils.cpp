#include <sfmlutils/windowutils.hpp>

namespace sfmlutils
{
	ScopedViewContext::ScopedViewContext(sf::RenderWindow & window, const sf::View & view)
		: window_(window)
		, previousView_(window_.getView())
	{
		window_.setView(view);
	}

	ScopedViewContext::~ScopedViewContext()
	{
		window_.setView(previousView_);
	}
}