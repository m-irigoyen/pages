#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/String.hpp>

#include <mutils/variant.hpp>
#include <unordered_map>

namespace mutils
{
	class SettingsManager
	{
	public :
		SettingsManager();

		//! Sets the given key to given value. If no entry with that key exist, it is created
		// Returns false if it couldn't set the value, true otherwise.
		bool setValue(std::string key, const Variant& value);

		//! Gets value for given key. If the key exists, value is set to its value, and returns true.
		//! Returns false otherwise
		bool getValue(std::string key, Variant& value);

		// TODO : serialize / unserialize from file

	private:
		std::unordered_map<std::string, Variant> map_;
	};
}