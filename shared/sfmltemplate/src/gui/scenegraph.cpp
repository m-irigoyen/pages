#include <sfmltemplate/gui/scenegraph.hpp>

#include <mutils/assert.hpp>
#include <mutils/vectorutils.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace sfmltemplate
{
	using InteractableVector = std::vector<AbstractInteractableNode*>;

	SceneGraph::SceneGraph()
	{
	}
	SceneGraph::~SceneGraph()
	{
	}

	void SceneGraph::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		sceneRoot.draw(target, states);
	}

	void SceneGraph::onCursorMove(mutils::Vec2 cursorPos)
	{
		for (AbstractInteractableNode* i : interactables_)
		{
			i->onCursorMove(cursorPos);
		}
	}

	bool SceneGraph::onCursorPress(mutils::Vec2 cursorPos)
	{
		for (AbstractInteractableNode* i : interactables_)
		{
			if (i->checkTouchBegin(cursorPos))
			{
				return true;
			}
		}
		return false;
	}

	bool SceneGraph::onCursorRelease(mutils::Vec2 cursorPos)
	{
		for (AbstractInteractableNode* i : interactables_)
		{
			if (i->checkTouchEnd(cursorPos))
			{
				return true;
			}
		}
		return false;
	}

	void SceneGraph::registerInteractableNode(AbstractInteractableNode* i)
	{
		mutils::addUnique(interactables_, i);
	}

	void SceneGraph::unregisterInteractableNode(AbstractInteractableNode* i)
	{
		mutils::eraseOne(interactables_, i);
	}

	void SceneGraph::tick(float dt)
	{
		sceneRoot.tick(dt);
	}
}


