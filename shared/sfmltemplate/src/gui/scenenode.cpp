#include <sfmltemplate/gui/scenenode.hpp>

#include <mutils/assert.hpp>
#include <sfmlutils/vectorutils.hpp>

namespace sfmltemplate
{
	SceneNode::SceneNode()
		: parent_(nullptr)
	{

	}
	SceneNode* SceneNode::attachChild(SceneNode::UniquePtr child)
	{
		MUTILS_ASSERT(child->parent_ == nullptr);
		child->parent_ = this;
		children_.push_back(std::move(child));
		return children_.back().get();
	}

	SceneNode::UniquePtr SceneNode::detachChild(const SceneNode & node)
	{
		auto found = std::find_if(children_.begin(), children_.end(),
			[&](SceneNode::UniquePtr& p) -> bool
		{
			return p.get() == &node;
		});

		MUTILS_ASSERT(found != children_.end());

		SceneNode::UniquePtr result = std::move(*found);
		result->parent_ = nullptr;
		children_.erase(found);
		return result;
	}

	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= getTransform();	//Get the node's transform, and apply it to states
		drawSelf(target, states);
		drawChildren(target, states);
	}

	void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
	{
		for (const SceneNode::UniquePtr& child : children_)
		{
			child->draw(target, states);
		}
	}

	void SceneNode::drawSelf(sf::RenderTarget & target, sf::RenderStates states) const
	{
	}

	mutils::Vec2 SceneNode::getWorldPosition() const
	{
		return sfmlutils::sfToVec2(getWorldTransform() * sf::Vector2f());
	}

	sf::Transform SceneNode::getWorldTransform() const
	{
		sf::Transform t = sf::Transform::Identity;
		// Going up the scene graph
		for (const SceneNode* node = this
			; node != nullptr
			; node = node->parent_)
		{
			t = node->getTransform() * t;
		}
		return t;
	}

	void SceneNode::tick(float dt)
	{
		tickSelf(dt);
		tickChildren(dt);
	}
	void SceneNode::tickChildren(float dt)
	{
		for (const SceneNode::UniquePtr& child : children_)
		{
			child->tick(dt);
		}
	}
	void SceneNode::tickSelf(float dt)
	{
	}
}