#pragma once

#include <string>
#include <vector>

namespace scenelib
{
	struct Choice
	{
		Choice(std::string text = "", std::string nextScene = "");
		std::string text; //!< Text displayed to the player
		std::string nextScene; //!< Name of the next scene to go to
	};

	struct Scene
	{
		Scene(std::string name = "", std::string text = "");
		std::string name; //!< Name of the scene
		std::string text; //!< Text that is displayed to players
		std::vector<Choice> choices; //!< Choices offered to the player
	};
}