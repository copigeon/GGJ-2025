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
	sf::Font title_font_big;


	//MENU
	sf::Text title;

	sf::Text bends_countdown_header;
	sf::Text bends_countdown;
	sf::Text distance_travelled_header;
	sf::Text distance_travelled;

	sf::Text win;
	sf::Text lose_drown;
	sf::Text lose_bends;
	sf::Text start;
	sf::Text start_1;
	sf::Text start_1a;
	sf::Text start_1b;

	sf::Text start_2;



private:

};