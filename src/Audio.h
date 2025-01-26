#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>



class Audio {

public:
	Audio();
	~Audio();
	// COM BADGE
	sf::SoundBuffer bubble_buffer;
	sf::Sound bubble_sound;

	sf::SoundBuffer release_buffer;
	sf::Sound release_sound;

private:

};