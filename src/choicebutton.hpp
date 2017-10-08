#pragma once

#include <mutils/color.hpp>

#include <sfmltemplate/gui/nodes/shapeshifterpushbuttonnode.hpp>

namespace pages
{
	class ChoiceButton : public sfmltemplate::ShapeShifterPushButtonNode
	{
	public:
		ChoiceButton();

	protected:
		virtual void onEnableChanged() override;
		virtual void onStatusChanged(Status oldStatus) override;


		mutils::Color hoverColor_;
		mutils::Color restColor_;
		mutils::Color selectedColor_;
		mutils::Color hoverOutlineColor_;
		mutils::Color restOutlineColor_;
		mutils::Color selectedOutlineColor_;
	};
}