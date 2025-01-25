
#include "Game.h"
#include <iostream>
#include <memory>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
	srand(time(NULL));

    //Text object contacts all block text el
    audio = std::make_unique<Audio>();
    text = std::make_unique<Text>(window);

    //GAME PLAY SPECIFICS
    mouse_position = std::make_shared<sf::Vector2f>();
    click = std::make_shared<sf::Vector2f>();
    left_click = std::make_shared<sf::Vector2f>();
}

Game::~Game()
{
}

bool Game::init()
{
    const int level[] =
    {
    17,17,17,17,17,17,17,17,
    17,17,17,17,17,17,17,17,
    17,17,17,17,17,17,17,17,
    17,17,17,17,17,17,17,17,
    10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,
    15,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,16,
    15,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,16,
    13,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,14,
    15,10,10,10,10,10,10,14,
    13,10,10,10,10,10,10,16,
    15,10,10,10,10,10,10,14,
    11,10,10,10,10,10,10,16,
    8,10,10,10,10,10,10,9,
    0,1,2,3,4,5,6,7,
    };

    // create the tilemap from the level definition
    
    if (!map.load("../Data/Images/trench_tiles.png", sf::Vector2u(32, 32), sf::Vector2u(32, 32), level, 8, 50))
    {
        return -1;
    }



    //CREATE VIEWS

    view1.reset(sf::FloatRect(0.f, 1340.f, 256.f, 256.f));

    //view2.setCenter(sf::Vector2f(100.f, 100.f));
    //view2.setSize(sf::Vector2f(400.f, 400.f));

    //view1.setCenter(*player.getPosition());
    //view1.setCenter(sf::Vector2f(200.f, 200.f));
    //view1.setSize(sf::Vector2f(200.f, 200.f));
    //view1.setRotation(20.f);

    window.setView(view1);

    //CREATE PLAYER

    player.initSprite("../Data/Images/player.png");
    player.getSprite()->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y-200));


    //CREATE OXYGEN
    oxygen.setSize(sf::Vector2f(oxygen_bar, 50));
    oxygen.setPosition(window.getSize().x / 2 - oxygen.getGlobalBounds().width / 2, window.getSize().y - 75);
    oxygen.setFillColor(sf::Color::Blue);

    return true;
}


void Game::update(float dt)
{
    //MOUSE UPDATES
    *mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    mouse_pointer = sf::FloatRect(mouse_position->x, mouse_position->y, 1.0, 1.0);

    switch (game_state)
    {
    case MENU:
        std::cout << "This is UPDATE MENU GAMESTATE" << std::endl;

        break;
    case INTRO:
        std::cout << "This is INTRO UPDATE GAMESTATE" << std::endl;
        break;
    case PLAYING:
        //std::cout << "This is UPDATE PLAYING GAMESTATE" << std::endl;

        //MOVE THE PLAYER

        //START MOVEMENT
        if (player_bubbles > 3) {
            if (player.getSprite()->getPosition().y > window.getSize().y / 2 - (player.getSprite()->getGlobalBounds().height / 2)) {
                player.getSprite()->move(0, -1 * player.speed * dt);
            }
        }

        player.getSprite()->move(player.direction * player.speed * dt, 0);
        if (player.getSprite()->getPosition().x < 0) {
            player.getSprite()->move(1 * player.speed * dt, 0);
        }
        else if (player.getSprite()->getPosition().x > (window.getSize().x - player.getSprite()->getGlobalBounds().width)) {
            player.getSprite()->move(-1 * player.speed * dt, 0);
        }

        // RESET VIEW - MAKE THIS X NUMBER OF TIMES TO REACH SURFACE?
        if (view1.getCenter().y < 800 && distance_travelled < 10000) {
            view1.reset(sf::FloatRect(0.f, 1000.f, 256.f, 256.f));
        }
        else if (view1.getCenter().y < 140) {
            view1.move(0.f, 0);
            //SURVIVED WIN
        }
        else {
            if (get_bends && bends_timer > 30) {
                view1.move(0.f, 0);
                std::cout << "YOU DIED";
            }
            else if (player_bubbles > 3) {
                view1.move(0.f, -1 * bubble_speed_multiplier * dt);
                distance_travelled += (bubble_speed_multiplier * dt);
                std::cout << distance_travelled << std::endl;
            }
        }

        //DO SOMETHING WITH PLAYER SPEED
        bubble_speed_multiplier = player_bubbles * 10;

        //BENDS TIMER
  
        if (bubble_speed_multiplier > 200) {
            get_bends = true;
            bends_timer++;
        }
        else {
            get_bends = false;
            bends_timer = 0;
        }



        //UPDATE OXYGEN
        if (oxygen_timer.getElapsedTime().asSeconds() > 0.1)
        {
            oxygen_bar --;
            oxygen.setSize(sf::Vector2f(oxygen_bar, 50));
            oxygen_timer.restart();
        }
        if (oxygen_bar < 500) {
            oxygen.setFillColor(sf::Color::Yellow);
        }
        else if (oxygen_bar < 100) {
            oxygen.setFillColor(sf::Color::Red);
        }

        //BUBBLES
        for (auto& this_bubble : vec_bubbles) {

            this_bubble->getSprite()->move(0, -1 * bubble.speed * dt);

            if (player.getSprite()->getGlobalBounds().intersects(this_bubble->getSprite()->getGlobalBounds())) {
                std::cout << "bubble";
                std::cout << player_bubbles << std::endl;
                player_bubbles = player_bubbles + 1;
                std::cout << player_bubbles << std::endl;
                this_bubble->popped = true;
            }
        }

        //REMOVE COLLECTED BUBBLES
        if (!vec_bubbles.empty()) {
            for (int i = vec_bubbles.size() - 1; i >= 0; i--) {
                if (vec_bubbles.at(i)->popped == true) {
                    vec_bubbles.erase(vec_bubbles.begin() + i);
                }
            }
        }

        break;
    case GAME_WON:
        std::cout << "This is UPDATE GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is UPDATE GAME_LOST GAMESTATE" << std::endl;
        break;
    }
}

void Game::render()
{
    switch (game_state)
    {

    case MENU:
        std::cout << "This is RENDER MENU GAMESTATE" << std::endl;
        break;
    case INTRO:
        std::cout << "This is RENDER PLAYING GAMESTATE" << std::endl;
        break;
    case PLAYING:
        //std::cout << "This is RENDER PLAYING GAMESTATE" << std::endl;

        window.setView(view1);
        window.draw(map);
        window.setView(window.getDefaultView());
        window.draw(*player.getSprite());
        window.draw(oxygen);

        for (auto& this_bubble : vec_bubbles) {
            window.draw(*this_bubble->getSprite());
        }

        break;
    case GAME_WON:
        std::cout << "This is RENDER GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is RENDER GAME_LOST GAMESTATE" << std::endl;
        break;
    }
}

void Game::mouseClicked(sf::Event event)
{
    *click = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    switch (game_state)
    {
    case MENU:
        std::cout << "This is MOUSECLICKED MENU GAMESTATE" << std::endl;
        break;
    case INTRO:
        std::cout << "This is MOUSECLICKED INTRO GAMESTATE" << std::endl;
        break;
    case PLAYING:
        std::cout << "This is MOUSECLICKED PLAYING GAMESTATE" << std::endl;
        break;
    case GAME_WON:
        std::cout << "This is MOUSECLICKED GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is MOUSECLICKED GAME_LOST GAMESTATE" << std::endl;
        break;
    }
}

void Game::mouseReleased(sf::Event event)
{
    sf::Vector2f unclick = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    switch (game_state)
    {
    case MENU:
        std::cout << "This is MOUSERELEASED MENU GAMESTATE" << std::endl;
        break;
    case INTRO:
        std::cout << "This is MOUSERELEASED INTRO GAMESTATE" << std::endl;
        break;
    case PLAYING:
        std::cout << "This is MOUSERELEASED PLAYING GAMESTATE" << std::endl;
        break;
    case GAME_WON:
        std::cout << "This is MOUSECLICKED GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is MOUSECLICKED GAME_LOST GAMESTATE" << std::endl;
        break;
    }
}

void Game::keyPressed(sf::Event event)
{
    switch (game_state)
    {
    case MENU:
        std::cout << "This is KEYPRESSED MENU GAMESTATE" << std::endl;
        break;
    case INTRO:
        std::cout << "This is KEYPRESSED INTRO GAMESTATE" << std::endl;
        break;
    case PLAYING:
        std::cout << "This is KEYPRESSED PLAYING GAMESTATE" << std::endl;
        if (event.key.code == sf::Keyboard::Z)
        {
            player.direction = -1;
        }
        if (event.key.code == sf::Keyboard::X)
        {
            player.direction = 1;
        }
        if (event.key.code == sf::Keyboard::B)
        {
            vec_bubbles.push_back(std::make_shared <GameObject> ());
            vec_bubbles[vec_bubbles.size() - 1]->initSprite("../Data/Images/bubble.png");
            vec_bubbles[vec_bubbles.size() - 1]->getSprite()->setPosition(sf::Vector2f(200, window.getSize().y - 100));
            vec_bubbles[vec_bubbles.size() - 1]->speed = 200;
        }

        break;
    case GAME_WON:
        std::cout << "This is KEYPRESSED GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is KEYPRESSED GAME_LOST GAMESTATE" << std::endl;
        break;
    }
}

void Game::keyReleased(sf::Event event)
{
    switch (game_state)
    {
    case MENU:
        std::cout << "This is KEYRELEASED MENU GAMESTATE" << std::endl;
        break;
    case INTRO:
        std::cout << "This is KEYRELEASED INTRO GAMESTATE" << std::endl;
        break;
    case PLAYING:
        std::cout << "This is KEYRELEASED PLAYING GAMESTATE" << std::endl;
        if (event.key.code == sf::Keyboard::Z)
        {
            player.direction = 0;
        }
        if (event.key.code == sf::Keyboard::X)
        {
            player.direction = 0;
        }
        break;
    case GAME_WON:
        std::cout << "This is KEYRELEASED GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is KEYRELEASED GAME_LOST GAMESTATE" << std::endl;
        break;
    }
}

void Game::mouseEntered(sf::Event event)
{
    switch (game_state)
    {
    case MENU:
        std::cout << "This is MOUSEENTERED MENU GAMESTATE" << std::endl;
        break;
    case INTRO:
        std::cout << "This is MOUSENTERED INTRO GAMESTATE" << std::endl;
        break;
    case PLAYING:
        std::cout << "This is MOUSEENTERED PLAYING GAMESTATE" << std::endl;
        break;
    case GAME_WON:
        std::cout << "This is MOUSEENTERED GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is MOUSEENTERED GAME_LOST GAMESTATE" << std::endl;
        break;
    }
}


