//#pragma once
//
//#include <sfmltemplate/hud/baseradiobutton.hpp>
//
//namespace sfmltemplate
//{
//	/*
//		Manages a group of radio buttons. The group does not have ownership of the buttons : they must
//		be deleted somewhere else in the program.
//	*/
//	class RadioButtonGroup
//	{
//	public:
//		RadioButtonGroup();
//		~RadioButtonGroup();
//
//		//! Adds button to group. Returns true if button was added, false otherwise.
//		//! The button must have a label unique within the group. Otherwise, it won't be added.
//		bool addButton(BaseRadioButton* button);
//
//		//! Clears the group, deleting all buttons of the group
//		void clear();
//
//		//! Returns true if button is part of the group
//		bool contains(BaseRadioButton* button) const;
//		//! Returns true if there is a button with this label, and found is a pointer to this button
//		//! Else, returns false
//		bool contains(std::string label) const;
//		bool contains(std::string label, BaseRadioButton*& found) const;
//
//		//! Returns the group's label
//		std::string getLabel() const;
//
//		BaseRadioButton* getSelected() const;
//
//		//! Change the currently selected button
//		bool changeSelected(std::string selected);
//		bool changeSelected(BaseRadioButton* selected);
//
//		//! Removes button from the group. Returns true if button was removed, false otherwise.
//		bool removeButton(BaseRadioButton* button);
//
//		//! Sets the group's label
//		void setLabel(std::string label);
//
//	protected:
//		std::string label_;
//		std::vector<BaseRadioButton*> group_;
//		BaseRadioButton* selected_;
//	};
//}
