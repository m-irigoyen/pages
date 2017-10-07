#pragma once

#include <string>
#include <mutils/vec2.hpp>

namespace mutils
{
	class Variant
	{
	public :
		enum TYPE
		{
			BOOL
			, INT
			, UNSIGNED_INT
			, FLOAT
			, DOUBLE
			, LONG
			, CHAR
			, STRING
			, VEC2
			, UNDEFINED
		};

		Variant(bool value);
		Variant(int value);
		Variant(unsigned int value);
		Variant(float value);
		Variant(double value);
		Variant(long value);
		Variant(char value);
		Variant(const char* value);
		Variant(const std::string value);
		Variant(const Vec2 value);
		Variant(void* value = nullptr);

		bool toBool();
		int toInt();
		unsigned int toUInt();
		float toFloat();
		double toDouble();
		long toLong();
		char toChar();
		std::string toStdString();
		Vec2 toVec2();
		void* toUndef();

		TYPE t_;

	private:

		union variantValue
		{
			bool b;
			int i;
			unsigned int ui;
			float f;
			double d;
			long l;
			char c;
			std::string s;
			Vec2 v;
			void* undef;

			variantValue(void* = nullptr);
			variantValue(bool val);
			variantValue(int val);
			variantValue(unsigned int val);
			variantValue(float val);
			variantValue(double val);
			variantValue(long val);
			variantValue(char val);
			variantValue(std::string val);
			variantValue(Vec2 val);
			~variantValue();
		};

		variantValue value_;
	};
}