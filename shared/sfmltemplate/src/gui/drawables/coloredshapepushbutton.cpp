//#include <sfmlhud/coloredshapepushbutton.hpp>
//
//#include <mutils/assert.hpp>
//
//#include <iostream>
//
//namespace sfmlhud
//{
//
//	ColoredShapePushButton::ColoredShapePushButton(unsigned int flags, AbstractHud& hud, Shape s)
//		: BasePushButton(flags, hud, s)
//	{
//
//	}
//
//	void ColoredShapePushButton::tick(float dt)
//	{
//		BasePushButton::tick(dt);
//	}
//
//	void ColoredShapePushButton::setColors(const sf::Color & restColor,
//		const sf::Color & hoverColor,
//		const sf::Color & clickColor)
//	{
//		restColor_ = restColor;
//		hoverColor_ = hoverColor;
//		clickColor_ = clickColor;
//		onStatusChanged();
//	}
//
//	sf::Color ColoredShapePushButton::getRestColor() const
//	{
//		return restColor_;
//	}
//
//	sf::Color ColoredShapePushButton::getHoverColor() const
//	{
//		return hoverColor_;
//	}
//
//	sf::Color ColoredShapePushButton::getClickColor() const
//	{
//		return clickColor_;
//	}
//
//	void ColoredShapePushButton::onStatusChanged()
//	{
//		if (hasShape_)
//		{
//			switch (status_)
//			{
//			case BaseButton::Status::Rest:
//				shape_->setFillColor(restColor_);
//				break;
//			case BaseButton::Status::Hovered:
//				shape_->setFillColor(hoverColor_);
//				break;
//			case BaseButton::Status::Clicked:
//				shape_->setFillColor(clickColor_);
//				break;
//			default:
//				MUTILS_UNREACHABLE;
//			}
//		}
//	}
//}