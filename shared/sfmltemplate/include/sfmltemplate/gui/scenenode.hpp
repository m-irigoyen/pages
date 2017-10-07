#pragma once

#include <mutils/vec2.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <memory>
#include <vector>

namespace sfmltemplate
{

	class SceneNode
		: public sf::Transformable
		, public virtual sf::Drawable
		, private sf::NonCopyable
	{
	public:
		SceneNode();

		typedef std::unique_ptr<SceneNode> UniquePtr;

		virtual SceneNode* attachChild(SceneNode::UniquePtr child);
		virtual SceneNode::UniquePtr detachChild(const SceneNode& node);

		// Inherited via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
		//! Only draws children
		virtual void drawChildren(sf::RenderTarget & target, sf::RenderStates states) const;
		//! Only draws itself, not the children
		virtual void drawSelf(sf::RenderTarget & target, sf::RenderStates states) const;

		//! Get world position of the node
		virtual mutils::Vec2 getWorldPosition() const;
		//! Get world transform of the node
		virtual sf::Transform getWorldTransform() const;


		//! Do all time dependent actions on self and children
		virtual void tick(float dt);
		//! Do all time dependent actions on children only
		virtual void tickChildren(float dt);
		//! Do all time dependent actions on self only
		virtual void tickSelf(float dt);

	protected:
		std::vector<SceneNode::UniquePtr> children_;
		SceneNode* parent_;
	};
}