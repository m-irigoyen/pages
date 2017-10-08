#pragma once

#include "choicebutton.hpp"
#include "pushbutton.hpp"

#include <sfmltemplate/core/guifactory.hpp>

namespace pages
{
	class GuiFactory : public sfmltemplate::GuiFactory
	{
	public:
		GuiFactory(sfmltemplate::ResourceManager* resourceManager);

		std::unique_ptr<PushButton> makePushButton() const;
		std::unique_ptr<ChoiceButton> makeChoiceButton() const;
	};
}

