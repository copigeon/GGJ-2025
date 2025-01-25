
#include "Text.h"

Text::Text(sf::RenderWindow& window) {

        //LOAD THE TITLE FONT HERE
        if (!title_font.loadFromFile("../Data/Fonts/JustInTheFirestormRegular.ttf")) { std::cout << "title_font did not load1 \n"; }

        // MENU
        title.setString("");
        title.setFont(title_font);
        title.setLetterSpacing(2);
        title.setCharacterSize(35);
        title.setOutlineThickness(1);
        title.setOutlineColor(sf::Color::Red);
        title.setFillColor((sf::Color::Yellow));
        title.setPosition((((float)window.getSize().x - title.getGlobalBounds().width) / 2), 100);
}

Text::~Text()
{
}

;