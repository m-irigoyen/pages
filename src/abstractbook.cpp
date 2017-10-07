#include "abstractbook.hpp"

#include "resourcemanager.hpp"

#include <mutils\collision.hpp>
#include <mutils\assert.hpp>
#include <sfmlutils/vectorutils.hpp>

namespace pages
{
	using Vec2 = mutils::Vec2;

	AbstractBook::AbstractBook(
		mutils::Vec2 pageSize
		, mutils::Vec2 margin
		, float cornerPressRadius
		, Vec2 edgePressRect)
		: handleSpeed_(0.01f)
		, lagThreshold_(1.f)
		, state_(STATE::REST)
		, cornerPressRadius_(cornerPressRadius)
		, edgePressRect_(edgePressRect)
		, currentPage_(0)
	{
		// TODO assert correct sizes
		setMargin(margin);
		setPageSize(pageSize);
	}

	void AbstractBook::setHandleSpeed(float speed)
	{
		if (speed > 0.f)
		{
			handleSpeed_ = speed;
		}
	}

	void AbstractBook::setLagThreshold(float threshold)
	{
		if (threshold > 0.f)
		{
			lagThreshold_ = threshold;
		}
	}

	// Shaders
	const std::string fsDrawInClip =
#include "shaders/fsdrawinclip.hpp"
		;

	const std::string fsDrawOutClip =
#include "shaders/fsdrawoutclip.hpp"
		;

	bool AbstractBook::init(ResourceManager* resourceManager)
	{
		if (!shaderInClip_.loadFromMemory(fsDrawInClip, sf::Shader::Type::Fragment))
		{
			return false;
		}
		if (!shaderOutClip_.loadFromMemory(fsDrawOutClip, sf::Shader::Type::Fragment))
		{
			return false;
		}

		return true;
	}


	AbstractBook::STATE AbstractBook::getCurrentState() const
	{
		return state_;
	}

	AbstractBook::HOOK AbstractBook::getCurrentHook() const
	{
		return hook_;
	}

	bool AbstractBook::isInDropZone(mutils::Vec2 pos, HOOK h) const
	{
		if (state_ != STATE::TURNING)
		{
			return false;
		}

		if (isRightToLeftDirection(h))
		{
			return pos.x < pointT_.x;
		}
		else
		{
			return pos.x > pointT_.x;
		}
	}

	bool AbstractBook::isInLeftPage(Vec2 pos) const
	{
		return mutils::isInAABB(pos, pointTL_, pointB_);
	}

	bool AbstractBook::isInRightPage(mutils::Vec2 pos) const
	{
		return mutils::isInAABB(pos, pointT_, pointBR_);
	}

	void AbstractBook::inputPosition(mutils::Vec2 pos)
	{
		mousePosition_ = pos;
	}

	void AbstractBook::tick(float dt)
	{
		if (state_ == STATE::REST)
		{
			// If mouse is in a hook zone, show
			HOOK h;
			if (checkAllHookZones(mousePosition_, h) && canTurn(h))
			{
				enterShowingState(h);
			}
		}
		// If mouse left the hook zone, recover
		else if ((state_ == STATE::SHOWING) && (!checkHookZone(mousePosition_, hook_)))
		{
			// Showing, but mouse position has left hook zone. Go back to rest
			enterRecoveringState();
		}
		else if (state_ == STATE::TURNING)
		{
			handleTarget_ = mousePosition_;
		}

		// Move handle
		clampHandleTarget();
		moveHandleTowards(handleTarget_);

		// If finished recovering, rest
		if ((state_ == STATE::RECOVERING) && (handle_ == handleTarget_))
		{
			state_ = STATE::REST;
		}
		// Turn
		else if ((state_ == STATE::FINISH_TURN) && (handle_ == handleTarget_))
		{
			onTurnCompleted();
		}

		prepareDraw(dt);
	}

	void AbstractBook::inputPress(mutils::Vec2 pos)
	{
		if (!canEnterTurn(state_))
		{
			return;
		}

		HOOK h;
		if (checkAllHookZones(pos, h))
		{
			enterTurningState(h);
		}
	}

	void AbstractBook::inputRelease(mutils::Vec2 pos)
	{
		if (getCurrentState() == STATE::TURNING)
		{
			if (isInDropZone(pos, hook_))
			{
				enterFinishTurn();
			}
			else
			{
				enterRecoveringState();
			}
		}
	}

	void AbstractBook::setMode(MODE mode)
	{
		// TODO that
	}

	void AbstractBook::turnRight()
	{
		// TODO that
	}

	void AbstractBook::turnLeft()
	{
		// TODO that
	}

	void AbstractBook::goToPage(unsigned int number)
	{
		// TODO that
	}

	void AbstractBook::setPageSize(const mutils::Vec2 & size)
	{
		if ((size.x > 0) && (size.y > 0))
		{
			pageSize_ = size;
			pageDiagonal_ = size.length();
			updatePoints();
		}
	}

	mutils::Vec2 AbstractBook::getPageSize() const
	{
		return pageSize_;
	}

	mutils::Vec2 AbstractBook::getBookSize() const
	{
		return margin_ * 2 + pageSize_ * 2;
	}

	void AbstractBook::setWindowSize(mutils::Vec2 size)
	{
		windowSize_ = size;
	}

	void AbstractBook::setMargin(const mutils::Vec2 & margin)
	{
		if ((margin.x > 0) && (margin.y > 0))
		{
			margin_ = margin;
			updatePoints();
		}
	}

	mutils::Vec2 AbstractBook::getMargin() const
	{
		return margin_;
	}

	void AbstractBook::turningPagesComputation(
		mutils::Vec2& p1
		, float& maskAngle
		, Vec2 & cPos
		, Vec2 & cOrigin
		, float & cRotation
		, Vec2 & dPos
		, bool & cIsLeft) const
	{
		Vec2 handle = handle_;
		Vec2 hook, far, close, p0;

		Vec2 tmp;
		getAllTurningData(hook_, hook, tmp, far, close);

		cornerHookComputation(handle
			, hook
			, far
			, close
			, maskAngle
			, cRotation
			, p0
			, p1);

		if (isRightToLeftDirection(hook_))
		{
			dPos = pointT_;
		}
		else
		{
			dPos = pointTL_;
			if (!isCenterHook(hook_))
			{
				cRotation += 180.f;
			}
		}
		cIsLeft = isRightToLeftDirection(hook_);
		cPos = handle_;

		switch (hook_)
		{
		case HOOK::TOP_RIGHT:
			cOrigin.reassign(0.f, 0.f);
			break;
		case HOOK::BOTTOM_RIGHT:
		case HOOK::CENTER_RIGHT:
			cOrigin.reassign(0.f, pageSize_.y);
			break;
		case HOOK::TOP_LEFT:
			cOrigin.reassign(pageSize_.x, 0.f);
			break;
		case HOOK::BOTTOM_LEFT:
		case HOOK::CENTER_LEFT:
			cOrigin.reassign(pageSize_.x, pageSize_.y);
			break;
		}
	}

	void AbstractBook::setShaders(int height
		, float maskAngle
		, Vec2 p1
		, sf::Shader & shaderC
		, sf::Shader & shaderD)
	{
		Vec2 a, b, d;
		float darkestAlpha = 0.25f;
		float fadeDistance = 100.f;
		float shadowCoeff = getTurningPageCoeff();
		computeClippingMaskRect(maskAngle, p1, getClippingMaskDimensions(), a, b, d);

		shaderC.setUniform("a", sfmlutils::vec2ToSf(a));
		shaderC.setUniform("b", sfmlutils::vec2ToSf(b));
		shaderC.setUniform("d", sfmlutils::vec2ToSf(d));
		shaderC.setUniform("darkestAlpha", darkestAlpha);
		shaderC.setUniform("shadowFadeDistance", fadeDistance);
		shaderC.setUniform("shadowCoefficient", shadowCoeff);
		shaderC.setUniform("height", 600);

		shaderD.setUniform("a", sfmlutils::vec2ToSf(a));
		shaderD.setUniform("b", sfmlutils::vec2ToSf(b));
		shaderD.setUniform("d", sfmlutils::vec2ToSf(d));
		shaderD.setUniform("darkestAlpha", darkestAlpha);
		shaderD.setUniform("shadowFadeDistance", fadeDistance);
		shaderD.setUniform("shadowCoefficient", shadowCoeff);
		shaderD.setUniform("height", 600);
	}

	float AbstractBook::getTurningPageCoeff() const
	{
		return 1.f - ((getDropPoint(hook_) - handle_).length() / (pageSize_.x * 2));
	}

	void AbstractBook::clampHandleTarget()
	{
		if (state_ == STATE::TURNING)
		{
			HOOK hook = getCurrentHook();
			if (isCenterHook(hook_))
			{
				if (handleTarget_.x < pointBL_.x)
				{
					handleTarget_.x = pointBL_.x;
				}
				else if (handleTarget_.x > pointBR_.x)
				{
					handleTarget_.x = pointBR_.x;
				}

				handleTarget_.y = pointB_.y;
			}
			// CENTER
			else
			{
				// Clamping between 2 circles centered around the spine of the book
				Vec2 farV;
				Vec2 closeV;
				Vec2 hookV;
				Vec2 dropV;

				getAllTurningData(hook, hookV, dropV, farV, closeV);

				Vec2 farToH = handleTarget_ - farV;
				Vec2 closeToH = handleTarget_ - closeV;
				float FHLength = farToH.length();
				float CHLength = closeToH.length();

				// If the handle is already inside both circles, no need to clamp
				if ((FHLength < pageDiagonal_) && (CHLength < pageSize_.x))
				{
					return;
				}

				Vec2 p, dir;
				float radius;

				if (FHLength > pageDiagonal_)
				{
					p = farV;
					dir = farToH.normalized();
					radius = pageDiagonal_;
					handleTarget_ = p + dir * radius;
				}
				closeToH = handleTarget_ - closeV;
				if (closeToH.length() > pageSize_.x)
				{
					p = closeV;
					dir = closeToH.normalized();
					radius = pageSize_.x;
					handleTarget_ = p + dir * radius;
				}
			}
		}
	}

	void AbstractBook::moveHandleTowards(mutils::Vec2 pos)
	{
		mutils::Vec2 dir = pos - handle_;
		if (dir.length() <= lagThreshold_)
		{
			handle_ = pos;
		}
		else
		{
			handle_ += dir * handleSpeed_;
		}
	}

	Vec2 AbstractBook::getDropPoint(HOOK h) const
	{
		if (h != HOOK::COUNT)
		{
			switch (h)
			{
			case HOOK::BOTTOM_LEFT:
			case HOOK::CENTER_LEFT:
				return pointBR_;
			case HOOK::BOTTOM_RIGHT:
			case HOOK::CENTER_RIGHT:
				return pointBL_;
			case HOOK::TOP_LEFT:
				return pointTR_;
			case HOOK::TOP_RIGHT:
				return pointTL_;
			}
		}
		return Vec2();
	}

	Vec2 AbstractBook::getHookPoint(HOOK h) const
	{
		if (h != HOOK::COUNT)
		{
			switch (h)
			{
			case HOOK::BOTTOM_LEFT:
			case HOOK::CENTER_LEFT:
				return pointBL_;
			case HOOK::BOTTOM_RIGHT:
			case HOOK::CENTER_RIGHT:
				return pointBR_;
			case HOOK::TOP_LEFT:
				return pointTL_;
			case HOOK::TOP_RIGHT:
				return pointTR_;
			}
		}
		return Vec2();
	}

	bool AbstractBook::getAllTurningData(
		HOOK h
		, Vec2& hook
		, Vec2& drop
		, Vec2& far
		, Vec2& close) const
	{
		if (h == HOOK::COUNT)
		{
			//TODO: unreachable
			return false;
		}

		if (state_ != STATE::REST)
		{
			switch (h)
			{
			case HOOK::BOTTOM_LEFT:
			case HOOK::CENTER_LEFT:
				close = pointB_;
				far = pointT_;
				break;
			case HOOK::TOP_LEFT:
				close = pointT_;
				far = pointB_;
				break;
			case HOOK::BOTTOM_RIGHT:
			case HOOK::CENTER_RIGHT:
				close = pointB_;
				far = pointT_;
				break;
			case HOOK::TOP_RIGHT:
				close = pointT_;
				far = pointB_;
				break;
			}
			hook = getHookPoint(h);
			drop = getDropPoint(h);

			return true;
		}
		return false;
	}

	void AbstractBook::cornerHookComputation(
		Vec2 handle
		, Vec2 hook
		, Vec2, Vec2 close
		, float & maskAngle
		, float & pageCAngle
		, Vec2 & p0
		, Vec2 & p1) const
	{
		// Handle and hook are at the same position.
		if (handle == hook)
		{
			maskAngle = -45.f;
			pageCAngle = 90.f;
			p0 = handle;
			p1 = close;
			return;
		}


		// Computing clipping plane angle
		// P0 = vec(B,influence) / 2
		p0 = (handle_ + hook) / 2;
		// P1 : intersection of the segment passing by P0, perpendicular to segment handle->hook

		Vec2 p0Corner(hook - p0);

		float p0CornerAngle = atan2(p0Corner.y, p0Corner.x);
		// clipping plane angle = t0t1angle

		float p1_x = p0.x - p0Corner.y * tan(p0CornerAngle);
		// normalizing p1_x
		if (((p1_x > close.x) && (close.x > hook.x))
			|| ((p1_x < close.x) && (close.x < hook.x)))
		{
			p1_x = close.x;
		}
		p1.reassign(p1_x, close.y);

		if (p0.y == p1.y)
		{
			pageCAngle = 0.f;
			maskAngle = 90.f;
			return;
		}

		if (p0.y > p1.y)
		{
			// TODO : that one is bugged
			maskAngle = atan2(p0.y - p1.y, p0.x - p1.x) * 180.f / PI;
		}
		else
		{
			maskAngle = atan2(p1.y - p0.y, p1.x - p0.x) * 180.f / PI;
		}
		pageCAngle = atan2(p1.y - handle_.y, p1.x - handle_.x) * 180.f / PI;

		// TODO :remove
		/*std::cout << "p0		" << p0.toString() << std::endl;
		std::cout << "p1		" << p1.toString() << std::endl;
		std::cout << "page		" << pageCAngle << std::endl;
		std::cout << "mask		" << maskAngle << std::endl << std::endl;*/
	}

	void AbstractBook::computeClippingMaskRect(
		float angle
		, Vec2 p1
		, Vec2 maskSize
		, Vec2 & a
		, Vec2 & b
		, Vec2 & d) const
	{
		Vec2 dir(1, 0);
		a = p1 + dir.rotatedDeg(angle) * (maskSize.x / 2);
		b = a + (p1 - a).normalized() * maskSize.x;
		d = a + (p1 - a).normalized().rotatedDeg(90) * maskSize.y;
	}

	Vec2 AbstractBook::getClippingMaskDimensions() const
	{
		Vec2 size = getBookSize();
		return Vec2(size.x * 2.f, size.y);
	}

	void AbstractBook::updatePoints()
	{
		pointTL_ = margin_;
		pointT_ = Vec2(
			pointTL_.x + pageSize_.x,
			pointTL_.y);
		pointTR_ = Vec2(
			pointT_.x + pageSize_.x,
			pointTL_.y);
		pointBL_ = Vec2(
			pointTL_.x,
			pointTL_.y + pageSize_.y);
		pointB_ = Vec2(
			pointBL_.x + pageSize_.x,
			pointBL_.y);
		pointBR_ = Vec2(
			pointB_.x + pageSize_.x,
			pointBL_.y);
		pointC_ = Vec2(
			pointT_.x,
			pointT_.y + pageSize_.y / 2);
		pointCR_ = Vec2(
			pointTR_.x,
			pointC_.y);
		pointCL_ = Vec2(
			pointTL_.x,
			pointC_.y);
	}
	bool AbstractBook::checkAllHookZones(Vec2 pos, HOOK & hook)
	{
		for (int i = 0; i < (int)HOOK::COUNT; ++i)
		{
			if (checkHookZone(pos, (HOOK)i))
			{
				hook = (HOOK)i;
				return true;
			}
		}

		return false;
	}

	bool AbstractBook::checkHookZone(mutils::Vec2 pos, HOOK hook)
	{
		Vec2 halfEPR = edgePressRect_ / 2;
		switch (hook)
		{
		case HOOK::BOTTOM_RIGHT:
			return mutils::isInCircle(pos, pointBR_, cornerPressRadius_);
		case HOOK::BOTTOM_LEFT:
			return mutils::isInCircle(pos, pointBL_, cornerPressRadius_);
		case HOOK::TOP_RIGHT:
			return mutils::isInCircle(pos, pointTR_, cornerPressRadius_);
		case HOOK::TOP_LEFT:
			return mutils::isInCircle(pos, pointTL_, cornerPressRadius_);
		case HOOK::CENTER_RIGHT:
			return mutils::isInAABB(pos, pointCR_ - halfEPR, pointCR_ + halfEPR);
		case HOOK::CENTER_LEFT:
			return mutils::isInAABB(pos, pointCL_ - halfEPR, pointCL_ + halfEPR);
		}

		MUTILS_ASSERT(false);
		return false;
	}

	void AbstractBook::enterShowingState(HOOK h)
	{
		if ((state_ != STATE::REST) || !canTurn(h))
		{
			return;
		}

		// TODO assert h != count
		hook_ = h;
		handle_ = getHookPoint(hook_);
		switch (hook_)
		{
		case HOOK::TOP_LEFT:
			handleTarget_ = pointTL_ + Vec2(1, 1).normalized() * (cornerPressRadius_ / 2);
			break;
		case HOOK::CENTER_LEFT:
			handleTarget_ = pointBL_ + Vec2(1, 0).normalized() * (cornerPressRadius_ / 2);
			break;
		case HOOK::BOTTOM_LEFT:
			handleTarget_ = pointBL_ + Vec2(1, -1).normalized() * (cornerPressRadius_ / 2);
			break;
		case HOOK::TOP_RIGHT:
			handleTarget_ = pointTR_ + Vec2(-1, 1).normalized() * (cornerPressRadius_ / 2);
			break;
		case HOOK::CENTER_RIGHT:
			handleTarget_ = pointBR_ + Vec2(-1, 0).normalized() * (cornerPressRadius_ / 2);
			break;
		case HOOK::BOTTOM_RIGHT:
			handleTarget_ = pointBR_ + Vec2(-1, -1).normalized() * (cornerPressRadius_ / 2);
			break;
		default:
			return;
			// TODO: unreachable
		}

		state_ = STATE::SHOWING;
	}

	void AbstractBook::enterRecoveringState()
	{
		if ((state_ == STATE::TURNING) || (state_ == STATE::SHOWING))
		{
			// TODO assert h != count
			switch (hook_)
			{
			case HOOK::TOP_LEFT:
				handleTarget_ = pointTL_;
				break;
			case HOOK::TOP_RIGHT:
				handleTarget_ = pointTR_;
				break;
			case HOOK::BOTTOM_LEFT:
			case HOOK::CENTER_LEFT:
				handleTarget_ = pointBL_;
				break;
			case HOOK::BOTTOM_RIGHT:
			case HOOK::CENTER_RIGHT:
				handleTarget_ = pointBR_;
				break;
				// TODO: the rest
			}
			state_ = STATE::RECOVERING;
		}
	}

	void AbstractBook::enterTurningState(HOOK h)
	{
		if (canEnterTurn(getCurrentState()) && canTurn(h))
		{
			// TODO assert h != count
			hook_ = h;
			state_ = STATE::TURNING;
		}
	}

	void AbstractBook::enterFinishTurn()
	{
		if (state_ != STATE::TURNING)
		{
			return;
		}

		// TODO :: assert state_ is turning
		switch (hook_)
		{
		case HOOK::TOP_LEFT:
			handleTarget_ = pointTR_;
			break;
		case HOOK::TOP_RIGHT:
			handleTarget_ = pointTL_;
			break;
		case HOOK::CENTER_LEFT:
		case HOOK::BOTTOM_LEFT:
			handleTarget_ = pointBR_;
			break;
		case HOOK::BOTTOM_RIGHT:
		case HOOK::CENTER_RIGHT:
			handleTarget_ = pointBL_;
			break;
			// TODO: unreachable
		}

		state_ = STATE::FINISH_TURN;
	}

	void AbstractBook::onTurnCompleted()
	{
		if (isRightToLeftDirection(hook_))
		{
			currentPage_ += 2;
		}
		else
		{
			currentPage_ -= 2;
		}

		state_ = STATE::REST;
	}
	bool AbstractBook::canEnterTurn(STATE s) const
	{
		switch (s)
		{
		case STATE::REST:
		case STATE::SHOWING:
			return true;
		}
		return false;
	}
	bool AbstractBook::canTurn(HOOK h)
	{
		/* Return true if :
		Hook left and currentPage > 0
		Hook right and currentPage < 0
		*/

		return ((isRightToLeftDirection(h) && (currentPage_ < pages_.size() - 2))
			|| (isLeftToRightDirection(h) && (currentPage_ > 0)));
	}

	bool AbstractBook::isRightToLeftDirection(HOOK h) const
	{
		switch (h)
		{
		case HOOK::TOP_RIGHT:
		case HOOK::BOTTOM_RIGHT:
		case HOOK::CENTER_RIGHT:
			return true;
		}
		return false;
	}
	bool AbstractBook::isLeftToRightDirection(HOOK h) const
	{
		return !isRightToLeftDirection(h);
	}
	bool AbstractBook::isBottomHook(HOOK h) const
	{
		return (h == HOOK::BOTTOM_LEFT) || (h == HOOK::BOTTOM_RIGHT);
	}
	bool AbstractBook::isCenterHook(HOOK h) const
	{
		return (h == HOOK::CENTER_LEFT) || (h == HOOK::CENTER_RIGHT);
	}
	bool AbstractBook::isTopHook(HOOK h) const
	{
		return (h == HOOK::TOP_LEFT) || (h == HOOK::TOP_RIGHT);
	}
	void AbstractBook::prepareDraw(float dt)
	{
		if ((state_ == STATE::SHOWING)
			|| (state_ == STATE::TURNING)
			|| (state_ == STATE::RECOVERING)
			|| (state_ == STATE::FINISH_TURN))
		{
			// Getting all values
			Vec2 cPos, dPos, cOrigin, p1;
			bool cLeft;
			sf::Shader* cShader;
			sf::Shader* dShader;
			float cRotation, maskAngle;
			turningPagesComputation(p1, maskAngle, cPos, cOrigin, cRotation, dPos, cLeft);
			if (isRightToLeftDirection(hook_))
			{
				cShader = &shaderOutClip_;
				dShader = &shaderInClip_;
				setShaders((int)windowSize_.y, maskAngle, p1, *cShader, *dShader);
			}
			else
			{
				cShader = &shaderInClip_;
				dShader = &shaderOutClip_;
				setShaders((int)windowSize_.y, maskAngle, p1, *cShader, *dShader);
			}
		}
	}

	void AbstractBook::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		// First, draw current pages.
		drawPage(target, states, currentPage_, pointTL_, Vec2(0.f, 0.f), 0.f, true);
		drawPage(target, states, currentPage_ + 1, pointT_, Vec2(0.f, 0.f), 0.f, false);

		// Drawing the other pages if needed
		if ((state_ == STATE::SHOWING)
			|| (state_ == STATE::TURNING)
			|| (state_ == STATE::RECOVERING)
			|| (state_ == STATE::FINISH_TURN))
		{
			// Getting all values
			unsigned int pageC, pageD;
			Vec2 cPos, dPos, cOrigin, p1;
			bool cLeft;
			const sf::Shader* cShader;
			const sf::Shader* dShader;
			float cRotation, maskAngle;
			turningPagesComputation(p1, maskAngle, cPos, cOrigin, cRotation, dPos, cLeft);
			if (isRightToLeftDirection(hook_))
			{
				pageC = currentPage_ + 2;
				pageD = currentPage_ + 3;
				cShader = &shaderOutClip_;
				dShader = &shaderInClip_;
			}
			else
			{
				pageC = currentPage_ - 1;
				pageD = currentPage_ - 2;
				cShader = &shaderInClip_;
				dShader = &shaderOutClip_;
			}

			// Drawing pages
			drawPage(target
				, states
				, pageD
				, isRightToLeftDirection(hook_) ? pointT_ : pointTL_
				, Vec2(0.f, 0.f)
				, 0.f
				, !cLeft
				, dShader);

			drawPage(target
				, states
				, pageC
				, cPos
				, cOrigin
				, cRotation
				, cLeft
				, cShader);
		}
	}

}