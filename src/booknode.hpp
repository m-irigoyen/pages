#pragma once

#include "gamebook.hpp"

#include <sfmltemplate/gui/nodes/abstractinteractablenode.hpp>
#include <sfmltemplate/gui/scenegraph.hpp>

namespace pages
{
	class BookNode : public sfmltemplate::SceneNode
	{
	public:
		BookNode();

		// Inherited via Drawable
		virtual void drawSelf(sf::RenderTarget & target, sf::RenderStates states) const override;

		virtual bool init(sfmltemplate::SceneGraph& sceneGraph
			, ResourceManager* resourceManager);

		//! Do all time dependent actions on self and children
		virtual void tick(float dt);

		GameBook* getBook();

	protected:
		GameBook book_;
	};
}