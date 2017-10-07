//#include <sfmltemplate/gui/abstractpushbutton.hpp>
//
//namespace sfmltemplate
//{
//	AbstractPushButton::AbstractPushButton(AbstractHud * hud, InputManager * manager)
//		: AbstractInteractable(hud, manager)
//	{
//	}
//	void AbstractPushButton::onHoverBegin()
//	{
//	}
//	void AbstractPushButton::onHoverEnd()
//	{
//	}
//	void AbstractPushButton::onTouchBegin()
//	{
//	}
//	void AbstractPushButton::onTouchEnd()
//	{
//		// If its an action, it will only be done once (in onActionStart)
//		// if its an input, we need both the press and release event
//		onActionStart();
//		onActionEnd();
//	}
//}