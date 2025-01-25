#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Text
{

public:
	Text(sf::RenderWindow& window);
	~Text();

	//FONTS
	sf::Font title_font;

	//MENU
	sf::Text title;

private:

};