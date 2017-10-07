#pragma once

#include <sfmltemplate/core/pathmanager.hpp>

namespace pages
{
	class PathManager : public sfmltemplate::PathManager
	{
	public:
		PathManager();

		std::string getFontsPath() const;
		std::string getTexturesPath() const;
	};
}