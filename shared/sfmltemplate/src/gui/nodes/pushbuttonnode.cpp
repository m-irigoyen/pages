#include <sfmltemplate/gui/nodes/pushbuttonnode.hpp>

#include <mutils/assert.hpp>

namespace sfmltemplate
{
	PushButtonNode::PushButtonNode()
		: AbstractInteractableNode()
	{
	}

	void PushButtonNode::onTouchEnd()
	{
		onActionStart();
		onActionEnd();
	}
}