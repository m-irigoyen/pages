#include "gamebook.hpp"

#include "pathmanager.hpp"
#include "resourcemanager.hpp"

#include <mutils/assert.hpp>
#include <mutils/vec2.hpp>
#include <sfmlutils/spriteutils.hpp>
#include <sfmlutils/vectorutils.hpp>

namespace pages
{
	using Vec2 = mutils::Vec2;

	GameBook::GameBook()
		: AbstractBook(Vec2(630.f, 700.f), Vec2(10.f, 10.f), 100.f, Vec2(80.f, 420.f))
	{

	}

	bool GameBook::init(ResourceManager* manager)
	{
		if (!AbstractBook::init(manager))
		{
			return false;
		}

		// Font
		/*font_ = manager->getFont(ResourceManager::Fonts::monofonto);
		MUTILS_ASSERT(font_);*/

		// Test page images

		PathManager* paths_ = (PathManager*)manager->getPathManager();
		currentPage_ = 0;

		// Shadow image
		if (!shadowTex_.loadFromFile(paths_->getTexturesPath() + "/shadow.png"))
		{
			MUTILS_ASSERT(false);
			return false;
		}
		shadowSprite_.setTexture(shadowTex_);

		pages_.resize(4);
		pagesTex_.resize(4);

		return true;
	}

	void GameBook::drawPage(sf::RenderTarget & target
		, sf::RenderStates states
		, unsigned int pageNb
		, mutils::Vec2 position
		, mutils::Vec2 pageOrigin
		, float rotation
		, bool leftPage
		, const sf::Shader * shader) const
	{
		//TODO : assert page nb and window
		sf::Sprite s = pages_[pageNb];
		s.setOrigin(sfmlutils::vec2ToSf(pageOrigin));
		s.setPosition(sfmlutils::vec2ToSf(position));
		s.setRotation(rotation);

		sf::Sprite shadow = shadowSprite_;
		shadow.setOrigin(sfmlutils::vec2ToSf(pageOrigin));
		shadow.setPosition(sfmlutils::vec2ToSf(position));
		shadow.setRotation(rotation);
		sfmlutils::setFlipHorizontal(&shadow, leftPage);

		if (shader)
		{
			sf::RenderStates s2 = states;
			s2.shader = shader;
			target.draw(s, s2);
			target.draw(shadowSprite_, s2);
		}
		else
		{
			target.draw(s, states);
			target.draw(shadow, states);
		}
	}
	std::vector<sf::Sprite>& GameBook::getPages()
	{
		return pages_;
	}

	std::vector<sf::Texture>& GameBook::getTextures()
	{
		return pagesTex_;
	}
}

