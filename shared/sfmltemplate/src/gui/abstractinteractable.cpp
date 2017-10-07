#include <sfmltemplate/gui/abstractinteractable.hpp>

#include <sfmltemplate/core/inputmanager.hpp>

#include <mutils/assert.hpp>
#include <sfmlutils/vectorutils.hpp>

namespace sfmltemplate
{
	AbstractInteractable::AbstractInteractable()
		: enabled_(true)
		, inputManager_(nullptr)
		, status_(Status::Rest)
	{

	}

	bool AbstractInteractable::isActionButton() const
	{
		return (action_) ? true : false;
	}

	bool AbstractInteractable::isEnabled() const
	{
		return enabled_;
	}

	void AbstractInteractable::onCursorMove(mutils::Vec2 pos)
	{
		if (enabled_)
		{
			if (status_ == Status::Rest)
			{
				if (isInInteractionZone(pos))	// Optimization to checking collision twice
				{
					setStatus(Status::Hovered);
					onHoverBegin();
				}
			}
			else if ((status_ == Status::Hovered) && (!isInInteractionZone(pos)))
			{
				setStatus(Status::Rest);
				onHoverEnd();
			}
		}
	}

	bool AbstractInteractable::checkTouchBegin(mutils::Vec2 pos)
	{
		if (enabled_ && isInInteractionZone(pos))
		{
			Status old = status_;
			setStatus(Status::Selected);
			onTouchBegin();
			return true;
		}
		return false;
	}

	bool AbstractInteractable::checkTouchEnd(mutils::Vec2 pos)
	{
		if (enabled_ && isInInteractionZone(pos))
		{
			setStatus(Status::Hovered);
			onTouchEnd();
			return true;
		}
		else if (enabled_ && status_ == Status::Selected)
		{
			setStatus(Status::Rest);
		}
		return false;
	}

	void AbstractInteractable::setAction(std::function<void()> action)
	{
		action_ = action;
		associatedInput_.clear();
	}

	void AbstractInteractable::setEnabled(bool enabled)
	{
		if (enabled_ != enabled)
		{
			enabled_ = enabled;
			onEnableChanged();
		}
	}

	void AbstractInteractable::setInput(std::string inputId, InputManager& manager)
	{
		associatedInput_ = inputId;
		inputManager_ = &manager;
		action_ = nullptr;
	}

	void AbstractInteractable::onActionEnd()
	{
		if (!isActionButton())
		{
			MUTILS_ASSERT(inputManager_);
			inputManager_->onButtonRelease(associatedInput_);
		}
	}
	void AbstractInteractable::onActionStart()
	{
		if (isActionButton())
		{
			action_();
		}
		else
		{
			MUTILS_ASSERT(inputManager_);
			inputManager_->onButtonPress(associatedInput_);
		}
	}

	void AbstractInteractable::setStatus(Status s)
	{
		Status old = status_;
		status_ = s;
		onStatusChanged(old);
	}
}