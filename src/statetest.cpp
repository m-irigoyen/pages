#include "statetest.hpp"

#include "booknode.hpp"
#include "gamebook.hpp"
#include "guifactory.hpp"
#include "resourcemanager.hpp"
#include "statemanager.hpp"

#include <sfmltemplate/core/graphics.hpp>
#include <sfmltemplate/core/inputmanager.hpp>
#include <sfmltemplate/gui/nodes/shapeshiftertogglebuttonnode.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <vector>

namespace pages
{
	StateTest::StateTest(
		sfmltemplate::Graphics * graphics
		, sfmltemplate::GuiFactory * guiFactory
		, sfmltemplate::InputManager * inputManager
		, ResourceManager * resourceManager
		, StateManager * stateManager)
		: AbstractState(graphics, guiFactory, inputManager, resourceManager, stateManager, 0)
	{

	}

	bool StateTest::clear()
	{
		return true;
	}

	sf::Text fitToPage(sf::Text& text, mutils::Vec2 textSize)
	{
		sf::FloatRect bounds = text.getGlobalBounds();
		if ((bounds.width <= textSize.x) && (bounds.height <= textSize.y))
		{
			return text;
		}

		// Too wide : need to cut.
		sf::Text result = text;
		result.setString("");
		sf::String completeStr = text.getString();
		sf::String tmp = result.getString();
		sf::String str = result.getString();
		for (int i = 0; i < completeStr.getSize(); ++i)
		{
			result.setString(str + completeStr[i]);
			bounds = result.getGlobalBounds();
			if ((bounds.width <= textSize.x) && (bounds.height <= textSize.y))
			{
				str += completeStr[i];
			}
			else
			{
				str += "\n" + completeStr[i];
			}
		}

		result.setString(str);
		return result;
	}

	void makePages(const scenelib::Scene& scene
		, GameBook& book
		, sf::Texture& paper
		, sf::Font& textFont
		, std::vector<sf::Sprite>& pages
		, std::vector<sf::Texture>& textures)
	{
		mutils::Vec2 pageSize = book.getPageSize();
		mutils::Vec2 pageMargin = mutils::Vec2(10, 10);

		sf::RenderTexture result;
		if (!result.create(pageSize.x, pageSize.y))
		{
			MUTILS_ASSERT(false);
			return;
		}

		// First, paper
		sf::Sprite paperSprite;
		paperSprite.setTexture(paper);
		result.draw(paperSprite);
		result.display();
		sf::Image tmp = result.getTexture().copyToImage();

		// Then ,the description text
		sf::Text t;
		t.setFont(textFont);
		t.setCharacterSize(14);
		t.setString(scene.text);
		t.setFillColor(sf::Color::Black);
		t = fitToPage(t, pageSize - mutils::Vec2(20, 20));
		t.setPosition(10, 10);
		result.draw(t);
		result.display();

		{
			sf::Image i = result.getTexture().copyToImage();
			i.saveToFile("c:/test/page1buildbefore.png");
			textures.push_back(sf::Texture());
			textures.back().loadFromImage(i);
			sf::Sprite s;
			s.setTexture(textures.back());
			pages.push_back(s);
			textures.back().copyToImage().saveToFile("c:/test/page1build.png");
		}
		{
			textures.push_back(sf::Texture());
			textures.back().loadFromImage(tmp);
			sf::Sprite s;
			s.setTexture(textures.back());
			pages.push_back(s);
		}
	}

	bool StateTest::init()
	{
		// Book stuff
		std::unique_ptr<BookNode> book(new BookNode);
		book->init(worldGraph_, (ResourceManager*)&resourceManager_);
		bookNode_ = (BookNode*)(hudGraph_.sceneRoot.attachChild(std::move(book)));

		scenes_.loadTestProject();

		// Make first pages
		makePages(scenes_.getCurrentScene(),
			*bookNode_->getBook(),
			resourceManager_.getTexture(ResourceManager::Textures::paper),
			resourceManager_.getFont(ResourceManager::Fonts::monofonto),
			bookNode_->getBook()->getPages(),
			bookNode_->getBook()->getTextures());

		return true;
	}



	void StateTest::tick(float dt)
	{
		AbstractState::tick(dt);


		if (scenes_.end)
		{
			stateManager_.requestQuit = true;
			return;
		}


		// TODO that
	}
}
