#include <sfmltemplate/gui/nodes/abstractinteractablenode.hpp>

#include <sfmlutils/vectorutils.hpp>

namespace sfmltemplate
{
	AbstractInteractableNode::AbstractInteractableNode()
		: AbstractInteractable()
	{

	}

	bool AbstractInteractableNode::isEnabled() const
	{
		if (enabled_
			&& parent_
			&& dynamic_cast<AbstractInteractableNode*>(parent_))
		{
			return ((AbstractInteractableNode*)parent_)->isEnabled();
		}
		else
		{
			return enabled_;
		}
	}

	void AbstractInteractableNode::onCursorMove(mutils::Vec2 pos)
	{
		onCursorMoveChildren(pos);
		onCursorMoveSelf(pos);
	}

	void AbstractInteractableNode::onCursorMoveChildren(mutils::Vec2 pos)
	{
		for (SceneNode::UniquePtr& c : children_)
		{
			if (dynamic_cast<AbstractInteractableNode*>(c.get()))
			{
				((AbstractInteractableNode*)parent_)->onCursorMove(pos);
			}
		}
	}
	void AbstractInteractableNode::onCursorMoveSelf(mutils::Vec2 pos)
	{
		AbstractInteractable::onCursorMove(pos);
	}

	bool AbstractInteractableNode::checkTouchBegin(mutils::Vec2 pos)
	{
		if (checkTouchBeginChildren(pos))
		{
			return true;
		}
		else
		{
			return checkTouchBeginSelf(pos);
		}
	}
	bool AbstractInteractableNode::checkTouchBeginChildren(mutils::Vec2 pos)
	{
		for (SceneNode::UniquePtr& c : children_)
		{
			if (dynamic_cast<AbstractInteractableNode*>(c.get())
				&& ((AbstractInteractableNode*)parent_)->checkTouchBegin(pos))
			{
				return true;
			}
		}
		return false;
	}
	bool AbstractInteractableNode::checkTouchBeginSelf(mutils::Vec2 pos)
	{
		return AbstractInteractable::checkTouchBegin(pos);
	}

	bool AbstractInteractableNode::checkTouchEnd(mutils::Vec2 pos)
	{
		if (checkTouchEndChildren(pos))
		{
			return true;
		}
		else
		{
			return checkTouchEndSelf(pos);
		}
	}
	bool AbstractInteractableNode::checkTouchEndChildren(mutils::Vec2 pos)
	{
		for (SceneNode::UniquePtr& c : children_)
		{
			if (dynamic_cast<AbstractInteractableNode*>(c.get())
				&& ((AbstractInteractableNode*)parent_)->checkTouchEnd(pos))
			{
				return true;
			}
		}
		return false;
	}

	bool AbstractInteractableNode::checkTouchEndSelf(mutils::Vec2 pos)
	{
		return AbstractInteractable::checkTouchEnd(pos);
	}
}

