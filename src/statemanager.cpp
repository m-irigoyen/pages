#include "statemanager.hpp"

namespace pages
{
	StateManager::StateManager()
		: sfmltemplate::StateManager()
		, play(false)
		, test(false)
	{

	}

	bool StateManager::init(sfmltemplate::Graphics* graphics
		, sfmltemplate::GuiFactory* guiFactory
		, sfmltemplate::InputManager* inputManager
		, sfmltemplate::ResourceManager* resourceManager
		, sfmltemplate::StateManager* stateManager)
	{
		stateMainMenu = new StateMainMenu(graphics
			, guiFactory
			, inputManager
			, (ResourceManager*)resourceManager
			, (StateManager*)stateManager);

		stateGame = new StateGame(graphics
			, guiFactory
			, inputManager
			, (ResourceManager*)resourceManager
			, (StateManager*)stateManager);

		stateTest = new StateTest(graphics
			, guiFactory
			, inputManager
			, (ResourceManager*)resourceManager
			, (StateManager*)stateManager);

		return stateMainMenu->init() && stateGame->init() && stateTest->init();
	}

	sfmltemplate::AbstractState * StateManager::getCurrentState()
	{
		if (test)
		{
			return stateTest;
		}
		else if (play)
		{
			return stateGame;
		}
		else
		{
			return stateMainMenu;
		}
	}

	int StateManager::getCurrentStateId() const
	{
		return stateMainMenu->getId();
	}

	void StateManager::setState(int id)
	{
	}

	void StateManager::goToPreviousState()
	{
	}

}
