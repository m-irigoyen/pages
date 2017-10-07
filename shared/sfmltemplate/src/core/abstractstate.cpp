#include <sfmltemplate/core/abstractstate.hpp>

#include <sfmltemplate/core/graphics.hpp>
#include <sfmltemplate/core/inputmanager.hpp>
#include <sfmltemplate/core/resourcemanager.hpp>
#include <sfmltemplate/core/statemanager.hpp>

namespace sfmltemplate
{
	AbstractState::AbstractState(Graphics * graphics
		, GuiFactory* guiFactory
		, InputManager * inputManager
		, ResourceManager * resourceManager
		, StateManager * stateManager
		, int id)
		: graphics_(*graphics)
		, guiFactory_(*guiFactory)
		, inputManager_(*inputManager)
		, resourceManager_(*resourceManager)
		, stateManager_(*stateManager)
		, id_(id)
	{
	}

	AbstractState::~AbstractState()
	{
	}

	void AbstractState::tick(float dt)
	{
		// Passing mouse movement to hud
		mutils::Vec2 mousePos = inputManager_.getMouseScreenPosition(graphics_.getWindow());

		hudGraph_.onCursorMove(mousePos);
		worldGraph_.onCursorMove(mousePos);

		if (inputManager_.pressEvent("touch"))
		{
			hudGraph_.onCursorPress(mousePos);
			worldGraph_.onCursorPress(mousePos);
		}
		if (inputManager_.releaseEvent("touch"))
		{
			hudGraph_.onCursorRelease(mousePos);
			worldGraph_.onCursorRelease(mousePos);
		}

		// Then, ticking hud
		hudGraph_.tick(dt);
		worldGraph_.tick(dt);
	}

	int AbstractState::getId() const
	{
		return id_;
	}

	void AbstractState::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		worldGraph_.draw(target, states);
		hudGraph_.draw(target, states);
	}
}

