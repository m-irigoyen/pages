#include <sfmltemplate/core/resourcemanager.hpp>

#include <sfmltemplate/core/pathmanager.hpp>

#include <mutils/assert.hpp>

namespace sfmltemplate
{
	ResourceManager::ResourceManager(PathManager * paths)
		: paths_(*paths)
	{
	}

	ResourceManager::~ResourceManager()
	{
	}
	sf::Texture & ResourceManager::getTexture(index id)
	{
		MUTILS_ASSERT(id >= 0);
		return textureHolder_.get(id);
	}
	sf::Font & ResourceManager::getFont(index id)
	{
		MUTILS_ASSERT(id >= 0);
		return fontHolder_.get(id);
	}

	PathManager * ResourceManager::getPathManager() const
	{
		return &paths_;
	}
}