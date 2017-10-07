#include <sfmltemplate/core/pathmanager.hpp>

namespace sfmltemplate
{
	PathManager::PathManager()
	{
	}
	PathManager::~PathManager()
	{
	}

	std::string PathManager::getResourcesPath() const
	{
#ifndef NDEBUG
		// Debug
		return "../resources";
#else
		// RELEASE
		return "resources";
#endif
	}
	bool PathManager::init()
	{
		return true;
	}
}