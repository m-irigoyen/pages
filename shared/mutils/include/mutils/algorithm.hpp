#pragma once

#include <limits>
#include <algorithm>

namespace mutils
{
	template <typename T>
	T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	bool almostEqual(const float& a, const float& b
		, const float& epsilon = std::numeric_limits<float>::epsilon());

	template <typename T> inline constexpr
		int sign(T x, std::false_type is_signed) {
		return T(0) < x;
	}

	template <typename T> inline constexpr
		int sign(T x, std::true_type is_signed) {
		return (T(0) < x) - (x < T(0));
	}

	template <typename T> inline constexpr
		int sign(T x) {
		return sign(x, std::is_signed<T>());
	}
}