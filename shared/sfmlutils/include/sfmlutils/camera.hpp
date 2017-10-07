#pragma once

#include <mutils/vec2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sfmlutils
{
	class Camera
	{
	public:
		Camera(sf::RenderWindow& window);
		Camera(sf::RenderWindow& window
			, mutils::Vec2 size
			, mutils::Vec2 pos);

		//! Returns the view corresponding to the camera values
		virtual sf::View getView() const;

		//! Get the window this camera is bound to
		virtual sf::RenderWindow& getWindow() const;

		//! Returns the bounds of the camera in world coordinates
		virtual sf::FloatRect getWorldBounds() const;

		//! Moves camera by given vector
		virtual void move(const mutils::Vec2& movement);

		//! Resets the camera to its window's default view
		virtual void resetToDefaultView();

		////! Rotates the came by given amount (in degrees)
		//void rotate(const float& rotation);

		//! Set the camera's window
		virtual void setWindow(sf::RenderWindow& window);

		//! Tick the camera
		virtual void tick(float dt);

		mutils::Vec2 worldSize;		//!< Size of the camera bounds in world space
		mutils::Vec2 worldPosition;	//!< Position of the camera in world space
		sf::FloatRect viewport;		//!< Viewport of the camera (left,top,width,height) in screen coordinates
	protected:
		sf::RenderWindow* window_;

	};
}