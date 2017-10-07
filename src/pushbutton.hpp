#pragma once

#include <mutils/color.hpp>

#include <sfmltemplate/gui/nodes/shapeshifterpushbuttonnode.hpp>

namespace pages
{
	class PushButton : public sfmltemplate::ShapeShifterPushButtonNode
	{
	public:
		PushButton();

	protected:
		virtual void onEnableChanged() override;
		virtual void onStatusChanged(Status oldStatus) override;


		mutils::Color hoverColor_;
		mutils::Color restColor_;
		mutils::Color selectedColor_;
	};
}