#pragma once

#include <scenelib/scene.hpp>

#include <map>
#include <string>

namespace scenelib
{
	class YAMLParser;
	class SceneManager
	{
	public:
		friend YAMLParser;

		typedef std::map<std::string, Scene> SceneMap;
		SceneManager();

		void doChoice(int choiceNb);

		bool exists(std::string sceneName) const;

		const Scene& getCurrentScene() const;

		void goToScene(std::string sceneName);

		//! Returns true if some scenes are loaded, and there is no error in the scenes
		bool isValid() const;

		bool loadFromFile(std::string file);
		bool loadTestProject();

		bool end;
		bool changed;

	protected:
		SceneMap scenes_;
		SceneMap::iterator currentScene_;
	};
}