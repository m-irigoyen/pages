#pragma once

#include "pushbutton.hpp"

#include <sfmltemplate/core/guifactory.hpp>

namespace pages
{
	class GuiFactory : public sfmltemplate::GuiFactory
	{
	public:
		GuiFactory(sfmltemplate::ResourceManager* resourceManager);

		std::unique_ptr<PushButton> makePushButton() const;
	};
}

