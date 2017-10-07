#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/System/String.hpp>

#include <string>

namespace sfmltemplate
{
	class InputManager;
	class InputProcessor
	{
	public:
		InputProcessor(InputManager* manager);
		~InputProcessor();

		virtual bool processSFMLInput(sf::Event& event);

		virtual void HUDPress(std::string id);
		virtual void HUDRelease(std::string id);

		virtual bool init();

	protected:

		InputManager& inputManager_;
		//TODO : add context functionality, to register different contexts during gameplay
	};
}