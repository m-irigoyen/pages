#pragma once

#include <sfmltemplate/core/resourcemanager.hpp>

namespace pages
{
	class ResourceManager : public sfmltemplate::ResourceManager
	{
	public:
		enum Fonts
		{
			monofonto = 0,
		};
		enum Textures
		{
			paper = 0,
		};

		ResourceManager(sfmltemplate::PathManager* pathManager);

		// Hérité via ResourceManager
		virtual bool clear() override;
		virtual bool init() override;
	};
}