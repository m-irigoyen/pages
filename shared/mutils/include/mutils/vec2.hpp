#pragma once

/*
This code originates from https://github.com/SFML/SFML/wiki/Source:-2D-Vector-Manipulation,
rewritten to my naming conventions
*/

/* Includes - STL */
#include <string>

namespace mutils
{

/* Defines */
#define PI 3.14159265358979323846F

	class Vec2
	{
	public:
		/* The x and y values of this vector */
		float x, y;

		Vec2(void);
		Vec2(const Vec2&);
		Vec2(float, float);
		~Vec2(void);

		/*
		* Add and assign operator
		* @Vec2		Vector to add against
		* ->Vec2	this
		*/
		Vec2& operator+=(const Vec2);

		/*
		* Add operator
		* @Vec2		Vector for adding against
		* ->Vec2	Result
		*/
		Vec2 operator+(const Vec2) const;

		/*
		* Subtract and assign operator
		* @Vec2		Vector to subtract against
		* ->Vec2	this
		*/
		Vec2& operator-=(const Vec2);

		/*
		* Subtract operator
		* @Vec2		Vector for subtracting against
		* ->Vec2	Result
		*/
		Vec2 operator-(const Vec2) const;

		/*
		* Multiply and assign operator
		* @float		Scalar for multiplying against
		* ->Vec2	this
		*/
		Vec2& operator*=(float);

		/*
		* Multiply operator
		* @float		Scalar for multiplying against
		* ->Vec2	Result
		*/
		Vec2 operator*(float) const;

		/*
		* Divide and assign operator
		* @float		Scalar for dividing against
		* ->Vec2	this
		*/
		Vec2& operator/=(float);

		/*
		* Divide operator
		* @float		Scalar for dividing against
		* ->Vec2	Result
		*/
		Vec2 operator/(float) const;

		/*
		* Rotate and assign operator
		* @float		Theta for rotating against
		* ->Vec2	this
		*/
		Vec2& operator%=(float);

		/*
		* Rotate operator
		* @float		Theta for rotating against
		* ->Vec2	Result
		*/
		Vec2 operator%(float) const;

		/*
		* Rotate the vector
		* @float		Theta for rotating against (in degrees)
		* ->Vec2	Result
		*/
		void rotateDeg(float);

		/*
		* Rotate the vector
		* @float		Theta for rotating against (in radians)
		* ->Vec2	Result
		*/
		void rotateRad(float);

		/*
		* Rotate the vector
		* @float		Theta for rotating against (in degrees)
		* ->Vec2	Result
		*/
		Vec2 rotatedDeg(float) const;

		/*
		* Rotate the vector
		* @float		Theta for rotating against (in radians)
		* ->Vec2	Result
		*/
		Vec2 rotatedRad(float) const;

		/*
		* Equals operator
		* @Vec2		Vector for comparing against
		* ->bool		Result
		*/
		bool operator==(const Vec2);

		/*
		* Not equals operator
		* @Vec2		Vector for comparing against
		* ->bool		Result
		*/
		bool operator!=(const Vec2);

		/*
		* The dot product of this and another vector
		* @Vec2		Vector for comparing against
		* ->float		The dot product
		*/
		float dot(const Vec2);

		/*
		* The normalization of this vector
		* ->Vec2	A new vector that equals this vector normalized
		*/
		Vec2 normalize();

		/*
		* The normalization of this vector
		* ->Vec2	A new vector that equals this vector normalized
		*/
		Vec2 normalized() const;

		/*
		* Truncates this vector
		* @float		Value to truncate by
		* ->Vec2		this
		*/
		Vec2& trunc(float);

		/*
		* The angle of this vector
		* ->float		This vector's angle in radians
		*/
		float angle() const;

		/*
		* The length of this vector
		* ->float		This vector's length
		*/
		float length() const;

		/*
		* Reassigns this vector's values to the specified values
		* @float		The new x value
		* @float		The new y value
		*/
		void reassign(float, float);

		/*
		* Reassigns this vector's values to the vector
		* @Vec2		The new vector
		*/
		void reassign(Vec2);

		/*
		* Reassigns this vector's values to the vector
		* @float		Minimum value
		* @float		Maximum value
		*/
		void clamp(float min, float max);

		/*
		* Reassigns this vector's values to the vector
		* @float		Minimum x value
		* @float		Maximum x value
		* @float		Minimum y value
		* @float		Maximum y value
		*/
		void clamp(float minX, float maxX, float minY, float maxY);

		/*
		* A string representation of this vector
		* ->std::string	This vector to a string
		*/
		std::string toString() const;

		/*
		* Reassigns vector from string representation. If string is invalid, reset Vector to 0,0
		* ->std::string	The string to take values from
		* ->bool If the operation was successful
		*/
		bool fromString(const std::string& s);

		//! Same as above, static version.
		static bool fromString(const std::string& s, Vec2& result)
		{
			Vec2 v;
			return v.fromString(s);
		}

		/*
		* Convert an angle from degree to radian
		* ->float	An angle in degree
		*/
		static float degToRad(float angleInDegree);

		/*
		* Convert an angle from radian to degree
		* ->float	An angle in radian
		*/
		static float radToDeg(float angleInRadian);
	};
}