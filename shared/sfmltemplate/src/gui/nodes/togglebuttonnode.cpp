#include <sfmltemplate/gui/nodes/togglebuttonnode.hpp>

#include <mutils/assert.hpp>

namespace sfmltemplate
{
	ToggleButtonNode::ToggleButtonNode()
		: AbstractInteractableNode()
	{
	}

	void ToggleButtonNode::setVariable(bool & var)
	{
		variable_ = &var;
	}

	bool ToggleButtonNode::toggle()
	{
		MUTILS_ASSERT(variable_);
		*variable_ = !(*variable_);
		onVariableChanged();
		return variable_;
	}

	void ToggleButtonNode::onHoverBegin()
	{
	}

	void ToggleButtonNode::onHoverEnd()
	{
	}

	void ToggleButtonNode::onTouchBegin()
	{
	}

	void ToggleButtonNode::onTouchEnd()
	{
		toggle();
	}

	void ToggleButtonNode::onStatusChanged(Status oldStatus)
	{
	}

	void ToggleButtonNode::onEnableChanged()
	{
	}
	void ToggleButtonNode::onVariableChanged()
	{
	}
	void ToggleButtonNode::setAction(std::function<void()> action)
	{
	}
	void ToggleButtonNode::setInput(std::string inputId, InputManager & manager)
	{
	}
	void ToggleButtonNode::onActionEnd()
	{
	}
	void ToggleButtonNode::onActionStart()
	{
	}
}