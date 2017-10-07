#pragma once

namespace mutils
{
	class Observed;
	class Observer
	{
	public:
		virtual void onNotify(Observed* obs) = 0;
	};
}