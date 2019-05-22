#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Math
{
    public:
        static float Scale; // default window Height 
    public:
        static float ToDeg(float Rad);
        static float ToRad(float Deg);
        static float ToMeter(float Pixel);

        static float ToPixel(float Meter);
        static sf::Vector2f ToPixel(b2Vec2 vec);
};
