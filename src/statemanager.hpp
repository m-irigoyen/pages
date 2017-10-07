#pragma once

#include "stategame.hpp"
#include "statemainmenu.hpp"
#include "statetest.hpp"

#include <sfmltemplate/core/statemanager.hpp>

namespace pages
{
	class StateManager : public sfmltemplate::StateManager
	{
	public:
		StateManager();

		// Hérité via StateManager
		virtual bool init(sfmltemplate::Graphics* graphics
			, sfmltemplate::GuiFactory* guiFactory
			, sfmltemplate::InputManager* inputManager
			, sfmltemplate::ResourceManager* resourceManager
			, sfmltemplate::StateManager* stateManager) override;
		virtual sfmltemplate::AbstractState * getCurrentState() override;
		virtual int getCurrentStateId() const override;
		virtual void setState(int id) override;
		virtual void goToPreviousState() override;

		bool play;
		bool test;

		StateMainMenu* stateMainMenu;
		StateGame* stateGame;
		StateTest* stateTest;
	};
}