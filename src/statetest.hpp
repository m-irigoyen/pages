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

		// Hérité via AbstractState
		virtual bool clear() override;
		virtual bool init() override;
		virtual void tick(float dt) override;

		void doChoice(int c);
		void beginResetScene();
		void endResetScene();

	protected:
		void createButtons(sfmltemplate::SceneGraph& graph
			, GuiFactory& factory
			, const scenelib::Scene& s);

		BookNode* bookNode_;
		scenelib::SceneManager scenes_;
		std::vector<ChoiceButton*> choiceButtons_;

		bool turningPage_;
		/*virtual void draw(
		sf::RenderTarget & target
		, sf::RenderStates states) const override;*/
	};
}