#pragma once

#include <sfmltemplate/gui/nodes/abstractinteractablenode.hpp>

namespace sfmltemplate
{
	class ToggleButtonNode : public AbstractInteractableNode
	{
	public:
		ToggleButtonNode();

		//! Set the watched variable
		void setVariable(bool& var);

		bool toggle();

		// Hérité via AbstractInteractableNode
	protected:
		virtual void onHoverBegin() override;
		virtual void onHoverEnd() override;
		virtual void onTouchBegin() override;
		virtual void onTouchEnd() override;
		virtual void onStatusChanged(Status oldStatus) override;
		virtual void onEnableChanged() override;

		virtual void onVariableChanged();

		bool* variable_;

	private:
		virtual void setAction(std::function<void()> action) override;
		virtual void setInput(std::string inputId, InputManager& manager) override;
		virtual void onActionEnd() override;
		virtual void onActionStart() override;
	};
}
