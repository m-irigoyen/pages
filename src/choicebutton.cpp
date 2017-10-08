#include "choicebutton.hpp"

#include <sfmlutils/colorutils.hpp>

namespace pages
{
	ChoiceButton::ChoiceButton()
		: sfmltemplate::ShapeShifterPushButtonNode(Flags::SHAPE | Flags::TEXT, Shape::Rectangle)
		, hoverColor_(0.7f, 0.7f, 0.7f, 0.2f)
		, restColor_(0.8f, 0.8f, 0.8f, 0.2f)
		, selectedColor_(0.9f, 0.9f, 0.9f, 0.2f)
		, hoverOutlineColor_(0.f, 0.f, 1.f, 1.f)
		, restOutlineColor_(0.5f, 0.5f, 0.5f, 1.f)
		, selectedOutlineColor_(1.f, 0.f, 0.f, 1.f)
	{
		shape_->setFillColor(sfmlutils::toSfColor(restColor_));
		shape_->setOutlineColor(sfmlutils::toSfColor(restOutlineColor_));
		shape_->setOutlineThickness(1.f);

		text_->setCharacterSize(16);
		setMargin(5.f, 5.f);
	}
	void ChoiceButton::onEnableChanged()
	{
	}
	void ChoiceButton::onStatusChanged(Status oldStatus)
	{
		switch (status_)
		{
		case Status::Hovered:
			shape_->setFillColor(sfmlutils::toSfColor(hoverColor_));
			shape_->setOutlineColor(sfmlutils::toSfColor(hoverOutlineColor_));
			break;
		case Status::Rest:
			shape_->setFillColor(sfmlutils::toSfColor(restColor_));
			shape_->setOutlineColor(sfmlutils::toSfColor(restOutlineColor_));
			break;
		case Status::Selected:
			shape_->setFillColor(sfmlutils::toSfColor(selectedColor_));
			shape_->setOutlineColor(sfmlutils::toSfColor(selectedOutlineColor_));
			break;
		}
	}
}