
#include "Audio.h"

Audio::Audio()
{
    //COM BADGE
    if (!bubble_buffer.loadFromFile("../Data/Audio/bubble.wav")) {
        std::cout << "Sound bubble file not found" << std::endl;
    }
    bubble_sound.setBuffer(bubble_buffer);
    bubble_sound.setVolume(10);

    if (!release_buffer.loadFromFile("../Data/Audio/release.wav")) {
        std::cout << "Sound bubble file not found" << std::endl;
    }
    release_sound.setBuffer(release_buffer);
    release_sound.setVolume(10);
}

Audio::~Audio()
{

}
