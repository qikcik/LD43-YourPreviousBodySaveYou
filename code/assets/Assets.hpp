#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Assets
{
    public:
        static sf::Font font;
        static sf::SoundBuffer jump;
        static sf::SoundBuffer longJump;
        static sf::SoundBuffer kill;
        static sf::SoundBuffer win;
        static sf::SoundBuffer select;

        static sf::Sound sound;
    public:
        static void loadAll();

    private:
        Assets() = delete;
};