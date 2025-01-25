#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
    std::cout << "You should see a window that opens as well as this writing to console..."
        << std::endl;

    // create window and set up
    sf::RenderWindow window(sf::VideoMode(1024, 768), "GGJ2025", sf::Style::Close);
    window.setFramerateLimit(60);

    //initialise an instance of the game class
    Game game(window);

    //run the init function of the game class and check it all initialises ok
    if (!game.init())
    {
        return 0;
    }

    // A Clock starts counting as soon as it's created
    sf::Clock clock;

    // Game loop: run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        //'process inputs' element of the game loop
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) 
            window.close();
            // key pressed event
            if (event.type == sf::Event::KeyPressed) { game.keyPressed(event); }
            // key released event
            if (event.type == sf::Event::KeyReleased) { game.keyReleased(event); }
            // mouse button pressed event
            if (event.type == sf::Event::MouseButtonPressed) { game.mouseClicked(event); }
            // mouse button pressed event
            if (event.type == sf::Event::MouseButtonReleased) { game.mouseReleased(event); }
            // mouse button pressed event
            if (event.type == sf::Event::MouseEntered) { game.mouseEntered(event); }
        }

        //'update' element of the game loop
        game.update(dt);       
        

        //'render' element of the game loop
        window.clear(sf::Color::Black);
        game.render();
        window.display();
    }

    return 0;
}
