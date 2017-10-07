#pragma once

#include <sfmltemplate/gui/nodes/abstractinteractablenode.hpp>

#include <mutils/vec2.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <map>

namespace sfmltemplate
{
	class SceneGraph : public virtual sf::Drawable
	{
	public:
		SceneGraph();
		~SceneGraph();

		// Hérité via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

		virtual void onCursorMove(mutils::Vec2 cursorPos);
		virtual bool onCursorPress(mutils::Vec2 cursorPos);
		virtual bool onCursorRelease(mutils::Vec2 cursorPos);

		void registerInteractableNode(AbstractInteractableNode* interactable);
		void unregisterInteractableNode(AbstractInteractableNode* interactable);

		//! Ticks all hud elements.
		virtual void tick(float dt);

		SceneNode sceneRoot;
	protected:
		std::vector<AbstractInteractableNode*> interactables_;
	};
}