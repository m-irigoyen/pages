#include "app.hpp"

#include "guifactory.hpp"
#include "pathmanager.hpp"
#include "resourcemanager.hpp"
#include "statemanager.hpp"

#include <sfmltemplate/core/graphics.hpp>
#include <sfmltemplate/core/inputmanager.hpp>
#include <sfmltemplate/core/inputprocessor.hpp>

namespace pages
{
	App::App()
		: Application()
	{
	}

	bool App::createComponents()
	{
		pathManager_ = new PathManager();
		resourceManager_ = new ResourceManager(pathManager_);
		guiFactory_ = new GuiFactory(resourceManager_);
		stateManager_ = new StateManager();
		graphics_ = new sfmltemplate::Graphics(resourceManager_, stateManager_);
		inputManager_ = new sfmltemplate::InputManager(graphics_);
		inputProcessor_ = new sfmltemplate::InputProcessor(inputManager_);

		return true;
	}

	bool App::init()
	{
		if (!Application::init())
		{
			MUTILS_ASSERT(false);
			return false;
		}

		// Registering default inputs
		inputManager_->registerButton("touch");
		return true;
	}
}
