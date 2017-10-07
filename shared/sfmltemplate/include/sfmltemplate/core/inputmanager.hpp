#pragma once

#include <mutils/vec2.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <map>

namespace sfmltemplate
{
	struct Button
	{
		std::string id;	// Id of the button
		bool isPressed;	// Is this button pressed right now
		bool pressEvent;	// Was this button pressed during this frame ?
		bool releaseEvent;	// was this button released during this frame ?
	};

	class Graphics;
	class InputProcessor;
	class InputManager
	{
	public:
		friend InputProcessor;

		InputManager(Graphics* graphics);
		~InputManager();

		//! Return true if button is currently pressed
		bool isButtonPressed(std::string id) const;
		//! Returns true if given id is registered
		bool isValidButtonId(std::string id) const;
		//! Return true if button was pressed this frame
		bool pressEvent(std::string id) const;
		//! Return true if button was released this frame
		bool releaseEvent(std::string id) const;

		//! Get mouse position in screen space
		mutils::Vec2 getMouseScreenPosition(sf::RenderWindow& relativeTo) const;
		//! Get mouse position in world space
		mutils::Vec2 getMouseWorldPosition(
			sf::RenderWindow& window
			, sf::View currentView) const;

		void onButtonPress(std::string id);
		void onButtonRelease(std::string id);

		void resetFrameEvents();

		bool init();

		// Text capture stuff
		void cancelTextCapture();
		void endTextCapture();
		bool isTextCapturing() const;
		void startTextCapture(sf::String& inputTo);

		void registerButton(std::string id);

	protected:
		void registerTextCaptureCharacter(char c);
		void registerTextCaptureBackspace();

		Button& getButtonFromId(std::string id);
		const Button& getConstButtonFromId(std::string id) const;


		Graphics& graphics_;

		std::map<std::string, Button> buttons_;

		sf::String* inputTo_;
	};
}
