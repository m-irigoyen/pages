#pragma once

namespace sfmltemplate
{
	class Graphics;
	class GuiFactory;
	class InputManager;
	class InputProcessor;
	class PathManager;
	class ResourceManager;
	class StateManager;
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual bool createComponents() = 0;
		virtual bool init();
		virtual bool run();
		virtual void close();

	protected:
		Graphics* graphics_;
		GuiFactory* guiFactory_;
		InputManager* inputManager_;
		InputProcessor* inputProcessor_;
		PathManager* pathManager_;
		ResourceManager* resourceManager_;
		StateManager* stateManager_;
	};
}
