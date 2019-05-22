#pragma once

#include "../window/controller.hpp"
#include "Box2D/Box2D.h"
#include "../game/object/objectData.hpp"

class DrawerHandler
{
    public:
        virtual ~DrawerHandler() {}
        virtual void draw(sf::RenderWindow &win,sf::ConvexShape &shape, ObjectData* Data ) = 0;
};

class PhysicController : public Controller
{
    public:

        PhysicController(b2Vec2 Gravity,DrawerHandler& drawer);
        virtual ~PhysicController();

    public:
        void onUpdate(float DeltaTime);
        void onDraw(sf::RenderWindow &win);


    protected: b2World m_world;
    public:    b2World& getWorld() {return m_world; }

    protected:
        DrawerHandler& m_drawer;


    
};