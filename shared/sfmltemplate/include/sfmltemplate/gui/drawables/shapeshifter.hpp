#pragma once

#include <mutils/vec2.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


namespace sfmltemplate
{
	class ShapeShifter : public virtual sf::Drawable
	{
	public:
		//---------------------
		// ENUMERATIONS
		//---------------------

		//! Flags to specify the components of this button
		enum Flags
		{
			TEXT = 1 << 0,
			SPRITE = 1 << 1,
			SHAPE = 1 << 2,
			TEXT_SHADER = 1 << 3,
			SPRITE_SHADER = 1 << 4,
			SHAPE_SHADER = 1 << 5,
		};

		//! Types of shapes supported by this button
		enum class Shape
		{
			Circle,
			Rectangle,

			COUNT
		};

		//---------------------
		// MEMBER FUNCTIONS
		//---------------------

		ShapeShifter(unsigned int flags,
			Shape s = Shape::COUNT);
		virtual ~ShapeShifter();

		virtual void centerMiddleLeft();

		// Hérité via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

		virtual sf::FloatRect getBounds(mutils::Vec2 position) const;

		//! Returns the margin between the shape and other elements
		virtual mutils::Vec2 getMargin() const;

		//! Get the shape
		virtual sf::Shape* getShape() const;

		//! Get the shader used to draw the shape
		virtual sf::Shader* getShapeShader() const;

		//! Get the sprite of the button
		sf::Sprite* getSprite() const;

		//! Get the shader used to draw the sprite
		sf::Shader* getSpriteShader() const;

		//! Get the sf::Text of the button
		virtual sf::Text* getText() const;

		//! Get the shader used to draw the text
		virtual sf::Shader* getTextShader() const;

		//! Sets the margin to use between the text and the shape
		virtual void setMargin(float x, float y);
		virtual void setMargin(const mutils::Vec2& margin);

		//! Set the text's string
		virtual void setString(std::string text);

		//! Force shape to given size
		//! If rectangle : size.x = width, size.y = height
		//! If circle : size.x = radius
		void setShapeSize(mutils::Vec2 size);

		//! If the button has a shape and a sprite or text, set the shape size to the size of the other
		//! If there is both a sprite and text, the sprite's size is taken
		void setShapeSizeToContentSize();

		//! Sets button sprite to given sprite
		void setSprite(const sf::Sprite& sprite);

	protected:
		virtual void init(unsigned int f, Shape s);
		virtual void onShapeChanged();
		virtual void onSpriteChanged();
		virtual void onTextChanged();

		Shape shapeType_;

		bool hasText_;
		bool hasShape_;
		bool hasSprite_;

		mutils::Vec2 margin_;
		sf::Vector2f position_;

		sf::Text* text_;
		sf::Shader* textShader_;
		sf::Shape* shape_;
		sf::Shader* shapeShader_;
		sf::Sprite* sprite_;
		sf::Shader* spriteShader_;
	};
}