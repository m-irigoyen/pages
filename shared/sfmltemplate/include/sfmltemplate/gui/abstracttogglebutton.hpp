//TODO : that

//#pragma once
//
//#include <sfmlhud/abstractbutton.hpp>
//
//namespace sfmlhud
//{
//	class AbstractToggleButton : public AbstractButton
//	{
//	public:
//		enum STATE
//		{
//			OFF,
//			ON,
//
//			COUNT
//		};
//
//		AbstractToggleButton();
//
//		virtual void onMouseMove(const sf::Vector2f& pos) override;
//		virtual bool onMousePress(const sf::Vector2f& pos) override;
//		virtual bool onMouseRelease(const sf::Vector2f& pos) override;
//
//		//! Forces state without notifying observers
//		virtual void setState(STATE s) = 0;
//
//		STATE getState() const;
//
//		virtual void setHoverIndication() = 0;
//
//		virtual bool isOn() const;
//
//		virtual void toggle();
//
//	protected:
//		bool hover_;
//		STATE state_;
//	};
//}