#pragma once
#include <SFML/Graphics.hpp>

class State;

class GameLoop
{
    public:
        GameLoop(sf::RenderWindow &window);
        ~GameLoop();

    public:
        sf::Color BackgrundColor;
        void run(State* state);
    
    protected:
        sf::RenderWindow &m_window;
        State * m_state;

    
};

#include "state.hpp"