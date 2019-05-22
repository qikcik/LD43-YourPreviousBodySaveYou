#pragma once 

#include "../window/state.hpp"
#include "../physic/physicController.hpp"
#include "object/player.hpp"
#include "../levelLoader/levelLoader.hpp"
#include "object/objectCreator.hpp"
#include "object/objectDrawer.hpp"
#include "object/objectCollisionChecker.hpp"

#include "levelInfo.hpp"

class GameState : public State
{
    public:
         GameState(int i);
         ~GameState();

    protected:
        ObjectDrawer m_drawer;
        PhysicController m_physic; 
        Player m_player;
        ObjectCreator m_creator;
        LevelLoader m_loader;
        ObjectCollisionChecker m_checker;

        LevelInfo m_info;

    protected:
        bool m_gamePlay = false;
        bool m_toRestart = false;
        int m_ID;

    public:
        void onEvent(sf::Event &event, sf::RenderWindow &win);
        State* onUpdate(float DeltaTime);
        void onDraw(sf::RenderWindow &win);

};