#pragma once

#include <string>

namespace sfmltemplate
{
	class PathManager
	{
	public:
		PathManager();
		~PathManager();

		virtual std::string getResourcesPath() const;

		virtual bool init();
	};
}