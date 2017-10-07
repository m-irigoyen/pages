#pragma once

#include <string>

namespace scenelib
{
	class SceneManager;
	class YAMLParser
	{
	public:
		YAMLParser();

		bool loadYAMLFromFile(SceneManager& manager, std::string file);
	};
}