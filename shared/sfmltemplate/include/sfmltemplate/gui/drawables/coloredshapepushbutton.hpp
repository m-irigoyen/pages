//#pragma once
//
//#include "basepushbutton.hpp"
//
//#include <SFML/Graphics/Color.hpp>
//
//namespace sfmlhud
//{
//	class ColoredShapePushButton : public BasePushButton
//	{
//	public:
//		ColoredShapePushButton(unsigned int flags, AbstractHud& hud, Shape s);
//		virtual void tick(float dt);
//
//		void setColors(const sf::Color& restColor,
//			const sf::Color& hoverColor,
//			const sf::Color& clickColor);
//
//		sf::Color getRestColor() const;
//		sf::Color getHoverColor() const;
//		sf::Color getClickColor() const;
//
//	protected:
//
//		sf::Color restColor_;
//		sf::Color hoverColor_;
//		sf::Color clickColor_;
//		virtual void onStatusChanged();
//	};
//}
