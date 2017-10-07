#pragma once

#include <sfmltemplate/gui/nodes/abstractinteractablenode.hpp>

namespace sfmltemplate
{
	class PushButtonNode : public AbstractInteractableNode
	{
	public:
		PushButtonNode();

		// Hérité via AbstractInteractableNode
	protected:
		virtual void onTouchEnd() override;
	};
}
