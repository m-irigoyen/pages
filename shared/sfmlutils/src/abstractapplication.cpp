#include <sfmlutils/abstractapplication.hpp>

#include <iostream>

namespace sfmlutils
{
	AbstractApplication::AbstractApplication()
		: init_(false)
	{
	}

	bool AbstractApplication::canRun()
	{
		return init_;
	}

	bool AbstractApplication::run()
	{
		try
		{
			float dtMin = std::min(fpsDt_, physicsDt_);

			sf::Time currentFrame;
			elapsed_ = sf::seconds(0);
			clock_.restart();
			sf::Event e;
			while (window_->isOpen())
			{
				while (window_->pollEvent(e))
				{
					handleEvent(e);
				}

				elapsed_ = clock_.getElapsedTime();
				sf::Time frameTime = elapsed_ - currentFrame;
				if (frameTime.asSeconds() >= dtMin)
				{
					currentFrame = sf::seconds(currentFrame.asSeconds() + dtMin);
					simulate(dtMin);
					display(1.f);
				}
			}
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}

		return true;
	}

	bool AbstractApplication::runFreePhysics()
	{
		try
		{
			sf::Time currentTime = sf::seconds(0.f);
			float accumulator = 0.f;
			sf::Event e;

			elapsed_ = sf::seconds(0);
			clock_.restart();
			while (window_->isOpen())
			{
				while (window_->pollEvent(e))
				{
					handleEvent(e);
				}

				elapsed_ = clock_.getElapsedTime();
				sf::Time frameTime = elapsed_ - currentTime;
				if (frameTime.asSeconds() > 0.25f)
				{
					frameTime = sf::seconds(0.25f);
				}
				sf::Time currentTime = elapsed_;

				accumulator += frameTime.asSeconds();

				while (accumulator >= physicsDt_)
				{
					simulate(physicsDt_);

					accumulator -= physicsDt_;
				}

				display(accumulator / physicsDt_);
			}
		}
		catch (std::exception e)
		{
			std::cerr << e.what() << std::endl;
			return false;
		}

		return true;
	}
	bool AbstractApplication::handleEvent(const sf::Event & e)
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			window_->close();
			return true;
		}

		return false;
	}
}