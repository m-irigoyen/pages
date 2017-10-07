#pragma once

namespace mutils
{
	//TODO dig out the resource manager prototype
	class AbstractResourceManager
	{
	public :
		static AbstractResourceManager& getInstance()
		{
			// Guaranteed to be destroye, instantiated on first use
			static AbstractResourceManager instance;
			return instance;
		}

		const std::string resourcesPath;
		const std::string RunesSubPath;
		const std::string RunesImagesPath;
		const std::string RunesFontPath;

	private:
		AbstractResourceManager() {}

		// C++ 11 method
	public:
		// Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
		AbstractResourceManager(const AbstractResourceManager&) = delete;
		void operator=(const AbstractResourceManager&) = delete;
	};
}

	