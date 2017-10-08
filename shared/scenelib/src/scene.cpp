#include "..\include\scenelib\scene.hpp"

namespace scenelib
{
	Choice::Choice(std::string t, std::string nS)
		: text(t)
		, nextScene(nS)
	{
	}
	Scene::Scene(std::string n, std::string t)
		: name(n)
		, text(t)
		, isRedirection(false)
	{
	}
}