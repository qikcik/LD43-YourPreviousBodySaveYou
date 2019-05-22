#pragma once

#include <Box2D/Box2D.h>
#include <iostream>

class ShooterObj
{
    public:
        ShooterObj(b2Vec2 pos, b2Vec2 move) : m_pos(pos) , m_move(move) {};

        void update(b2Body *b)
        {
            b->SetLinearVelocity( m_move );
            if(m_body)
            {
                b->SetTransform( m_pos, b->GetAngle() );
                m_body = nullptr;
            }
        }

        void reset(b2Body *b)
        {
            m_body = b;
        }

    protected:
        b2Body* m_body;
        b2Vec2 m_pos;
        b2Vec2 m_move;
};

class ObjectData
{
    public:
        enum Type
        {
            Normal,
            Wall,
            Jumper,
            Kill,
            Win,
            Player,
            Corpse,
            Shooter,
        };

    public:
        ObjectData(Type t , void* p = nullptr ) : m_type(t) , extra(p)
        {

        }

        ~ObjectData()
        {
            ShooterObj* obj = (ShooterObj*)extra;
            delete obj;
        }

    public:
        void* extra;

        Type getType()
        {
            return m_type;
        }

        Type setType(Type type)
        {
            m_type = type;
        }

    protected:
        Type m_type;

};
