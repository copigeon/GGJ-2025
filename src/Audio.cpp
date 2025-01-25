
#include "Audio.h"

Audio::Audio()
{
    //COM BADGE
    if (!com_badge_buffer.loadFromFile("../Data/AUDIO/TOOLS/com_badge.wav")) {
        std::cout << "Sound com_badge file not found" << std::endl;
    }
    com_badge_sound.setBuffer(com_badge_buffer);
    com_badge_sound.setVolume(8);
}

Audio::~Audio()
{

}
