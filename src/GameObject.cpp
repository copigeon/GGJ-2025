
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


void GameObject::animatePlayer(sf::Clock& animation_clock)
{
	if (animation_clock.getElapsedTime().asSeconds() > 0.08)
	{
		sprite_texture_rect = sf::IntRect(
			sprite_rect_pos_x[frame], sprite_rect_pos_y[sprite_layer], 120, 150);
		getSprite()->setTextureRect(sprite_texture_rect);
		if (frame < 4)
		{
			frame++;
		}
		else
		{
			frame = 0;
		}
		animation_clock.restart();
	}
}