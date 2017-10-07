#include <mutils/observed.hpp>

#include <mutils/observer.hpp>
#include <mutils/assert.hpp>
#include <mutils/algorithm.hpp>

namespace mutils
{
	using obsVec = std::vector<Observer*>;

	Observed::Observed()
	{
	}

	Observed::~Observed()
	{
	}

	std::vector<Observer*>::iterator find(std::vector<Observer*>& vec,
		Observer * obs)
	{
		return std::find(vec.begin(), vec.end(), obs);
	}

	bool Observed::registerObserver(Observer * obs)
	{
		MUTILS_ASSERT(obs);
		obsVec::iterator it = find(observers_, obs);
		if (it == observers_.end())
		{
			observers_.push_back(obs);
			onObserverRegistered(obs);
			return true;
		}
		return false;
	}

	bool Observed::unregisterObserver(Observer * obs)
	{
		MUTILS_ASSERT(obs);
		obsVec::iterator it = find(observers_, obs);
		if (it != observers_.end())
		{
			observers_.erase(it);
			return true;
		}
		return false;
	}

	bool Observed::isRegistered(Observer * obs)
	{
		return find(observers_, obs) != observers_.end();
	}

	void Observed::notifyObservers()
	{
		for (Observer* o : observers_)
		{
			o->onNotify(this);
			onObserverNotified(o);
		}
	}


}

