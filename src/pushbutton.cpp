#include "pushbutton.hpp"

#include <sfmlutils/colorutils.hpp>


namespace pages
{
	PushButton::PushButton()
		: sfmltemplate::ShapeShifterPushButtonNode(Flags::SHAPE | Flags::TEXT, Shape::Rectangle)
		, hoverColor_(0.f, 0.f, 1.f, 1.f)
		, restColor_(0.5f, 0.5f, 0.5f, 1.f)
		, selectedColor_(1.f, 0.f, 0.f, 1.f)
	{
		onStatusChanged(Status::Rest);
	}

	void PushButton::onEnableChanged()
	{
	}

	void PushButton::onStatusChanged(Status oldStatus)
	{
		switch (status_)
		{
		case Status::Hovered:
			shape_->setFillColor(sfmlutils::toSfColor(hoverColor_));
			break;
		case Status::Rest:
			shape_->setFillColor(sfmlutils::toSfColor(restColor_));
			break;
		case Status::Selected:
			shape_->setFillColor(sfmlutils::toSfColor(selectedColor_));
			break;
		}
	}
}