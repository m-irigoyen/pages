//#include <sfmltemplate/gui/abstractradiobutton.hpp>
//
//#include <sfmltemplate/gui/radiobuttongroup.hpp>
//
//#include <mutils/assert.hpp>
//
//namespace sfmltemplate
//{
//	BaseRadioButton::BaseRadioButton(AbstractHud * hud, InputManager * manager)
//		: AbstractInteractable(hud, manager)
//	{
//	}
//
//	RadioButtonGroup* BaseRadioButton::getGroup() const
//	{
//		return group_;
//	}
//
//	std::string BaseRadioButton::getLabel() const
//	{
//		return label_;
//	}
//
//	void BaseRadioButton::setLabel(std::string label)
//	{
//		MUTILS_ASSERT(!label.empty());
//		label_ = label;
//	}
//
//	void BaseRadioButton::setGroup(RadioButtonGroup * group)
//	{
//		group_ = group;
//	}
//
//	void BaseRadioButton::setSelected(bool isSelected)
//	{
//		isSelected_ = isSelected;
//		onSelectedChanged();
//	}
//
//	void BaseRadioButton::onHoverBegin()
//	{
//	}
//
//	void BaseRadioButton::onHoverEnd()
//	{
//	}
//
//	void BaseRadioButton::onTouchBegin()
//	{
//	}
//
//	void BaseRadioButton::onTouchEnd()
//	{
//	}
//
//	bool BaseRadioButton::onClickEnd()
//	{
//		MUTILS_ASSERT(group_);
//		group_->changeSelected(label_);
//		notifyHUD(true);
//		return BaseButton::onClickEnd();
//	}
//}
//
