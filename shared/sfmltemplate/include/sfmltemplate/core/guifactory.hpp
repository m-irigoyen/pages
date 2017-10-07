#pragma once

namespace sfmltemplate
{
	class ResourceManager;
	class GuiFactory
	{
	public:
		GuiFactory(ResourceManager* resourceManager);

	protected:
		ResourceManager& resourceManager_;
	};
}