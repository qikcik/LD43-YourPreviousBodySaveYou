#include "math.hpp"

float Math::Scale =  (720.f / 20.f);


float Math::ToDeg(float Rad)
{
    return (180* Rad / b2_pi );
}

float Math::ToRad(float Deg)
{
    return (b2_pi * Deg / 180.f); 
}

float Math::ToMeter(float Pixel)
{
    return Pixel * (1  / Scale );
}

float Math::ToPixel(float Meter)
{
    return Meter * Scale ;
}


sf::Vector2f Math::ToPixel(b2Vec2 vec)
{
    return sf::Vector2f( ToPixel(vec.x),ToPixel(float(vec.y)) );
}