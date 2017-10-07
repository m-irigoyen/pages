#include <sfmltemplate/core/graphics.hpp>

#include <sfmltemplate/core/resourcemanager.hpp>
#include <sfmltemplate/core/statemanager.hpp>

#include <mutils/assert.hpp>

namespace sfmltemplate
{
	Graphics::Graphics(ResourceManager* resourceManager, StateManager* stateManager)
		: resourceManager_(*resourceManager)
		, stateManager_(*stateManager)
	{

	}

	Graphics::~Graphics()
	{
	}

	bool Graphics::init(std::string n)
	{
		appName_ = n;
		window_ = new sf::RenderWindow();
		resizeWindow(1280, 720);
		if (!window_)
		{
			// TODO :error log
			return false;
		}

		return true;
	}

	bool Graphics::isWindowOpened() const
	{
		return window_->isOpen();
	}

	void Graphics::resizeWindow(int width, int height)
	{
		window_->create(sf::VideoMode(width, height)
			, appName_
			, sf::Style::Titlebar | sf::Style::Close);
	}

	sf::RenderWindow & Graphics::getWindow()
	{
		return *window_;
	}
}