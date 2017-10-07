#include <sfmltemplate/core/inputprocessor.hpp>

#include <sfmltemplate/core/inputmanager.hpp>

#include <mutils/assert.hpp>

namespace sfmltemplate
{
	InputProcessor::InputProcessor(InputManager * manager)
		: inputManager_(*manager)
	{
	}
	InputProcessor::~InputProcessor()
	{
	}
	bool InputProcessor::processSFMLInput(sf::Event & event)
	{
		if (inputManager_.isTextCapturing())
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					inputManager_.endTextCapture();
					return true;
				case sf::Keyboard::BackSpace:
					inputManager_.registerTextCaptureBackspace();
					return true;
				case sf::Keyboard::Escape:
					inputManager_.cancelTextCapture();
					return true;
				}
			}
			else if (event.type == sf::Event::TextEntered)
			{
				inputManager_.registerTextCaptureCharacter(event.text.unicode);
			}
		}
		else
		{
			if ((event.type == sf::Event::MouseButtonPressed)
				|| (event.type == sf::Event::MouseButtonReleased))
			{
				std::string id;
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					id = "touch";
					break;
				/*case sf::Mouse::Right:
					id = "touch";
					break;*/
				default:
					return false;
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					inputManager_.onButtonPress(id);
				}
				else
				{
					inputManager_.onButtonRelease(id);
				}
				return true;
			}
		}
		return false;
	}

	void InputProcessor::HUDPress(std::string id)
	{
		inputManager_.onButtonPress(id);
	}
	void InputProcessor::HUDRelease(std::string id)
	{
		inputManager_.onButtonRelease(id);
	}
	bool InputProcessor::init()
	{
		return true;
	}
}