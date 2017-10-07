#include "booknode.hpp"

#include "resourcemanager.hpp"

namespace pages
{
	BookNode::BookNode()
		: SceneNode()
	{
	}
	void BookNode::drawSelf(sf::RenderTarget & target, sf::RenderStates states) const
	{
		book_.draw(target, states);
	}
	bool BookNode::init(sfmltemplate::SceneGraph & sceneGraph
		, ResourceManager* resourceManager)
	{
		return book_.init(resourceManager);
	}

	void BookNode::tick(float dt)
	{
		book_.tick(dt);
	}
	GameBook * BookNode::getBook()
	{
		return &book_;
	}
}
