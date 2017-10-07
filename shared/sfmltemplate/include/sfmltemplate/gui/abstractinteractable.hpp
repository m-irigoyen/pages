#pragma once

#include <mutils/vec2.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <functional>
#include <string>

namespace sfmltemplate
{
	class InputManager;
	class AbstractInteractable
	{
	public:
		enum class Status
		{
			Rest,
			Hovered,
			Selected,

			COUNT
		};

		AbstractInteractable();

		//! Get the Axis Aligned Bounding Box of the element (xLeft, yTop, width, height)
		virtual sf::FloatRect getAABB() const = 0;

		virtual bool isActionButton() const;
		virtual bool isEnabled() const;
		virtual bool isInInteractionZone(mutils::Vec2 pos) const = 0;

		virtual void onCursorMove(mutils::Vec2 pos);
		virtual bool checkTouchBegin(mutils::Vec2 pos);
		virtual bool checkTouchEnd(mutils::Vec2 pos);

		virtual void setAction(std::function<void()> action);
		virtual void setEnabled(bool enabled);
		virtual void setInput(std::string inputId, InputManager& manager);

	protected:
		virtual void onHoverBegin() = 0;
		virtual void onHoverEnd() = 0;
		virtual void onTouchBegin() = 0;
		virtual void onTouchEnd() = 0;
		virtual void onActionEnd();
		virtual void onActionStart();
		virtual void onStatusChanged(Status oldStatus) = 0;
		virtual void onEnableChanged() = 0;
		virtual void setStatus(Status s);

		bool enabled_;
		InputManager* inputManager_;
		std::string associatedInput_;
		std::function<void()> action_;
		Status status_;
	};
}