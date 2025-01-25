#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>



class Audio {

public:
	Audio();
	~Audio();
	// COM BADGE
	sf::SoundBuffer com_badge_buffer;
	sf::Sound com_badge_sound;

private:

};