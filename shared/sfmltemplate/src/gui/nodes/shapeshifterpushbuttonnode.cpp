#include <sfmltemplate/gui/nodes/shapeshifterpushbuttonnode.hpp>

#include <mutils/collision.hpp>

namespace sfmltemplate
{
	ShapeShifterPushButtonNode::ShapeShifterPushButtonNode(unsigned int flags
		, ShapeShifter::Shape shape)
		: PushButtonNode()
		, ShapeShifter(flags, shape)
	{
	}
	void ShapeShifterPushButtonNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		PushButtonNode::draw(target, states);
	}
	void ShapeShifterPushButtonNode::drawSelf(sf::RenderTarget & target, sf::RenderStates states) const
	{
		ShapeShifter::draw(target, states);
	}
	sf::FloatRect ShapeShifterPushButtonNode::getAABB() const
	{
		return getBounds(getWorldPosition());
	}
	bool ShapeShifterPushButtonNode::isInInteractionZone(mutils::Vec2 pos) const
	{
		sf::FloatRect b = getBounds(getWorldPosition());
		return mutils::isInAABB(pos, b.left, b.top, b.width, b.height);
	}
	void ShapeShifterPushButtonNode::onHoverBegin()
	{
	}
	void ShapeShifterPushButtonNode::onHoverEnd()
	{
	}
	void ShapeShifterPushButtonNode::onTouchBegin()
	{
	}
}
