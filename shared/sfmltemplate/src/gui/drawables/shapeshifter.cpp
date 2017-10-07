#include <sfmltemplate/gui/drawables/shapeshifter.hpp>

#include <mutils/assert.hpp>
#include <sfmlutils/shapeutils.hpp>
#include <sfmlutils/vectorutils.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace sfmltemplate
{
	ShapeShifter::ShapeShifter(unsigned int flags, Shape s)
		: text_(nullptr)
		, shape_(nullptr)
		, sprite_(nullptr)
		, textShader_(nullptr)
		, shapeShader_(nullptr)
		, spriteShader_(nullptr)
		, shapeType_(s)
		, hasText_(false)
		, hasSprite_(false)
		, hasShape_(false)
	{
		init(flags, s);
	}
	ShapeShifter::~ShapeShifter()
	{
		if (shape_) { delete(shape_); shape_ = nullptr; }
		if (shapeShader_) { delete(shapeShader_); shapeShader_ = nullptr; }
		if (sprite_) { delete(sprite_); sprite_ = nullptr; }
		if (spriteShader_) { delete(spriteShader_); spriteShader_ = nullptr; }
		if (text_) { delete(text_); text_ = nullptr; }
		if (textShader_) { delete(textShader_); textShader_ = nullptr; }
	}

	void ShapeShifter::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (hasShape_)
		{
			states.shader = shapeShader_;
			target.draw(*shape_, states);
			states.shader = nullptr;
		}
		if (hasSprite_)
		{
			states.shader = spriteShader_;
			target.draw(*sprite_, states);
			states.shader = nullptr;
		}
		if (hasText_)
		{
			states.shader = textShader_;
			target.draw(*text_, states);
			states.shader = nullptr;
		}
	}

	sf::FloatRect ShapeShifter::getBounds(mutils::Vec2 position) const
	{
		sf::FloatRect res;
		if (hasShape_)
		{
			MUTILS_ASSERT(shape_);
			res = shape_->getGlobalBounds();
		}
		else if (hasSprite_)
		{
			MUTILS_ASSERT(sprite_);
			res = sprite_->getGlobalBounds();
		}
		else if (hasText_)
		{
			MUTILS_ASSERT(text_);
			res = text_->getGlobalBounds();
		}
		res.left += position.x;
		res.top += position.y;
		return res;
	}

	mutils::Vec2 ShapeShifter::getMargin() const
	{
		return margin_;
	}
	sf::Shape * ShapeShifter::getShape() const
	{
		return shape_;
	}
	sf::Shader * ShapeShifter::getShapeShader() const
	{
		return shapeShader_;
	}
	sf::Sprite * ShapeShifter::getSprite() const
	{
		return sprite_;
	}
	sf::Shader * ShapeShifter::getSpriteShader() const
	{
		return spriteShader_;
	}
	sf::Text * ShapeShifter::getText() const
	{
		return text_;
	}
	sf::Shader * ShapeShifter::getTextShader() const
	{
		return textShader_;
	}
	void ShapeShifter::setMargin(float x, float y)
	{
		setMargin(mutils::Vec2(x, y));
	}
	void ShapeShifter::setMargin(const mutils::Vec2 & margin)
	{
		MUTILS_ASSERT((margin.x >= 0.f) && (margin_.y >= 0.f));
		margin_ = margin;
	}
	void ShapeShifter::setString(std::string text)
	{
		if (text_)
		{
			text_->setString(text);
			sfmlutils::setOriginToCenter(*text_);
			onTextChanged();
		}
	}
	void ShapeShifter::setShapeSize(mutils::Vec2 size)
	{
		if (hasShape_)
		{
			MUTILS_ASSERT(shape_);
			if (shapeType_ == Shape::Rectangle)
			{
				MUTILS_ASSERT(size.x >= 0.f && size.y >= 0.f);
				((sf::RectangleShape*)shape_)->setSize(sfmlutils::vec2ToSf(size));
			}
			else if (shapeType_ == Shape::Circle)
			{
				MUTILS_ASSERT(size.x >= 0.f);
				((sf::CircleShape*)shape_)->setRadius(size.x);
			}
			else
			{
				MUTILS_UNREACHABLE;
			}
			sfmlutils::setOriginToCenter(*shape_);
		}
	}
	void ShapeShifter::setShapeSizeToContentSize()
	{
		if (hasShape_)
		{
			sf::FloatRect r;
			if (hasSprite_)
			{
				MUTILS_ASSERT(sprite_);
				r = sprite_->getGlobalBounds();
			}
			else if (hasText_)
			{
				MUTILS_ASSERT(text_);
				r = text_->getGlobalBounds();
			}
			else
			{
				return;
			}
			setShapeSize(mutils::Vec2(r.width, r.height));
			sfmlutils::setOriginToCenter(*shape_);
		}
	}
	void ShapeShifter::setSprite(const sf::Sprite & sprite)
	{
		sprite_ = new sf::Sprite(sprite);
		sfmlutils::setOriginToCenter(*sprite_);
	}
	void ShapeShifter::init(unsigned int flags, Shape s)
	{
		if (flags & TEXT)
		{
			text_ = new sf::Text;
			hasText_ = true;
		}
		if (flags & TEXT_SHADER)
		{
			textShader_ = new sf::Shader;
		}
		if (flags & SHAPE)
		{
			switch (s)
			{
			case Shape::Circle:
				shape_ = new sf::CircleShape;
				shapeType_ = Shape::Circle;
				break;
			case Shape::Rectangle:
				shape_ = new sf::RectangleShape;
				shapeType_ = Shape::Rectangle;
				break;
			default:
				MUTILS_UNREACHABLE;
			}
			hasShape_ = true;
		}
		if (flags & SHAPE_SHADER)
		{
			shapeShader_ = new sf::Shader;
		}
		if (flags & SPRITE)
		{
			sprite_ = new sf::Sprite;
			hasSprite_ = true;
		}
		if (flags & SPRITE_SHADER)
		{
			spriteShader_ = new sf::Shader;
		}
	}
	void ShapeShifter::onShapeChanged()
	{
	}
	void ShapeShifter::onSpriteChanged()
	{
	}
	void ShapeShifter::onTextChanged()
	{
		if (hasShape_)
		{
			MUTILS_ASSERT(shape_);
			sf::FloatRect textBounds = text_->getGlobalBounds();
			if (shapeType_ == Shape::Rectangle)
			{
				((sf::RectangleShape*)shape_)->setSize(sf::Vector2f(textBounds.width + margin_.x * 2
					, textBounds.height + margin_.y * 2));
			}
			else
			{
				((sf::CircleShape*)shape_)->setRadius(std::max(textBounds.width + margin_.x
					, textBounds.height + margin_.y));
			}
			sfmlutils::setOriginToCenter(*shape_);
		}
	}
}

