#include "objectCreator.hpp"

#include <iostream>
#include "../../physic/simpleBody.hpp"
#include "objectData.hpp"

ObjectCreator::ObjectCreator(b2World &world, Player& player)
    :m_world(world)
    ,m_player(player)
{

}

ObjectCreator::~ObjectCreator()
{

}

void ObjectCreator::setGravity(b2Vec2 g)
{
    m_world.SetGravity(g);
}

void ObjectCreator::create(std::string type, b2Vec2 pos, b2Vec2* tab, int ammount, std::map<std::string,std::string>& map)
{
    std::cout << "[ADD]" << type << std::endl;
    if(type == "RESPAWN")
    {
        m_player.create(pos,tab,ammount, map);
    }
    else if(type == "NORMAL")
    {
        SimpleBody::generate(m_world,pos,tab,ammount, new ObjectData( ObjectData::Type::Normal ) );
    }
    else if(type == "WALL")
    {
        SimpleBody::generate(m_world,pos,tab,ammount, new ObjectData( ObjectData::Type::Wall ) );
    }
    else if(type == "KILL")
    {
        SimpleBody::generate(m_world,pos,tab,ammount, new ObjectData( ObjectData::Type::Kill ) );
    }
    else if(type == "WIN")
    {
        SimpleBody::generate(m_world,pos,tab,ammount, new ObjectData( ObjectData::Type::Win ) );
    }
    else if(type == "JUMPER")
    {
        SimpleBody::generate(m_world,pos,tab,ammount, new ObjectData( ObjectData::Type::Jumper) , 0.2f, 1.f);
    }
    else if(type == "SHOOTER")
    {
        b2Vec2 move( std::stof( map["SpeedX"].c_str(), 0 ) ,std::stof( map["SpeedY"].c_str(), 0 ) ); 
        std::cout << "[ARGUMENTS] SpeedX and SpeedY => (" << move.x << "," << move.y << ")\n";
        
        void* ptr = new ShooterObj(pos, move);
        SimpleBody::generate(m_world,pos,tab,ammount, new ObjectData( ObjectData::Type::Shooter, ptr ) , 1.f, 0.f, true);
    }
}