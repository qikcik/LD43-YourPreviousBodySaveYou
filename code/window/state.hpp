#pragma once
#include <SFML/Graphics.hpp>

class State
{
    public:
        virtual ~State() {};

    public:
        virtual void onEvent(sf::Event &event,sf::RenderWindow &win) =0;
        virtual State* onUpdate(float DeltaTime) =0;
        virtual void onDraw(sf::RenderWindow &win) =0;
};