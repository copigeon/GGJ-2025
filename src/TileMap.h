#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{

public:
	TileMap();
	~TileMap();

	bool load(const std::string& tileset, sf::Vector2u textRectSize, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};