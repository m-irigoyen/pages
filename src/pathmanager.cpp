#include "pathmanager.hpp"

namespace pages
{
	PathManager::PathManager()
		: sfmltemplate::PathManager()
	{

	}

	std::string pages::PathManager::getFontsPath() const
	{
		return getResourcesPath() + "/fonts";
	}

	std::string pages::PathManager::getTexturesPath() const
	{
		return getResourcesPath() + "/textures";
	}
}