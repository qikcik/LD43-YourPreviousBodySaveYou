#pragma once 

#include <Box2D/Box2D.h>

#include "../../levelLoader/levelLoader.hpp"
#include "player.hpp"


class ObjectCreator : public HandleCreator
{
    public:
        ObjectCreator(b2World &world, Player& player);
        virtual ~ObjectCreator();

        void setGravity(b2Vec2 g);
        void create(std::string type, b2Vec2 pos, b2Vec2* tab, int ammount, std::map<std::string,std::string>& map); 
    protected:
        b2World& m_world;
        Player& m_player;
};