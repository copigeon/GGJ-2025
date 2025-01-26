
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

    player.initSprite("../Data/Images/diver.png");
    player.getSprite()->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y-200));
    player.sprite_texture_rect = sf::IntRect(player.sprite_rect_pos_x[0], player.sprite_rect_pos_y[0], 120, 150);
    player.sprite_rect_pos_x[0] = 0;
    player.sprite_rect_pos_x[1] = 120;
    player.sprite_rect_pos_x[2] = 240;
    player.sprite_rect_pos_x[3] = 360;
    player.sprite_rect_pos_y[0] = 0;
    player.sprite_rect_pos_y[1] = 150;
    player.getSprite()->setTextureRect(player.sprite_texture_rect);
    //player.getSprite()->setScale(1, 1);


    //CREATE OXYGEN
    oxygen_tank.setSize(sf::Vector2f(360, 70));
    oxygen_tank.setPosition(100, 30);
    if (!oxygen_tank_texture.loadFromFile("../Data/Images/oxygen.png")) {
        std::cout << "Object texture did not load\n";
    }
    oxygen_tank_texture.setRepeated(true);
    oxygen_tank.setTexture(&oxygen_tank_texture);


    oxygen.setSize(sf::Vector2f(oxygen_bar / 4, 70));
    oxygen.setPosition(oxygen_tank.getPosition().x + 70, 30);
    oxygen.setFillColor(sf::Color::Blue);

    //BENDS
    bends_indicator.setOutlineThickness(10);
    bends_indicator.setOutlineColor(sf::Color::Red);
    bends_indicator.setPosition(10, 10);
    bends_indicator.setSize(sf::Vector2f(window.getSize().x-20, window.getSize().y-20));
    bends_indicator.setFillColor(sf::Color::Transparent);

    death_indicator.setOutlineThickness(10);
    death_indicator.setOutlineColor(sf::Color::Red);
    death_indicator.setPosition(10, 10);
    death_indicator.setSize(sf::Vector2f(window.getSize().x - 20, window.getSize().y - 20));
    death_indicator.setFillColor(sf::Color(225,70,25,100));

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

        //START MOVEMEN


        if (player_bubbles > 3) {
            if (player.getSprite()->getPosition().y > window.getSize().y / 2 - (player.getSprite()->getGlobalBounds().height / 2)) {
                player.getSprite()->move(0, -1 * player.speed * dt);
            }
        }
        else {
            if (player.getSprite()->getPosition().y < window.getSize().y - 200) {
                player.getSprite()->move(0, 1 * player.speed * dt);
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
            win = true;
        }
        else {
            if (get_bends && bends_timer > 5) {
                view1.move(0.f, 0);
                std::cout << "YOU DIED";
                game_state = GameState::GAME_LOST;
            }
            else if (player_bubbles > 3) {
                view1.move(0.f, -1 * bubble_speed_multiplier * dt);
                distance_travelled += (bubble_speed_multiplier * dt);
                //std::cout << distance_travelled << std::endl;
                int distance_left = 10000 - distance_travelled;
                text->distance_travelled.setString(std::to_string(distance_left));
                text->distance_travelled.setPosition(window.getSize().x - 100 - text->distance_travelled.getGlobalBounds().width, 50);

            }
            else if (distance_travelled > 0) {
                view1.move(0.f, 1 * 50 * dt);
                distance_travelled -= (50 * dt);
                //std::cout << distance_travelled << std::endl;
                int distance_left = 10000 - distance_travelled;
                text->distance_travelled.setString(std::to_string(distance_left));
                text->distance_travelled.setPosition(window.getSize().x - 100 - text->distance_travelled.getGlobalBounds().width, 50);
            }
        }

        //DO SOMETHING WITH PLAYER SPEED
        bubble_speed_multiplier = player_bubbles * 10;

        //BENDS TIMER
  
        if (bubble_speed_multiplier > 200 && distance_travelled < 10000) {
            get_bends = true;
            if (bends_clock.getElapsedTime().asSeconds() > 1)
            {
                bends_timer++;
                int bends_count = 5 - bends_timer;
                text->bends_countdown.setString(std::to_string(bends_count));
                bends_clock.restart();
            }
            
        }
        else {
            get_bends = false;
            bends_timer = 0;
        }



        //UPDATE OXYGEN
        if (oxygen_timer.getElapsedTime().asSeconds() > 0.1 && distance_travelled < 10000)
        {
            oxygen_bar --;
            oxygen.setSize(sf::Vector2f(oxygen_bar / 4, 70));
            oxygen_timer.restart();
        }
        if (oxygen_bar < 500) {
            oxygen.setFillColor(sf::Color::Yellow);
        }
        else if (oxygen_bar < 100) {
            oxygen.setFillColor(sf::Color::Red);
        }

        if (oxygen_bar <= 0)
        {
            game_state = GameState::GAME_LOST;
        }

        //BUBBLES
        //float bubble_timer = random_number(1, 3);
        //bubble_timer = bubble_timer / 100;
        //spawn the bubbles
        if (bubble_spawn_timer.getElapsedTime().asSeconds() > 0.2)
        {
            bubble_spawn();
            bubble_spawn_timer.restart();
        }


        for (auto& this_bubble : vec_bubbles) {

            this_bubble->getSprite()->move(0, -1 * this_bubble->speed * dt);

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
        //BUBBLES
        if (bubble_spawn_timer.getElapsedTime().asSeconds() > 0.2)
        {
            bubble_spawn();
            bubble_spawn_timer.restart();
        }
        break;
    case GAME_LOST:
        std::cout << "This is UPDATE GAME_LOST GAMESTATE" << std::endl;
        //BUBBLES

        for (auto& this_bubble : vec_bubbles) {
            this_bubble->getSprite()->move(0, -1 * bubble.speed * dt);
        }

        if (bubble_spawn_timer.getElapsedTime().asSeconds() > 0.2)
        {
            bubble_spawn();
            bubble_spawn_timer.restart();
        }
        break;
    }
}

void Game::render()
{
    switch (game_state)
    {

    case MENU:
        //std::cout << "This is RENDER MENU GAMESTATE" << std::endl;
        window.setView(view1);
        window.draw(map);
        window.setView(window.getDefaultView());
        window.draw(*player.getSprite());
        window.draw(oxygen);
        window.draw(oxygen_tank);


        for (auto& this_bubble : vec_bubbles) {
            window.draw(*this_bubble->getSprite());
        }

        window.draw(text->start);
        window.draw(text->start_1);
        window.draw(text->start_1a);
        window.draw(text->start_1b);

        window.draw(text->start_2);



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
        window.draw(oxygen_tank);
        if (bends_timer > 0) {
            window.draw(text->bends_countdown_header);
            window.draw(text->bends_countdown);
            window.draw(bends_indicator);
        }

        for (auto& this_bubble : vec_bubbles) {
            window.draw(*this_bubble->getSprite());
        }

        if (distance_travelled < 10000) {
            window.draw(text->distance_travelled_header);
            window.draw(text->distance_travelled);
        }
        if (win)
        {
            window.draw(text->win);
        }

        break;
    case GAME_WON:
        std::cout << "This is RENDER GAME_WON GAMESTATE" << std::endl;
        break;
    case GAME_LOST:
        std::cout << "This is RENDER GAME_LOST GAMESTATE" << std::endl;
        window.setView(view1);
        window.draw(map);
        window.setView(window.getDefaultView());
        window.draw(*player.getSprite());
        window.draw(death_indicator);
        for (auto& this_bubble : vec_bubbles) {
            window.draw(*this_bubble->getSprite());
        }
        if (oxygen_bar <= 0)
        {
            window.draw(text->lose_drown);
        }
        if (bends_timer > 5)
        {
            window.draw(text->lose_bends);
        }

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
        //std::cout << "This is KEYPRESSED PLAYING GAMESTATE" << std::endl;
        if (event.key.code == sf::Keyboard::Z)
        {
            player.direction = -1;
            player.sprite_layer = 1;
            player.animatePlayer(animation_clock);

        }
        if (event.key.code == sf::Keyboard::X)
        {
            player.direction = 1;
            player.sprite_layer = 0;
            player.animatePlayer(animation_clock);

        }
        if (event.key.code == sf::Keyboard::B)
        {
            std::cout << "play audio";
            audio->bubble_sound.play();
        }
        if (event.key.code == sf::Keyboard::Space)
        {
            if (distance_travelled < 10000) {
                if (player_bubbles > 0) {
                    player_bubbles--;
                    std::cout << player_bubbles << std::endl;
                    float position_x = (float)player.getSprite()->getPosition().x + ((float)player.getSprite()->getGlobalBounds().width / 2);
                    float position_y = (float)player.getSprite()->getPosition().y - 50;
                    std::cout << position_y;
                    bubble_release(position_x - 15, position_y);
                    bubble_release(position_x + 15, position_y);
                    bubble_release(position_x, position_y);
                }
            }
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
        if (event.key.code == sf::Keyboard::Space)
        {
            game_state = GameState::PLAYING;
        }
        break;
    case INTRO:
        std::cout << "This is KEYRELEASED INTRO GAMESTATE" << std::endl;
        break;
    case PLAYING:
        //std::cout << "This is KEYRELEASED PLAYING GAMESTATE" << std::endl;
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

int Game::random_number(int min, int max)
{
    return rand() % max + min;
}

void Game::bubble_spawn()
{
    vec_bubbles.push_back(std::make_shared <GameObject>());
    vec_bubbles[vec_bubbles.size() - 1]->initSprite("../Data/Images/bubble.png");
    float position_x = random_number(50, window.getSize().x - 100);
    vec_bubbles[vec_bubbles.size() - 1]->getSprite()->setPosition(sf::Vector2f(position_x, window.getSize().y - 100));
    float scale = random_number(1, 50);
    scale = scale / 100;
    vec_bubbles[vec_bubbles.size() - 1]->getSprite()->setScale(scale, scale);
    float speed = random_number(200, 250);
    vec_bubbles[vec_bubbles.size() - 1]->speed = speed;
    float bubble_rand = random_number(10, 500);
    bubble_rand = bubble_rand / 100;
    if (bubble_audio_timer.getElapsedTime().asSeconds() > bubble_rand && audio->bubble_sound.getStatus() != sf::Sound::Status::Playing)
    {
        audio->bubble_sound.play();
        bubble_audio_timer.restart();
    }
}

void Game::bubble_release(float position_x, float position_y)
{
    std::cout << position_y;
    vec_bubbles.push_back(std::make_shared <GameObject>());
    vec_bubbles[vec_bubbles.size() - 1]->initSprite("../Data/Images/bubble.png");
    vec_bubbles[vec_bubbles.size() - 1]->getSprite()->setPosition(sf::Vector2f(position_x, position_y));
    float scale = random_number(1, 50);
    scale = scale / 100;
    vec_bubbles[vec_bubbles.size() - 1]->getSprite()->setScale(scale, scale);

    float speed = random_number(300, 450);
    vec_bubbles[vec_bubbles.size() - 1]->speed = speed;

        audio->release_sound.play();

}



