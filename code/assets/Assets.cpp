#include "Assets.hpp"

sf::Font Assets::font;
sf::SoundBuffer Assets::jump;
sf::SoundBuffer Assets::longJump;
sf::SoundBuffer Assets::kill;
sf::SoundBuffer Assets::win;
sf::SoundBuffer Assets::select;


sf::Sound Assets::sound;

void Assets::loadAll()
{
    Assets::font.loadFromFile("assets/font/font.ttf");

    jump.loadFromFile("assets/sound/jump.wav");
    longJump.loadFromFile("assets/sound/jump2.wav");
    kill.loadFromFile("assets/sound/kill.wav");
    win.loadFromFile("assets/sound/win.wav");
    select.loadFromFile("assets/sound/select.wav");
}