#pragma once

#include <sfmltemplate/core/abstractstate.hpp>

namespace pages
{
	class BookNode;
	class ResourceManager;
	class StateManager;
	class StateGame : public sfmltemplate::AbstractState
	{
	public:
		StateGame(sfmltemplate::Graphics* graphics
			, sfmltemplate::GuiFactory* guiFactory
			, sfmltemplate::InputManager* inputManager
			, ResourceManager* resourceManager
			, StateManager* stateManager);

		// Hérité via AbstractState
		virtual bool clear() override;
		virtual bool init() override;
		virtual void tick(float dt) override;

	protected:
		BookNode* bookNode_;
		/*virtual void draw(
		sf::RenderTarget & target
		, sf::RenderStates states) const override;*/
	};
}