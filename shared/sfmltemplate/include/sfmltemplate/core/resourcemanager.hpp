#pragma once

#include <sfmltemplate/core/resourceholder.hpp>

#include <SFML/Graphics/Font.hpp>
#include <vector>

namespace sfmltemplate
{
	class PathManager;
	class ResourceManager
	{
	public:
		typedef unsigned int index;
		ResourceManager(PathManager* paths);
		~ResourceManager();

		virtual bool clear() = 0;
		virtual bool init() = 0;

		PathManager* getPathManager() const;

		sf::Font& getFont(index id);
		sf::Texture& getTexture(index id);
		// TODO : add the rest

	protected:
		PathManager& paths_;
		ResourceHolder<sf::Texture, index> textureHolder_;
		ResourceHolder<sf::Font, index> fontHolder_;
	};
}