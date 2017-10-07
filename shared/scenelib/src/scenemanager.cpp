#include <scenelib/scenemanager.hpp>
#include "yamlparser.hpp"

#include <mutils/assert.hpp>
#include <mutils/stringutils.hpp>

#include <iostream>

namespace scenelib
{
	void logError(std::string sceneName, int nbChoice, std::string error)
	{
		std::cout << "[" << sceneName << "](choice " << nbChoice << ") : "
			<< error << std::endl;
	}

	void logError(std::string sceneName, std::string error)
	{
		std::cout << "[" << sceneName << "]" << " : " << error << std::endl;
	}

	void logError(std::string error)
	{
		std::cout << "ERROR : " << error << std::endl;
	}


	SceneManager::SceneManager()
		: end(false)
		, currentScene_(scenes_.end())
	{
	}

	void SceneManager::doChoice(int choiceNb)
	{
		MUTILS_ASSERT((currentScene_ != scenes_.end()
			&& (choiceNb >= 0)
			&& (choiceNb < currentScene_->second.choices.size())));

		goToScene(currentScene_->second.choices[choiceNb].nextScene);
	}

	bool SceneManager::exists(std::string sceneName) const
	{
		return scenes_.find(sceneName) != scenes_.end();
	}

	const Scene & SceneManager::getCurrentScene() const
	{
		// TODO: insérer une instruction return ici
		MUTILS_ASSERT(currentScene_ != scenes_.end());
		return currentScene_->second;
	}

	void SceneManager::goToScene(std::string sceneName)
	{
		if (mutils::compare(sceneName, "end"))
		{
			end = true;
			currentScene_ = scenes_.end();
		}
		else
		{
			MUTILS_ASSERT(exists(sceneName));
			currentScene_ = scenes_.find(sceneName);
		}
	}

	bool SceneManager::isValid() const
	{
		if (scenes_.empty())
		{
			MUTILS_ASSERT(false);
			logError("No scenes loaded");
			return false;
		}

		bool ok = true;
		for (auto it = scenes_.begin();
			it != scenes_.end();
			++it)
		{
			if (it->first.empty())
			{
				MUTILS_ASSERT(false);
				logError(it->second.name, "Empty scene id in the map");
				ok = false;
			}
			if (it->second.name.empty())
			{
				MUTILS_ASSERT(false);
				logError(it->second.name, "Empty scene name");
				ok = false;
			}
			if (it->second.text.empty())
			{
				MUTILS_ASSERT(false);
				logError(it->second.name, "Empty scene description");
				ok = false;
			}
			if (it->second.choices.empty())
			{
				MUTILS_ASSERT(false);
				logError(it->second.name, "Scene doesn't have choices");
				ok = false;
			}
			else
			{
				int i = 0;
				for (auto itChoices = it->second.choices.begin();
					itChoices != it->second.choices.end();
					++it)
				{
					if (itChoices->text.empty())
					{
						MUTILS_ASSERT(false);
						logError(it->second.name, i, "Scene doesn't have choices");
						ok = false;
					}
					if (itChoices->nextScene.empty())
					{
						MUTILS_ASSERT(false);
						logError(it->second.name, i, "No next scene to go to");
						ok = false;
					}
					if (!mutils::compare(itChoices->nextScene, "end")
						&& !exists(itChoices->nextScene))
					{
						MUTILS_ASSERT(false);
						logError(it->second.name, i, "Scene " + it->second.name
							+ " doesn't exist");
						ok = false;
					}
					++i;
				}
			}
		}
		return ok;
	}

	bool SceneManager::loadFromFile(std::string file)
	{
		scenes_.clear();
		currentScene_ = scenes_.end();

		YAMLParser parser;
		if (!parser.loadYAMLFromFile(*this, file))
		{
			MUTILS_ASSERT(false);
			return false;
		}

		if (!isValid())
		{
			MUTILS_ASSERT(false);
			return false;
		}

		return isValid();
	}
	bool SceneManager::loadTestProject()
	{
		scenes_.clear();
		currentScene_ = scenes_.end();

		Scene s1("begin", "This is a test scene. It describes a test scene.\nYeah.\n\n\nJust do something okay ?");
		s1.choices.push_back(Choice("Do something.", "nice"));
		s1.choices.push_back(Choice("Do nothing.", "nothing"));
		s1.choices.push_back(Choice("Twiddle your thumbs around.", "nothing"));
		scenes_.insert(std::make_pair(s1.name, s1));

		Scene s2("nice", "Good, good. That's it. Game over man. Congratulations.");
		s2.choices.push_back(Choice("Well that was easy.", "end"));
		scenes_.insert(std::make_pair(s2.name, s2));

		Scene s3("nothing", "... Why do I get all the dumb ones ?  Ok, let's try again.");
		s3.choices.push_back(Choice("Ok", "begin"));
		scenes_.insert(std::make_pair(s3.name, s3));

		currentScene_ = scenes_.find("begin");

		return true;
	}
}