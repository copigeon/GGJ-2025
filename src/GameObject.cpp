
#include "GameObject.h"

GameObject::GameObject()
{
	texture = std::make_shared<sf::Texture>();
	sprite = std::make_shared<sf::Sprite>();
	position = std::make_unique<sf::Vector2f>();
	sprite_rect_pos_x[0] = 0;
	sprite_rect_pos_x[1] = 0;
	sprite_rect_pos_x[2] = 0;
	sprite_rect_pos_x[3] = 0;
	sprite_rect_pos_y[0] = 0;
	sprite_rect_pos_y[1] = 0;
}

GameObject::~GameObject()
{
}

std::shared_ptr<sf::Sprite>& GameObject::getSprite()
{
	return sprite;
}

std::unique_ptr<sf::Vector2f>& GameObject::getPosition()
{
	return position;
}
void GameObject::setPosition(sf::Vector2f vector)
{
	*position = vector;
}

bool GameObject::initSprite(std::string file_name)
{
	if (!this->texture->loadFromFile(file_name)) {
		std::cout << "Object texture did not load\n";
	}
	this->texture->setRepeated(true);
	sprite->setTexture(*texture);
	return true;
}

std::string GameObject::getName()
{
	return name;
}
void GameObject::setName(std::string string)
{
	name = string;
}
