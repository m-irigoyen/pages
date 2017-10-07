#pragma once

#include <scenelib/scenemanager.hpp>

namespace scenelib
{
	class TxtParser
	{
	public:
		TxtParser();

		bool loadFromFile(SceneManager& manager, std::string filename);
	};
}