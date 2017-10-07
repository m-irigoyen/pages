#pragma once

#include <sfmltemplate/gui/abstractinteractable.hpp>
#include <sfmltemplate/gui/scenenode.hpp>

namespace sfmltemplate
{
	class SceneGraph;
	class AbstractInteractableNode : public SceneNode, public AbstractInteractable
	{
	public:
		AbstractInteractableNode();

		virtual bool isEnabled() const;

		// Call to process cursor move events
		virtual void onCursorMove(mutils::Vec2 pos) override;
		virtual void onCursorMoveChildren(mutils::Vec2 pos);
		virtual void onCursorMoveSelf(mutils::Vec2 pos);

		// Call to process touch begin events
		virtual bool checkTouchBegin(mutils::Vec2 pos) override;
		virtual bool checkTouchBeginChildren(mutils::Vec2 pos);
		virtual bool checkTouchBeginSelf(mutils::Vec2 pos);

		// Call to process touch end events
		virtual bool checkTouchEnd(mutils::Vec2 pos) override;
		virtual bool checkTouchEndChildren(mutils::Vec2 pos);
		virtual bool checkTouchEndSelf(mutils::Vec2 pos);
	};
}