#pragma once

#include "choicebutton.hpp"

#include <scenelib/scenemanager.hpp>

#include <sfmltemplate/core/abstractstate.hpp>

namespace pages
{
	class BookNode;
	class GuiFactory;
	class ResourceManager;
	class StateManager;
	class StateTest : public sfmltemplate::AbstractState
	{
	public:
		StateTest(sfmltemplate::Graphics* graphics
			, sfmltemplate::GuiFactory* guiFactory
			, sfmltemplate::InputManager* inputManager
			, ResourceManager* resourceManager
			, StateManager* stateManager);

		// H�rit� via AbstractState
		virtual bool clear() override;
		virtual bool init() override;
		virtual void tick(float dt) override;

		void doChoice(int c);
		void beginResetScene(bool init = false);
		void endResetScene();

	protected:
		void createButtons(sfmltemplate::SceneGraph& graph
			, GuiFactory& factory
			, const scenelib::Scene& s);

		BookNode* bookNode_;
		scenelib::SceneManager scenes_;
		std::vector<ChoiceButton*> choiceButtons_;

		bool finishedTurningPage_;
		bool turningPage_;
		float turnTime_;
		mutils::Vec2 midPoint_;
		/*virtual void draw(
		sf::RenderTarget & target
		, sf::RenderStates states) const override;*/
	};
}