#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace SimpleBody
{
    void generate(b2World &world, b2Vec2 pos, b2Vec2* tab, int ammount, void * data, float friction = 0.95f, float restitution =0.f, bool isDynamic = false )
    {
        b2BodyDef def;

        def.type = b2_staticBody;
        if(isDynamic)
        {
            def.type = b2_dynamicBody;
        }

        def.position.Set(pos.x, pos.y);
        b2Body * body = world.CreateBody(&def);

        b2PolygonShape boxShape;
        boxShape.Set(tab,ammount);

        b2FixtureDef boxFixDef;
        boxFixDef.shape = &boxShape;
        boxFixDef.density = 1.0f;
        boxFixDef.friction = friction;
        boxFixDef.restitution = restitution;

        body->CreateFixture(&boxFixDef);
        body->SetFixedRotation(true);
        body->SetUserData(data);

        if(isDynamic)
        {
            body->SetGravityScale( 0.f );
        }
    }
}