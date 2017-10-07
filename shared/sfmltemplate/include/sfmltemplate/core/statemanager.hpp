#pragma once

namespace sfmltemplate
{
	class AbstractState;
	class Graphics;
	class GuiFactory;
	class InputManager;
	class ResourceManager;
	class StateManager
	{
	public:
		StateManager();
		~StateManager();

		// Initialize the graphics engine
		virtual bool init(Graphics* graphics
			, GuiFactory* guiFactory
			, InputManager* inputManager
			, ResourceManager* resourceManager
			, StateManager* stateManager) = 0;

		virtual AbstractState* getCurrentState() = 0;
		virtual int getCurrentStateId() const = 0;
		virtual void setState(int id) = 0;
		virtual void goToPreviousState() = 0;

		bool requestQuit;

	protected:
		float timer_;
		int currentState_;
		int previousState_;
	};
}