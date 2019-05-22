#include "gameState.hpp"
#include <iostream>

#include "../assets/Assets.hpp"


GameState::GameState(int i)
    : m_physic(b2Vec2(0,0),m_drawer)
    , m_player(m_physic.getWorld())
    , m_creator(m_physic.getWorld(),m_player)
    , m_loader(m_creator)
    , m_checker(m_player)
    , m_ID(i)
{
    m_physic.getWorld().SetContactListener(&m_checker);

    std::cout << "[ID] " << m_ID << std::endl;

    if(m_ID == 0)
    {
        m_info.set("","Your Previous Body Save You","press enter to start","","by Qikcik(Querk)");
    }
    else
    {
        auto info = m_loader.load("assets/map/"+std::to_string(i)+".json");
        if(info.isLoad == false) 
        {
            m_ID = -1;
            m_info.set("The End","thanks for play :)","created for ludum dare 43","using C++, SFML, Box2D, SimpleJSON, TILED","by Qikcik(Querk)");
        }
        else
        {
            m_info.set("LEVEL "+std::to_string(i),"\""+info.name+"\"",info.desc1,info.desc2,"press: Enter - to continue, R - to restart level");
        }
    }
}

GameState::~GameState()
{
    std::cout << "[STATE] destroy => GameState\n";
}

void GameState::onEvent(sf::Event &event, sf::RenderWindow &win)
{
    if(event.type == sf::Event::Closed)
        win.close();

    if(m_gamePlay)
    {
        if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space )
            m_player.jump();
        if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R )
            m_toRestart = true;
            
    }
    else 
    {
        if(m_ID != -1)
        {
            if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return )
            {
                Assets::sound.setBuffer(Assets::select);
                Assets::sound.play();
                m_gamePlay = true;
            }
        }
        if(m_ID == 0)
        {
            if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return )
            {
                Assets::sound.setBuffer(Assets::select);
                Assets::sound.play();
                m_player.win = true;
            }
        }
    }

    
}


State* GameState::onUpdate(float DeltaTime)
{
    if(m_gamePlay)
    {
        m_physic.onUpdate(DeltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            m_player.move(Player::MoveDirection::Left);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            m_player.move(Player::MoveDirection::Right);
        else 
            m_player.move(Player::MoveDirection::None);

        m_player.onUpdate();
    }

    if( m_player.win)
        return new GameState(m_ID+1);
    if( m_toRestart)
        return new GameState(m_ID);

    return nullptr;
}

void GameState::onDraw(sf::RenderWindow &win)
{
    if(m_gamePlay)
    {
        m_physic.onDraw(win);
    }
    else
    {
        m_info.onDraw(win);
    }
}