#include <sfmltemplate/core/inputmanager.hpp>

#include <sfmltemplate/core/graphics.hpp>

#include <mutils/assert.hpp>
#include <sfmlutils/vectorutils.hpp>
#include <SFML/Window/Mouse.hpp>

namespace sfmltemplate
{
	using ButtonMap = std::map<std::string, Button>;

	InputManager::InputManager(Graphics* g)
		: graphics_(*g)
		, inputTo_(nullptr)
	{
	}

	InputManager::~InputManager()
	{
	}

	bool InputManager::isButtonPressed(std::string id) const
	{
		MUTILS_ASSERT(isValidButtonId(id));
		const Button& b = getConstButtonFromId(id);
		return  b.isPressed;
	}

	bool InputManager::isValidButtonId(std::string id) const
	{
		return buttons_.find(id) != buttons_.end();
	}

	bool InputManager::pressEvent(std::string id) const
	{
		MUTILS_ASSERT(isValidButtonId(id));
		const Button& b = getConstButtonFromId(id);
		return  b.pressEvent;
	}

	bool InputManager::releaseEvent(std::string id) const
	{
		MUTILS_ASSERT(isValidButtonId(id));
		const Button& b = getConstButtonFromId(id);
		return  b.releaseEvent;
	}

	mutils::Vec2 InputManager::getMouseScreenPosition(sf::RenderWindow& relativeTo) const
	{
		return sfmlutils::sfToVec2(sf::Mouse::getPosition(graphics_.getWindow()));
	}

	mutils::Vec2 InputManager::getMouseWorldPosition(sf::RenderWindow& window
		, sf::View currentView) const
	{
		return sfmlutils::sfToVec2(window.mapPixelToCoords(sf::Mouse::getPosition(window),
			currentView));
	}

	void InputManager::resetFrameEvents()
	{
		for (ButtonMap::iterator it = buttons_.begin(); it != buttons_.end(); ++it)
		{
			it->second.pressEvent = false;
			it->second.releaseEvent = false;
		}
	}

	bool InputManager::init()
	{
		return true;
	}

	void InputManager::startTextCapture(sf::String & inputTo)
	{
		inputTo_ = &inputTo;
	}

	void InputManager::cancelTextCapture()
	{
		MUTILS_ASSERT(inputTo_);
		inputTo_->clear();
		inputTo_ = nullptr;
		//TODO that
	}

	void InputManager::endTextCapture()
	{
		MUTILS_ASSERT(inputTo_);
		inputTo_ = nullptr;
	}

	bool InputManager::isTextCapturing() const
	{
		return inputTo_ != nullptr;
	}

	void InputManager::registerTextCaptureCharacter(char c)
	{
		MUTILS_ASSERT(inputTo_);
		*inputTo_ += c;
	}

	void InputManager::registerTextCaptureBackspace()
	{
		MUTILS_ASSERT(inputTo_);
		inputTo_->erase(inputTo_->getSize() - 1, 1);
	}

	Button& InputManager::getButtonFromId(std::string id)
	{
		ButtonMap::iterator it = buttons_.find(id);
		if (it != buttons_.end())
		{
			return it->second;
		}
		MUTILS_ASSERT(false);
		// TODO replace this by a throw
		Button b;
		return b;
	}

	const Button& InputManager::getConstButtonFromId(std::string id) const
	{
		ButtonMap::const_iterator it = buttons_.find(id);
		if (it != buttons_.end())
		{
			return it->second;
		}
		MUTILS_ASSERT(false);
		// TODO replace this by a throw
		Button b;
		return b;
	}

	void InputManager::onButtonPress(std::string id)
	{
		Button& b = getButtonFromId(id);
		b.isPressed = true;
		b.pressEvent = true;
	}

	void InputManager::onButtonRelease(std::string id)
	{
		Button& b = getButtonFromId(id);
		b.isPressed = false;
		b.releaseEvent = true;
	}
	void InputManager::registerButton(std::string id)
	{
		buttons_.insert(std::make_pair(id, Button()));
	}
}

