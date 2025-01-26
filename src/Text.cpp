
#include "Text.h"

Text::Text(sf::RenderWindow& window) {

        //LOAD THE TITLE FONT HERE
        if (!title_font.loadFromFile("../Data/Fonts/open-sans/OpenSans-Regular.ttf")) { std::cout << "title_font did not load1 \n"; }
        //LOAD THE TITLE FONT HERE
        if (!title_font_big.loadFromFile("../Data/Fonts/open-sans/OpenSans-ExtraBold.ttf")) { std::cout << "title_font did not load1 \n"; }

        // MENU

        start.setString("Get to the Surface!");
        start.setFont(title_font_big);
        start.setLetterSpacing(2);
        start.setCharacterSize(35);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        start.setFillColor((sf::Color::Magenta));
        start.setPosition(window.getSize().x / 2 - (start.getGlobalBounds().width / 2), 150);

        start_1a.setString("Collect the bubbles to float up!");
        start_1a.setFont(title_font_big);
        start_1a.setLetterSpacing(2);
        start_1a.setCharacterSize(20);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        start_1a.setFillColor((sf::Color::Magenta));
        start_1a.setPosition(window.getSize().x / 2 - (start_1a.getGlobalBounds().width / 2), 200);

        start_1b.setString("Release the bubbles to drift down!");
        start_1b.setFont(title_font_big);
        start_1b.setLetterSpacing(2);
        start_1b.setCharacterSize(20);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        start_1b.setFillColor((sf::Color::Magenta));
        start_1b.setPosition(window.getSize().x / 2 - (start_1b.getGlobalBounds().width / 2), 225);

        start_1.setString("w = left / x = right / space = release bubbles!");
        start_1.setFont(title_font_big);
        start_1.setLetterSpacing(2);
        start_1.setCharacterSize(25);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        start_1.setFillColor((sf::Color::Magenta));
        start_1.setPosition(window.getSize().x / 2 - (start_1.getGlobalBounds().width / 2), 250);

        start_2.setString("PRESS SPACE TO START");
        start_2.setFont(title_font_big);
        start_2.setLetterSpacing(2);
        start_2.setCharacterSize(35);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        start_2.setFillColor((sf::Color::Magenta));
        start_2.setPosition(window.getSize().x / 2 - (start_2.getGlobalBounds().width / 2), 300);


        title.setString("Get to ");
        title.setFont(title_font);
        title.setLetterSpacing(2);
        title.setCharacterSize(35);
        title.setOutlineThickness(1);
        title.setOutlineColor(sf::Color::Red);
        title.setFillColor((sf::Color::Yellow));
        title.setPosition((((float)window.getSize().x - title.getGlobalBounds().width) / 2), 100);


        // BENDS
        bends_countdown_header.setString("If you dont slow down you'll get the Bends!");
        bends_countdown_header.setFont(title_font);
        bends_countdown_header.setLetterSpacing(2);
        bends_countdown_header.setCharacterSize(25);
        bends_countdown_header.setOutlineThickness(0);
        //bends_countdown_header.setOutlineColor(sf::Color::Red);
        bends_countdown_header.setFillColor((sf::Color::Red));
        bends_countdown_header.setPosition(window.getSize().x/2 -bends_countdown_header.getGlobalBounds().width/2, window.getSize().y-200);

        bends_countdown.setString("0");
        bends_countdown.setFont(title_font_big);
        bends_countdown.setLetterSpacing(2);
        bends_countdown.setCharacterSize(35);
        bends_countdown.setOutlineThickness(0);
        //bends_countdown.setOutlineColor(sf::Color::Red);
        bends_countdown.setFillColor((sf::Color::Red));
        bends_countdown.setPosition(window.getSize().x / 2 - bends_countdown.getGlobalBounds().width / 2, window.getSize().y-150);

        // DISTANCE
        distance_travelled_header.setString("Distance to Surface:");
        distance_travelled_header.setFont(title_font);
        distance_travelled_header.setLetterSpacing(2);
        distance_travelled_header.setCharacterSize(20);
        distance_travelled_header.setOutlineThickness(0);
        //distance_travelled_header.setOutlineColor(sf::Color::Red);
        distance_travelled_header.setFillColor((sf::Color::Yellow));
        distance_travelled_header.setPosition(window.getSize().x - 100 - distance_travelled_header.getGlobalBounds().width, 30);

        distance_travelled.setString("10000");
        distance_travelled.setFont(title_font_big);
        distance_travelled.setLetterSpacing(2);
        distance_travelled.setCharacterSize(35);
        distance_travelled.setOutlineThickness(0);
        //bends_countdown.setOutlineColor(sf::Color::Red);
        distance_travelled.setFillColor((sf::Color::Yellow));
        distance_travelled.setPosition(window.getSize().x -100 - distance_travelled.getGlobalBounds().width, 50);

        win.setString("You Made it! Whoopee!");
        win.setFont(title_font);
        win.setLetterSpacing(2);
        win.setCharacterSize(40);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        win.setFillColor((sf::Color::Green));
        win.setPosition(window.getSize().x / 2 - (win.getGlobalBounds().width / 2), window.getSize().y / 2+150);

        lose_drown.setString("Oh dear! You drowned!");
        lose_drown.setFont(title_font);
        lose_drown.setLetterSpacing(2);
        lose_drown.setCharacterSize(40);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        lose_drown.setFillColor((sf::Color::White));
        lose_drown.setPosition(window.getSize().x / 2 - (lose_drown.getGlobalBounds().width / 2), 150);

        lose_bends.setString("Oh dear! The Bends got you!");
        lose_bends.setFont(title_font);
        lose_bends.setLetterSpacing(2);
        lose_bends.setCharacterSize(40);
        //title.setOutlineThickness(1);
        //title.setOutlineColor(sf::Color::Green);
        lose_bends.setFillColor((sf::Color::White));
        lose_bends.setPosition(window.getSize().x / 2 - (lose_bends.getGlobalBounds().width / 2), 150);

}

Text::~Text()
{
}

;