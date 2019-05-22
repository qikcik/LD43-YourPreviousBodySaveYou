#pragma once

#include <Box2D/Box2D.h>
#include "objectData.hpp"

#include "player.hpp"
//ObjectCollisionChecker.hpp
#include "../../assets/Assets.hpp"

class ObjectCollisionChecker : public b2ContactListener
{
    public:

        ObjectCollisionChecker( Player& player ) : m_player(player) {}
        protected: Player& m_player;

        void BeginContact( b2Contact * c )
        {
            b2Fixture * fixtureA = c->GetFixtureA();
            b2Fixture * fixtureB = c->GetFixtureB();

            ObjectData* ObjectA = (ObjectData*)(c->GetFixtureA()->GetBody()->GetUserData());
            ObjectData* ObjectB = (ObjectData*)(c->GetFixtureB()->GetBody()->GetUserData());


            b2Body* mainBody;
            b2Body* secondBody;

            ObjectData* main;
            ObjectData* second;

            if(ObjectA != nullptr && ObjectB != nullptr)
            {
                bool isPlayer = false;
                if(ObjectA->getType() == ObjectData::Type::Player)
                {
                    second = ObjectB;
                    main = ObjectA;
                    isPlayer = true;
                }
                if(ObjectB->getType() == ObjectData::Type::Player)
                {
                    second = ObjectA;
                    main = ObjectB;
                    isPlayer = true;
                }
                if(isPlayer)
                {
                    if(second->getType() == ObjectData::Type::Normal) 
                        m_player.setCanJump(true);
                    if(second->getType() == ObjectData::Type::Corpse) 
                        m_player.setCanJump(true);
                    if(second->getType() == ObjectData::Type::Jumper)
                    { 
                        Assets::sound.setBuffer(Assets::longJump);
                        Assets::sound.play();
                        m_player.setCanJump(true);
                    }
                    if(second->getType() == ObjectData::Type::Kill)
                        m_player.setKill(true);
                    if(second->getType() == ObjectData::Type::Win)
                    {
                        Assets::sound.setBuffer(Assets::win);
                        Assets::sound.play();
                        m_player.win = true;
                    }

                    if(second->getType() == ObjectData::Type::Shooter)
                        m_player.setKill(true);

                }


                bool isShooter = false;
                if(ObjectA->getType() == ObjectData::Type::Shooter)
                {
                    second = ObjectB;
                    main = ObjectA;
                    mainBody = fixtureA->GetBody();
                    secondBody = fixtureB->GetBody();
                    isShooter = true;
                }
                if(ObjectB->getType() == ObjectData::Type::Shooter)
                {
                    second = ObjectA;
                    main = ObjectB;
                    mainBody = fixtureB->GetBody();
                    secondBody = fixtureA->GetBody();
                    isShooter = true;
                }
                if(isShooter)
                {
                    if(second->getType() == ObjectData::Type::Shooter  )
                    {
                        ((ShooterObj*)((ObjectData*)mainBody->GetUserData())->extra)->reset(mainBody);
                        ((ShooterObj*)((ObjectData*)secondBody->GetUserData())->extra)->reset(secondBody);
                    }
                    else if(second->getType() != ObjectData::Type::Player && second->getType() != ObjectData::Type::Corpse  ) 
                        ((ShooterObj*)((ObjectData*)mainBody->GetUserData())->extra)->reset(mainBody);

                }

            }
        }

        void EndContact( b2Contact * c )
        {
            
        }
};