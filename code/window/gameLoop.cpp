#include "gameLoop.hpp"
#include <iostream>
#include "../physic/math.hpp"

GameLoop::GameLoop(sf::RenderWindow &window) 
    : m_window(window)
    , BackgrundColor(sf::Color(33,33,33))
{
    
}

GameLoop::~GameLoop() 
{
    if(m_state) delete m_state;
}

void GameLoop::run(State* state)
{
    m_state = state;
    State* temp_state;

    sf::Clock clock;

    //sf::View v = m_window.getDefaultView();
    //v.setCenter(sf::Vector2f( 0 , 0 ));
    //m_window.setView( v );

    while( m_window.isOpen() )
    {
        float delta = clock.getElapsedTime().asSeconds();
        clock.restart();
        //std::cout  << "[FPS]: " << 1.f / delta  << std::endl;

        sf::Event event;
        while(m_window.pollEvent(event))
        {
            if(m_state) m_state->onEvent(event,m_window);
        }

        if(m_state)
        { 
            temp_state = m_state->onUpdate(delta);
            if(temp_state)
            {
                delete m_state;
                m_state = temp_state;
            }
        }


        m_window.clear(BackgrundColor);
            if(m_state) m_state->onDraw(m_window);
        m_window.display();
    }
}