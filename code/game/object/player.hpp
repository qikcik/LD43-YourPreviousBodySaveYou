#pragma once

#include <Box2D/Box2D.h>
#include "../../window/controller.hpp"

class Player
{
    public:
        Player(b2World &world);
        ~Player();

        void create(b2Vec2 pos, b2Vec2* tab, int ammount, std::map<std::string,std::string>& map);

    protected:
        float m_acceleration = 4.f;
        float m_jumpForce = 5.f;

    public:
        enum MoveDirection { Left , Right, None };
        void move(MoveDirection dir);
        void jump();

    protected: bool m_canJump;
    public: void setCanJump(bool x) { m_canJump = x; }

    protected: bool m_doKill;
    public: void setKill(bool x) {m_doKill = x; }

    protected:
        void createBody();
        void kill();

    public: 
        bool win = false;
        void onUpdate();


    protected:
        b2Vec2 m_respawnPoint;
        b2PolygonShape m_shape;

        b2World &m_world;
        b2Body *m_body = nullptr;


};