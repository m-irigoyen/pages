#pragma once

#include <sfmltemplate/core/application.hpp>

namespace pages
{
	class App : public sfmltemplate::Application
	{
	public:
		App();

		virtual bool createComponents() override;

		virtual bool init() override;
	};
}