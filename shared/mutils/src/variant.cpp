#include <mutils/variant.hpp>

#include <mutils/assert.hpp>

namespace mutils
{
	Variant::Variant(bool value)
		: t_(BOOL)
		, value_(value)
	{
	}

	Variant::Variant(int value)
		: t_(INT)
		, value_(value)
	{
	}

	Variant::Variant(unsigned int value)
		: t_(UNSIGNED_INT)
		, value_(value)
	{
	}

	Variant::Variant(float value)
		: t_(FLOAT)
		, value_(value)
	{
	}

	Variant::Variant(double value)
		: t_(DOUBLE)
		, value_(value)
	{
	}

	Variant::Variant(long value)
		: t_(LONG)
		, value_(value)
	{
	}

	Variant::Variant(char value)
		: t_(CHAR)
		, value_(value)
	{
	}

	Variant::Variant(const char * value)
		: t_(STRING)
		, value_(std::string(value))
	{
	}

	Variant::Variant(const std::string value)
		: t_(STRING)
		, value_(value)
	{
	}

	Variant::Variant(const Vec2 value)
		: t_(VEC2)
		, value_(value)
	{
	}

	Variant::Variant(void * value)
		: t_(UNDEFINED)
		, value_(value)
	{
	}

	bool Variant::toBool()
	{
		switch (t_)
		{
		case BOOL:
			return value_.b;
		case INT:
			return value_.i != 0;
		case UNSIGNED_INT:
			return value_.ui != 0;
		case FLOAT:
			return value_.f != 0.f;
		case DOUBLE:
			return value_.d != 0.0;
		case LONG:
			return value_.l != 0;
		default:
			MUTILS_ASSERT(false);
		}
		return false;
	}

	int Variant::toInt()
	{
		switch (t_)
		{
		case BOOL:
			return (int)value_.b;
		case INT:
			return value_.i;
		case UNSIGNED_INT:
			return (int)value_.ui;
		case FLOAT:
			return (int)value_.f;
		case DOUBLE:
			return (int)value_.d;
		case LONG:
			return (int)value_.l;
		default:
			MUTILS_ASSERT(false);
		}
		return 0;
	}

	unsigned int Variant::toUInt()
	{
		switch (t_)
		{
		case BOOL:
			return (unsigned int)value_.b;
		case INT:
			return (unsigned int)value_.i;
		case UNSIGNED_INT:
			return value_.ui;
		case FLOAT:
			return (unsigned int)value_.f;
		case DOUBLE:
			return (unsigned int)value_.d;
		case LONG:
			return (unsigned int)value_.l;
		default:
			MUTILS_ASSERT(false);
		}
		return 0;
	}

	float Variant::toFloat()
	{
		switch (t_)
		{
		case BOOL:
			return (float)value_.b;
		case INT:
			return (float)value_.i;
		case UNSIGNED_INT:
			return (float)value_.ui;
		case FLOAT:
			return value_.f;
		case DOUBLE:
			return (float)value_.d;
		case LONG:
			return (float)value_.l;
		default:
			MUTILS_ASSERT(false);
		}
		return 0.f;
	}

	double Variant::toDouble()
	{
		switch (t_)
		{
		case BOOL:
			return (double)value_.b;
		case INT:
			return (double)value_.i;
		case UNSIGNED_INT:
			return (double)value_.ui;
		case FLOAT:
			return (double)value_.f;
		case DOUBLE:
			return value_.d;
		case LONG:
			return (double)value_.l;
		default:
			MUTILS_ASSERT(false);
		}
		return 0.0;
	}

	long Variant::toLong()
	{
		switch (t_)
		{
		case BOOL:
			return (long)value_.b;
		case INT:
			return (long)value_.i;
		case UNSIGNED_INT:
			return (long)value_.ui;
		case FLOAT:
			return (long)value_.f;
		case DOUBLE:
			return (long)value_.d;
		case LONG:
			return value_.l;
		default:
			MUTILS_ASSERT(false);
		}
		return 0;
	}

	char Variant::toChar()
	{
		switch (t_)
		{
		case CHAR:
			return value_.c;
		default:
			MUTILS_ASSERT(false);
		}
		return ' ';
	}

	std::string Variant::toStdString()
	{
		switch (t_)
		{
		case STRING:
			return value_.s;
		default:
			MUTILS_ASSERT(false);
		}
		return "";
	}

	Vec2 Variant::toVec2()
	{
		switch (t_)
		{
		case VEC2:
			return value_.v;
		default:
			MUTILS_ASSERT(false);
		}
		return Vec2();
	}

	void * Variant::toUndef()
	{
		switch (t_)
		{
		case UNDEFINED:
			return value_.undef;
		default:
			MUTILS_ASSERT(false);
		}
		return nullptr;
	}

	// variantValue
	Variant::variantValue::variantValue(void *)
		: undef(nullptr)
	{
	}

	Variant::variantValue::variantValue(bool val)
		: b(val)
	{
	}

	Variant::variantValue::variantValue(int val)
		: i(val)
	{
	}

	Variant::variantValue::variantValue(unsigned int val)
		: ui(val)
	{
	}

	Variant::variantValue::variantValue(float val)
		: f(val)
	{
	}

	Variant::variantValue::variantValue(double val)
		: d(val)
	{
	}

	Variant::variantValue::variantValue(long val)
		: l(val)
	{
	}

	Variant::variantValue::variantValue(char val)
		: c(val)
	{
	}

	Variant::variantValue::variantValue(std::string val)
		: s(val)
	{
	}

	Variant::variantValue::variantValue(Vec2 val)
		: v(val)
	{
	}

	Variant::variantValue::~variantValue()
	{
	}

}
