//#include <sfmltemplate/hud/radiobuttongroup.hpp>
//
//#include <mutils/stringutils.hpp>
//#include <mutils/vectorutils.hpp>
//
//#include <algorithm>
//
//namespace sfmltemplate
//{
//	RadioButtonGroup::RadioButtonGroup()
//		: selected_(nullptr)
//	{
//
//	}
//	RadioButtonGroup::~RadioButtonGroup() {
//
//	}
//
//	bool RadioButtonGroup::addButton(BaseRadioButton* button)
//	{
//		MUTILS_ASSERT(button);
//		if ((!button->getLabel().empty())
//			&& !contains(button->getLabel())
//			&& mutils::addUnique(group_, button))
//		{
//			if (button->getGroup())
//			{
//				button->getGroup()->removeButton(button);
//			}
//			button->setGroup(this);
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	void RadioButtonGroup::clear()
//	{
//		group_.clear();
//	}
//
//	bool RadioButtonGroup::contains(BaseRadioButton* button) const
//	{
//		MUTILS_ASSERT(button);
//		std::vector<BaseRadioButton*>::const_iterator it =
//			std::find(group_.begin(), group_.end(), button);
//		if (it != group_.end())
//		{
//			button = *it;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	bool RadioButtonGroup::contains(std::string label) const
//	{
//		BaseRadioButton* p;
//		return contains(label, p);
//	}
//
//	bool RadioButtonGroup::contains(std::string label, BaseRadioButton*& found) const {
//		for (BaseRadioButton* b : group_)
//		{
//			if (mutils::compare(label, b->getLabel()))
//			{
//				found = b;
//				return true;
//			}
//		}
//		return false;
//	}
//
//	std::string RadioButtonGroup::getLabel() const
//	{
//		return label_;
//	}
//
//	BaseRadioButton * RadioButtonGroup::getSelected() const
//	{
//		return selected_;
//	}
//
//	bool RadioButtonGroup::changeSelected(std::string selected)
//	{
//		bool ok = false;
//		for (BaseRadioButton* b : group_)
//		{
//			if (mutils::compare(b->getLabel(), selected))
//			{
//				ok = true;
//				b->setSelected(true);
//				selected_ = b;
//			}
//			else
//			{
//				b->setSelected(false);
//			}
//		}
//		return ok;
//	}
//
//	bool RadioButtonGroup::changeSelected(BaseRadioButton * selected)
//	{
//		MUTILS_ASSERT(selected);
//		return changeSelected(selected->getLabel());
//	}
//
//	bool RadioButtonGroup::removeButton(BaseRadioButton* button)
//	{
//		MUTILS_ASSERT(button);
//		std::vector<BaseRadioButton*>::const_iterator it =
//			std::find(group_.begin(), group_.end(), button);
//		if (it != group_.end())
//		{
//			button = *it;
//			group_.erase(it);
//			button->setGroup(nullptr);
//			return true;
//		}
//		return false;
//	}
//
//	void RadioButtonGroup::setLabel(std::string label)
//	{
//		MUTILS_ASSERT(!label.empty());
//		label_ = label;
//	}
//}