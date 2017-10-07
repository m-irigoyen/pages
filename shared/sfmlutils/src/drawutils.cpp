#include <sfmlutils/drawutils.hpp>

#include <mutils/assert.hpp>

#include <SFML/Graphics/VertexArray.hpp>

namespace sfmlutils
{
	void drawFullScreenQuad(sf::RenderWindow& window,
		const sf::Shader& shader)
	{
		sf::Vector2u size = window.getSize();
		sf::VertexArray arr(sf::TrianglesStrip, 4);
		arr.append(sf::Vertex(sf::Vector2f(0.f, 0.f)));
		arr.append(sf::Vertex(sf::Vector2f((float)size.x, 0.f)));
		arr.append(sf::Vertex(sf::Vector2f(0.f, (float)size.y)));
		arr.append(sf::Vertex(sf::Vector2f((float)size.x, (float)size.y)));
		window.draw(arr, &shader);
	}
}