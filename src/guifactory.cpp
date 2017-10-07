#include "guifactory.hpp"

#include "pathmanager.hpp"
#include "resourcemanager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace pages
{
	GuiFactory::GuiFactory(sfmltemplate::ResourceManager* resourceManager)
		: sfmltemplate::GuiFactory(resourceManager)
	{

	}

	std::unique_ptr<PushButton> GuiFactory::makePushButton() const
	{
		std::unique_ptr<PushButton> button(new PushButton);
		button->getText()->setFont(resourceManager_.getFont(ResourceManager::Fonts::monofonto));
		button->getText()->setFillColor(sf::Color(255, 255, 255, 255));
		button->setShapeSizeToContentSize();
		return button;
	}
}