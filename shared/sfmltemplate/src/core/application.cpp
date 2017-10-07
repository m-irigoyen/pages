#include <sfmltemplate/core/application.hpp>
#include <sfmltemplate/core/abstractstate.hpp>
#include <sfmltemplate/core/graphics.hpp>
#include <sfmltemplate/core/guifactory.hpp>
#include <sfmltemplate/core/inputmanager.hpp>
#include <sfmltemplate/core/inputprocessor.hpp>
#include <sfmltemplate/core/pathmanager.hpp>
#include <sfmltemplate/core/resourcemanager.hpp>
#include <sfmltemplate/core/statemanager.hpp>

#include <mutils/assert.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace sfmltemplate
{
	Application::Application()
		: graphics_(nullptr)
		, guiFactory_(nullptr)
		, inputManager_(nullptr)
		, inputProcessor_(nullptr)
		, pathManager_(nullptr)
		, resourceManager_(nullptr)
		, stateManager_(nullptr)
	{
	}

	Application::~Application()
	{
		delete (graphics_);
		graphics_ = nullptr;
		delete (guiFactory_);
		guiFactory_ = nullptr;
		delete (inputManager_);
		inputManager_ = nullptr;
		delete (inputProcessor_);
		inputProcessor_ = nullptr;
		delete (pathManager_);
		pathManager_ = nullptr;
		delete (resourceManager_);
		resourceManager_ = nullptr;
		delete (stateManager_);
		stateManager_ = nullptr;
	}

	bool Application::init()
	{
		if (!createComponents())
		{
			// TODO log stuff about that error
			return false;
		}

		MUTILS_ASSERT(graphics_
			&& guiFactory_
			&& inputManager_
			&& inputProcessor_
			&& pathManager_
			&& resourceManager_
			&& stateManager_);

		if (!pathManager_->init())
		{
			// TODO log stuff about that error
			MUTILS_ASSERT(false);
			return false;
		}
		if (!resourceManager_->init())
		{
			// TODO log stuff about that error
			MUTILS_ASSERT(false);
			return false;
		}
		if (!stateManager_->init(graphics_
			, guiFactory_
			, inputManager_
			, resourceManager_
			, stateManager_))
		{
			// TODO log stuff about that error
			MUTILS_ASSERT(false);
			return false;
		}
		if (!graphics_->init())
		{
			// TODO log stuff about that error
			MUTILS_ASSERT(false);
			return false;
		}
		if (!inputManager_->init())
		{
			// TODO log stuff about that error
			MUTILS_ASSERT(false);
			return false;
		}
		if (!inputProcessor_->init())
		{
			// TODO log stuff about that error
			MUTILS_ASSERT(false);
			return false;
		}

		return true;
	}
	bool Application::run()
	{
		MUTILS_ASSERT(graphics_
			&& inputManager_
			&& inputProcessor_
			&& pathManager_
			&& resourceManager_
			&& stateManager_);

		sf::Clock clock;
		sf::Time oldFrame = sf::seconds(0.f);
		sf::Time newFrame = oldFrame;
		sf::Time elapsed;

		while (graphics_->isWindowOpened())
		{
			newFrame = clock.getElapsedTime();
			elapsed = newFrame - oldFrame;
			oldFrame = newFrame;
			// Event handling
			inputManager_->resetFrameEvents(); // Resetting events with the event manager
			sf::RenderWindow& window = graphics_->getWindow();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (!inputProcessor_->processSFMLInput(event) && event.type == sf::Event::Closed)
				{
					window.close();
					continue;
				}
			}

			// TODO : tick time control
			stateManager_->getCurrentState()->tick(elapsed.asSeconds());
			if (stateManager_->requestQuit)
			{
				close();
				return true;
			}

			window.clear();
			window.draw(*stateManager_->getCurrentState());
			window.display();
		}

		return true;
	}

	void Application::close()
	{
		MUTILS_ASSERT(graphics_);
		graphics_->getWindow().close();
	}
}