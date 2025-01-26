#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

enum Status
{
	INITIAL,
};

class GameObject
{

public:
	GameObject();
	~GameObject();

	//GETTERS SETTERS

	std::shared_ptr<sf::Sprite>& getSprite();
	std::unique_ptr<sf::Vector2f>& getPosition();
	void setPosition(sf::Vector2f vector);
	void animatePlayer(sf::Clock& animation_clock);

	//FUNCTIONS

	bool initSprite(std::string file_name);

	sf::IntRect sprite_texture_rect;
	int sprite_rect_pos_x[4];
	int sprite_rect_pos_y[2];
	int frame = 0;
	int z_order = 0;
	int sprite_layer = 0;

	Status status = Status::INITIAL;

	//PLAYER
	int speed = 150;
	int direction = 0;

	//BUBBLE
	bool popped = false;

private:
	std::shared_ptr<sf::Sprite> sprite;
	std::unique_ptr<sf::Vector2f> position;
	std::shared_ptr<sf::Texture> texture;

};