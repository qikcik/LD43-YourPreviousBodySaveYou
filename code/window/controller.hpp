#pragma once

#include <SFML/Graphics.hpp>

class Controller
{
    public:
        virtual ~Controller() {};

    public:
        virtual void onUpdate(float DeltaTime) =0;
        virtual void onDraw(sf::RenderWindow &win) =0;

};