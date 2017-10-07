#include <sfmltemplate/core/guifactory.hpp>

#include <sfmltemplate/core/resourcemanager.hpp>

#include <mutils/assert.hpp>

namespace sfmltemplate
{
	GuiFactory::GuiFactory(ResourceManager * res)
		: resourceManager_(*res)
	{
	}
}
