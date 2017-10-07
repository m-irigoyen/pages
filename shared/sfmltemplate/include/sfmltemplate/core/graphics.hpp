#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sfmltemplate
{
	class ResourceManager;
	class StateManager;
	class Graphics
	{
	public:
		Graphics(ResourceManager* resourceManager, StateManager* stateManager);
		~Graphics();

		virtual sf::RenderWindow& getWindow();

		virtual bool init(std::string appName = "");

		virtual bool isWindowOpened() const;

		virtual void resizeWindow(int width, int height);

	protected:
		std::string appName_;
		ResourceManager& resourceManager_;
		StateManager& stateManager_;

		sf::RenderWindow* window_;

	};
}