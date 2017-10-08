#include "statetest.hpp"

#include "booknode.hpp"
#include "gamebook.hpp"
#include "guifactory.hpp"
#include "resourcemanager.hpp"
#include "statemanager.hpp"

#include <scenelib/scene.hpp>
#include <sfmltemplate/core/graphics.hpp>
#include <sfmltemplate/core/inputmanager.hpp>
#include <sfmltemplate/gui/nodes/shapeshiftertogglebuttonnode.hpp>
#include <sfmltemplate/gui/scenenode.hpp>

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

	void makeNextPages(const scenelib::Scene& scene
		, GameBook& book
		, sf::Texture& paper
		, sf::Font& textFont
		, std::vector<sf::Sprite>& pages
		, std::vector<sf::Texture>& textures)
	{
		textures.push_back(sf::Texture());
		textures.push_back(sf::Texture());
		pages.push_back(sf::Sprite());
		pages.push_back(sf::Sprite());

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

		sf::Image i = result.getTexture().copyToImage();
		textures[2].loadFromImage(i);
		pages[2].setTexture(textures.back());
		pages[2].setTextureRect(sf::IntRect(0, 0, pageSize.x, pageSize.y));
		textures[3].loadFromImage(tmp);
		pages[3].setTexture(textures.back());
		pages[3].setTextureRect(sf::IntRect(0, 0, pageSize.x, pageSize.y));
	}

	void resetPages(std::vector<sf::Sprite>& pages, std::vector<sf::Texture>& textures)
	{
		textures[0] = textures[2];
		textures[1] = textures[3];
		textures[2] = sf::Texture();
		textures[3] = sf::Texture();
		pages[0] = pages[2];
		pages[1] = pages[3];
		pages[2] = sf::Sprite();
		pages[3] = sf::Sprite();
		pages[0].setTexture(textures[0]);
		pages[1].setTexture(textures[1]);
	}

	void StateTest::createButtons(sfmltemplate::SceneGraph& graph
		, GuiFactory& factory
		, const scenelib::Scene& s)
	{
		mutils::Vec2 winSize(1280, 720);
		for (int i = 0; i < s.choices.size(); ++i)
		{
			const scenelib::Choice& c = s.choices[i];
			auto button = factory.makeChoiceButton();
			button->setPosition(20, 720 - 50 - i * 30);
			button->setString(c.text);
			button->centerMiddleLeft();
			button->setAction([this, i]() {
				this->doChoice(i);
			});
			auto buttonPtr = graph.sceneRoot.attachChild(std::move(button));
			hudGraph_.registerInteractableNode(
				(sfmltemplate::AbstractInteractableNode*)buttonPtr);
			choiceButtons_.push_back((ChoiceButton*)buttonPtr);
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
		beginResetScene();
		endResetScene();

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
		if (turningPage_)
		{
			// Remove old buttons
			for (ChoiceButton* c : choiceButtons_)
			{
				hudGraph_.unregisterInteractableNode(c);
				auto ptr = hudGraph_.sceneRoot.detachChild(*c);
			}
			choiceButtons_.clear();
			endResetScene();
		}
	}

	void StateTest::doChoice(int c)
	{
		scenes_.doChoice(c);
		beginResetScene();
	}

	void StateTest::beginResetScene()
	{
		makeNextPages(scenes_.getCurrentScene(),
			*bookNode_->getBook(),
			resourceManager_.getTexture(ResourceManager::Textures::paper),
			resourceManager_.getFont(ResourceManager::Fonts::monofonto),
			bookNode_->getBook()->getPages(),
			bookNode_->getBook()->getTextures());

		turningPage_ = true;
	}

	void StateTest::endResetScene()
	{
		resetPages(bookNode_->getBook()->getPages(),
			bookNode_->getBook()->getTextures());
		createButtons(hudGraph_
			, *((GuiFactory*)&guiFactory_)
			, scenes_.getCurrentScene());
		turningPage_ = false;
	}
}

