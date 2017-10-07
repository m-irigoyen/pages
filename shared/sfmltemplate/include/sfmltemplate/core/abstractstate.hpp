#pragma once

#include <sfmltemplate/gui/scenegraph.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace sfmltemplate
{
	class Graphics;
	class GuiFactory;
	class InputManager;
	class ResourceManager;
	class StateManager;
	class AbstractState : public sf::Drawable
	{
	public:
		AbstractState(Graphics* graphics
			, GuiFactory* guiFactory
			, InputManager* inputManager
			, ResourceManager* resourceManager
			, StateManager* stateManager
			, int id);
		~AbstractState();

		virtual bool clear() = 0;
		virtual bool init() = 0;
		virtual void tick(float dt);

		int getId() const;

	protected:
		int id_;

		Graphics& graphics_;
		GuiFactory& guiFactory_;
		InputManager& inputManager_;
		ResourceManager& resourceManager_;
		StateManager& stateManager_;

		SceneGraph hudGraph_;
		SceneGraph worldGraph_;

		// Hérité via Drawable
		virtual void draw(
			sf::RenderTarget & target
			, sf::RenderStates states) const override;
	};
}