#pragma once

namespace mutils
{
	class Color
	{
	public:
		Color(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		Color(int r, int g, int b, int a);

		void setFromFloat(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		void setFromInt(int r = 0, int g = 0, int b = 0, int a = 255);

		void getIntValues(int& r, int& g, int& b, int& a) const;

		float r;
		float g;
		float b;
		float a;
	};
}