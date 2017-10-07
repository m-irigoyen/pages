#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace sfmlutils
{
	class AbstractApplication
	{
	public:
		AbstractApplication();

		//! Initialize the application. Returns true if everything was setup successfuly, else false
		//! This must set the init_ boolean to true if successful
		virtual bool init() = 0;
		//! Returns true if the application can be run safely, else false
		virtual bool canRun();

		//! Runs the application. Returns true if application terminated successfully, false otherwise
		virtual bool run();

		virtual bool runFreePhysics();

		//! Treats given event. Returns true if the event was treated, false otherwise
		virtual bool handleEvent(const sf::Event& e);

		virtual void simulate(float dt) = 0;

		virtual void display(float dt) = 0;

	protected:
		sf::RenderWindow* window_;
		sf::Clock clock_;
		sf::Time elapsed_;

		float fpsDt_;
		float physicsDt_;

		bool init_;
	};
}