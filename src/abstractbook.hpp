#pragma once

#include <mutils/vec2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

namespace pages
{
	class ResourceManager;
	/*
	The Book class encapsulates the logic of an interactable book. The player can turn pages by
	clicking and draging pages around
	*/
	class AbstractBook : public sf::Drawable
	{
	public:
		enum class MODE
		{
			INTERACTIVE,
			AUTOMATIC,
			GOTO,	// The book is currently going to a certain page, flapping pages in between

			COUNT
		};

		enum class STATE
		{
			REST,	// Nothing is happening
			SHOWING,	// showing a bit of next/previous page
			TURNING,
			FINISH_TURN, // User dropped the turn in drop zone, finishing it
			RECOVERING, // User dropped the turn outside of drop zone, going back

			COUNT
		};

		enum class HOOK
		{
			TOP_LEFT,
			CENTER_LEFT,
			BOTTOM_LEFT,
			TOP_RIGHT,
			CENTER_RIGHT,
			BOTTOM_RIGHT,

			COUNT
		};

		AbstractBook(
			mutils::Vec2 pageSize
			, mutils::Vec2 margin
			, float cornerPressRadius
			, mutils::Vec2 edgePressRect);

		//! The speed (unit/call) at which the handle will catch up with player input
		virtual void setHandleSpeed(float speed);

		//! The threshold distance below which the handle should immediately snap to player input
		virtual void setLagThreshold(float threshold);

		virtual bool init(ResourceManager* resourceManager);

		virtual STATE getCurrentState() const;

		virtual bool isInDropZone(mutils::Vec2 pos, HOOK h) const;

		virtual bool isInLeftPage(mutils::Vec2 pos) const ;
		virtual bool isInRightPage(mutils::Vec2 pos) const ;

		// Handle positions

		/*! Returns current acceptable drop zone
		*	drop is the center point of the drop zone
		*	isCircle is true if the zone is a circle. If false, then its an AABB
		*	dimensions is (radius,radius) if isCircle == true, else its the (witdh,height)
		*/

		/*virtual bool getHandleDropPoint(mutils::Vec2& drop
			, bool& isCircle
			, mutils::Vec2& dimensions);*/


		// Events

		//! Update tracker position based on tracker speed and lag threshold
		virtual void inputPosition(mutils::Vec2 pos);

		//! In case you want the book state to change without caring about mouse position
		virtual void tick(float dt);

		//! Mouse/touch press event at given position
		virtual void inputPress(mutils::Vec2 pos);

		//! Mouse/touch release event at given position
		virtual void inputRelease(mutils::Vec2 pos);


		// Automatic mode
		virtual void setMode(MODE mode);

		//! Turn to next page if possible
		virtual void turnRight();

		//! Turn to previous page if possible
		virtual void turnLeft();

		//! Force the book in automatic mode and go to given page
		virtual void goToPage(unsigned int number);

		// SIZES
		virtual void setPageSize(const mutils::Vec2& size);
		virtual mutils::Vec2 getPageSize() const;

		virtual void setMargin(const mutils::Vec2& margin);
		virtual mutils::Vec2 getMargin() const;

		//! Returns book global size (margin + *2 page size)
		virtual mutils::Vec2 getBookSize() const;

		virtual void setWindowSize(mutils::Vec2 size);

		// Hérité via Drawable
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

		bool tryTurn(HOOK h);

		bool getAllTurningData(
			HOOK h
			, mutils::Vec2& hook
			, mutils::Vec2& drop
			, mutils::Vec2& far
			, mutils::Vec2& close
		) const;

		void forcePage(unsigned int pageNb);

		virtual void prepareDraw(float dt);


	protected:
		// Functions
		void turningPagesComputation(
			mutils::Vec2& p1
			, float& maskAngle
			, mutils::Vec2& cPos
			, mutils::Vec2& cOrigin
			, float& cRotation
			, mutils::Vec2& dPos
			, bool& cIsLeft) const;

		void setShaders(int height,
			float maskAngle
			, mutils::Vec2 p1
			, sf::Shader& c
			, sf::Shader& d);

		float getTurningPageCoeff() const;

		//! Clamps tracker based on current mode
		virtual void clampHandleTarget();

		virtual void moveHandleTowards(mutils::Vec2 pos);

		virtual HOOK getCurrentHook() const;
		virtual mutils::Vec2 getDropPoint(HOOK h) const;
		virtual mutils::Vec2 getHookPoint(HOOK h) const;

		virtual void cornerHookComputation(
			mutils::Vec2 handle
			, mutils::Vec2 hook
			, mutils::Vec2 far
			, mutils::Vec2 close
			, float& maskAngle
			, float& pageCAngle
			, mutils::Vec2 & p0
			, mutils::Vec2& p1) const;

		virtual void computeClippingMaskRect(
			float angle
			, mutils::Vec2 p1
			, mutils::Vec2 dimensions
			, mutils::Vec2& a
			, mutils::Vec2& b
			, mutils::Vec2& d) const;

		mutils::Vec2 getClippingMaskDimensions() const;

		//! Update the point positions
		virtual void updatePoints();

		//! Check if given position is inside any hook zone
		virtual bool checkAllHookZones(mutils::Vec2 pos, HOOK& hook);
		//! Check if given point is inside given hook zone
		virtual bool checkHookZone(mutils::Vec2 pos, HOOK hook);

		virtual void enterShowingState(HOOK h);
		virtual void enterRecoveringState();
		virtual void enterTurningState(HOOK h);
		virtual void enterFinishTurn();
		virtual void onTurnCompleted();

		virtual bool canEnterTurn(STATE s) const;

		//! Returns true if there are pages behind this book. False means you've reached the end
		//! of the book
		virtual bool canTurn(HOOK h);

		virtual bool isRightToLeftDirection(HOOK h) const;
		virtual bool isLeftToRightDirection(HOOK h) const;
		virtual bool isBottomHook(HOOK h) const;
		virtual bool isCenterHook(HOOK h) const;
		virtual bool isTopHook(HOOK h) const;


		// Attributes
		STATE state_;	//!< Current state of the book
		HOOK hook_;	//!< Point where the tracker is hooked on the turning page

		float lagThreshold_;	//!< Minimal distance below which the tracker shoudl snap to input
		float handleSpeed_;	//!< Speed at which the tracker follows input

		// Press tolerance is how far of the hook_point
		float cornerPressRadius_;
		mutils::Vec2 edgePressRect_;

		mutils::Vec2 mousePosition_; //!< Last known position of mouse
		mutils::Vec2 handleTarget_; //!< Point the handle wants to reach
		mutils::Vec2 handle_; //!< Handle that lags behind player input

		std::vector<sf::Texture> pagesTex_; //!< Textures of the pages
		std::vector<sf::Sprite> pages_;	//!< Sprites of the pages

		// Shadows
		sf::Texture shadowTex_;
		sf::Sprite shadowSprite_;

		// Size
		mutils::Vec2 windowSize_; //!< Size of the rendering window
		mutils::Vec2 margin_;
		mutils::Vec2 pageSize_;
		float pageDiagonal_;

		// Values stored to speed up computations
		mutils::Vec2 pointTL_;
		mutils::Vec2 pointT_;
		mutils::Vec2 pointTR_;
		mutils::Vec2 pointBL_;
		mutils::Vec2 pointB_;
		mutils::Vec2 pointBR_;
		mutils::Vec2 pointC_;
		mutils::Vec2 pointCL_;
		mutils::Vec2 pointCR_;

		// Current page
		unsigned int currentPage_;

		// Shaders to draw pages
		sf::Shader shaderInClip_;
		sf::Shader shaderOutClip_;



		//! Draws a single page
		virtual void drawPage(sf::RenderTarget & target
			, sf::RenderStates states
			, unsigned int pageNb
			, mutils::Vec2 position
			, mutils::Vec2 pageOrigin
			, float rotation
			, bool leftPage
			, const sf::Shader* shader = nullptr) const = 0;
};
}
