#pragma once

#include <sfmltemplate/gui/drawables/shapeshifter.hpp>
#include <sfmltemplate/gui/nodes/pushbuttonnode.hpp>

namespace sfmltemplate
{
	class ShapeShifterPushButtonNode : public PushButtonNode, public ShapeShifter
	{
	public:
		ShapeShifterPushButtonNode(unsigned int flags
			, ShapeShifter::Shape shape);

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target
			, sf::RenderStates states) const override;
		virtual void drawSelf(sf::RenderTarget & target
			, sf::RenderStates states) const override;

		// Hérité via AbstractInteractableNode
		virtual sf::FloatRect getAABB() const override;
		virtual bool isInInteractionZone(mutils::Vec2 pos) const override;

	protected:
		// Hérité via ShapeShifterPushButtonNode
		virtual void onHoverBegin() override;
		virtual void onHoverEnd() override;
		virtual void onTouchBegin() override;
	};
}
