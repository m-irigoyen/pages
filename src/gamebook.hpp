#pragma once

#include "abstractbook.hpp"

namespace pages
{
	class GameBook : public AbstractBook
	{
	public:
		GameBook();

		virtual bool init(ResourceManager* manager) override;

		// Hérité via AbstractBook
		virtual void drawPage(sf::RenderTarget & target
			, sf::RenderStates states
			, unsigned int pageNb
			, mutils::Vec2 position
			, mutils::Vec2 pageOrigin
			, float rotation
			, bool leftPage
			, const sf::Shader * shader = nullptr) const override;

		std::vector<sf::Sprite>& getPages();
		std::vector<sf::Texture>& getTextures();
	};
}