#pragma once

#include <vector>

namespace mutils
{
	class Observer;
	class Observed
	{
	public:
		Observed();
		~Observed();

		virtual bool registerObserver(Observer* obs);
		virtual bool unregisterObserver(Observer* obs);
		virtual bool isRegistered(Observer* obs);
		virtual void notifyObservers();

		virtual void onObserverRegistered(Observer* obs) = 0;
		virtual void onObserverNotified(Observer* obs) = 0;
	private:
		std::vector<Observer*> observers_;
	};
}