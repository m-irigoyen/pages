#include "stategame.hpp"

#include "booknode.hpp"
#include "guifactory.hpp"
#include "resourcemanager.hpp"
#include "statemanager.hpp"

#include <sfmltemplate/core/graphics.hpp>
#include <sfmltemplate/core/inputmanager.hpp>
#include <sfmltemplate/gui/nodes/shapeshiftertogglebuttonnode.hpp>

#include <iostream>

namespace pages
{
	StateGame::StateGame(
		sfmltemplate::Graphics * graphics
		, sfmltemplate::GuiFactory * guiFactory
		, sfmltemplate::InputManager * inputManager
		, ResourceManager * resourceManager
		, StateManager * stateManager)
		: AbstractState(graphics, guiFactory, inputManager, resourceManager, stateManager, 0)
	{

	}

	bool StateGame::clear()
	{
		return true;
	}

	bool StateGame::init()
	{
		// Book stuff
		std::unique_ptr<BookNode> book(new BookNode);
		book->init(worldGraph_, (ResourceManager*)&resourceManager_);
		bookNode_ = (BookNode*)(hudGraph_.sceneRoot.attachChild(std::move(book)));
		// Buttons

		return true;
	}

	void StateGame::tick(float dt)
	{
		AbstractState::tick(dt);


		// TODO that
	}
}
