#include "..\shared\sfmltemplate\include\sfmltemplate\core\resourcemanager.hpp"
#include "resourcemanager.hpp"

#include "pathmanager.hpp"

namespace pages
{
	ResourceManager::ResourceManager(sfmltemplate::PathManager* pm)
		: sfmltemplate::ResourceManager(pm)
	{
	}

	bool pages::ResourceManager::clear()
	{
		return true;
	}

	bool pages::ResourceManager::init()
	{
		// Loading fonts
		fontHolder_.load(Fonts::monofonto
			, ((PathManager&)paths_).getFontsPath() + "/monofonto.ttf");

		// Loading textures
		textureHolder_.load(Textures::paper,
			((PathManager&)paths_).getTexturesPath() + "/paper.png");

		return true;
	}
}
