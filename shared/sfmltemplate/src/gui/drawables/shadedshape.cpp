//#include <sfmlhud/shadedshape.hpp>
//
//#include <mutils/assert.hpp>
//
//#include <SFML/Graphics/Shader.hpp>
//
//namespace sfmlhud
//{
//	ShadedShape::ShadedShape(unsigned int flags, AbstractHud & hud, Shape s)
//		: BasePushButton(flags | SHAPE | SHAPE_SHADER, hud, s)
//		, statusTimer_(0.f)
//	{
//	}
//
//	void ShadedShape::onStatusChanged()
//	{
//		switch (status_)
//		{
//		case Status::Clicked:
//		case Status::Hovered:
//		case Status::Rest:
//			shapeShader_->setUniform("status", (int)status_);
//			break;
//		default :
//			MUTILS_UNREACHABLE;
//		}
//	}
//
//	void ShadedShape::tick(float dt)
//	{
//		MUTILS_ASSERT(shapeShader_);
//		statusTimer_ += dt;
//		shapeShader_->setUniform("stateTimer", statusTimer_);
//	}
//
//	bool ShadedShape::isValid() const
//	{
//		return hasShape_ && shapeShader_ && (type_ != Type::COUNT);
//	}
//
//}
//
