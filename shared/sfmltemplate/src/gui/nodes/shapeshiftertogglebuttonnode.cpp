#include <sfmltemplate/gui/nodes/shapeshiftertogglebuttonnode.hpp>

#include <mutils/collision.hpp>

namespace sfmltemplate
{
	ShapeShifterToggleButtonNode::ShapeShifterToggleButtonNode(unsigned int flags
		, ShapeShifter::Shape shape)
		: ToggleButtonNode()
		, ShapeShifter(flags, shape)
	{

	}

	void ShapeShifterToggleButtonNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		ToggleButtonNode::draw(target, states);
	}

	void ShapeShifterToggleButtonNode::drawSelf(sf::RenderTarget & target, sf::RenderStates states) const
	{
		ShapeShifter::draw(target, states);
	}

	sf::FloatRect ShapeShifterToggleButtonNode::getAABB() const
	{
		return getBounds(getWorldPosition());
	}

	bool ShapeShifterToggleButtonNode::isInInteractionZone(mutils::Vec2 pos) const
	{
		sf::FloatRect b = getBounds(getWorldPosition());
		return mutils::isInAABB(pos, b.left, b.top, b.width, b.height);
	}
}
