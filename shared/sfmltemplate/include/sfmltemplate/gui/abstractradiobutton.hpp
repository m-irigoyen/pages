//#pragma once
//
//#include <sfmltemplate/gui/abstractinteractable.hpp>
//
//#include <string>
//
//namespace sfmltemplate
//{
//	class RadioButtonGroup;
//	class BaseRadioButton : public AbstractInteractable
//	{
//	public:
//		BaseRadioButton(AbstractHud* hud = nullptr, InputManager* manager = nullptr);
//
//		RadioButtonGroup* getGroup() const;
//		std::string getLabel() const;
//		void setLabel(std::string label);
//		void setGroup(RadioButtonGroup* group);
//		void setSelected(bool isSelected);
//
//	protected:
//		virtual void onHoverBegin() override;
//		virtual void onHoverEnd() override;
//		virtual void onTouchBegin() override;
//		virtual void onTouchEnd() override;
//		//! Called when the button's selection status changes
//		virtual void onSelectedChanged() = 0;
//
//		bool isSelected_;	//!< True if this button is the one selected in his group
//		std::string label_;	//!< Used to differentiate between group members
//		RadioButtonGroup* group_;
//
//	};
//}