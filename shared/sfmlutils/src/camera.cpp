#include <sfmlutils/camera.hpp>

#include <sfmlutils/vectorutils.hpp>

#include <mutils/assert.hpp>

namespace sfmlutils
{
	using Vec2 = mutils::Vec2;

	Camera::Camera(sf::RenderWindow & window)
		: window_(&window)
	{
		resetToDefaultView();
	}

	Camera::Camera(sf::RenderWindow & window, mutils::Vec2 s, mutils::Vec2 p)
		: window_(&window),
		worldSize(s),
		worldPosition(p),
		viewport(0.f, 0.f, 1.f, 1.f)
	{
	}

	sf::View Camera::getView() const
	{
		sf::View v(getWorldBounds());
		v.setViewport(viewport);
		return v;
	}

	sf::RenderWindow & Camera::getWindow() const
	{
		MUTILS_ASSERT(window_);
		return *window_;
	}

	sf::FloatRect Camera::getWorldBounds() const
	{
		return sf::FloatRect(worldPosition.x - worldSize.x / 2.f,
			worldPosition.y - worldSize.y / 2.f,
			worldSize.x,
			worldSize.y);
	}

	void Camera::move(const mutils::Vec2 & movement)
	{
		worldPosition += movement;
	}

	void Camera::resetToDefaultView()
	{
		worldSize = sfmlutils::sfToVec2(window_->getDefaultView().getSize());
		worldPosition = sfmlutils::sfToVec2(window_->getDefaultView().getCenter());
		viewport = window_->getDefaultView().getViewport();
	}

	void Camera::setWindow(sf::RenderWindow & window)
	{
		window_ = &window;
	}

	void Camera::tick(float dt)
	{
	}

}


