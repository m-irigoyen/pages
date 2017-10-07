#include "statemainmenu.hpp"

#include "guifactory.hpp"
#include "resourcemanager.hpp"
#include "statemanager.hpp"

#include <sfmltemplate/core/graphics.hpp>
#include <sfmltemplate/core/inputmanager.hpp>
#include <sfmltemplate/gui/nodes/shapeshiftertogglebuttonnode.hpp>

#include <iostream>

namespace pages
{
	StateMainMenu::StateMainMenu(
		sfmltemplate::Graphics * graphics
		, sfmltemplate::GuiFactory * guiFactory
		, sfmltemplate::InputManager * inputManager
		, ResourceManager * resourceManager
		, StateManager * stateManager)
		: AbstractState(graphics, guiFactory, inputManager, resourceManager, stateManager, 0)
	{

	}

	bool StateMainMenu::clear()
	{
		return true;
	}

	bool StateMainMenu::init()
	{
		// Init the hud graph

		{
			auto button = ((GuiFactory*)&guiFactory_)->makePushButton();
			button->setPosition(sf::Vector2f(400, 250));
			button->setString("Play");
			button->setAction(
				[this]()
				{
				((StateManager*)&stateManager_)->play = true;
				}
			);
			auto buttonPtr = hudGraph_.sceneRoot.attachChild(std::move(button));
			hudGraph_.registerInteractableNode(
				(sfmltemplate::AbstractInteractableNode*)buttonPtr);
		}

		{
			auto button = ((GuiFactory*)&guiFactory_)->makePushButton();
			button->setPosition(sf::Vector2f(400, 300));
			button->setString("Quit");
			button->setAction(
				[this]()
			{
				stateManager_.requestQuit = true;
			}
			);
			auto buttonPtr = hudGraph_.sceneRoot.attachChild(std::move(button));
			hudGraph_.registerInteractableNode(
				(sfmltemplate::AbstractInteractableNode*)buttonPtr);
		}

		{
			auto button = ((GuiFactory*)&guiFactory_)->makePushButton();
			button->setPosition(sf::Vector2f(400, 400));
			button->setString("Test");
			button->setAction(
				[this]()
			{
				((StateManager*)&stateManager_)->test = true;
			}
			);
			auto buttonPtr = hudGraph_.sceneRoot.attachChild(std::move(button));
			hudGraph_.registerInteractableNode(
				(sfmltemplate::AbstractInteractableNode*)buttonPtr);
		}

		return true;
	}

	void StateMainMenu::tick(float dt)
	{
		AbstractState::tick(dt);


		// TODO that
	}
}
