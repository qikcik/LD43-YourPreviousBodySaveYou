#include "player.hpp"

#include "../../physic/math.hpp"
#include "objectData.hpp"
#include <iostream>


#include "../../assets/Assets.hpp"



Player::Player(b2World &world)
    : m_world(world)
{

}


Player::~Player()
{
    
}

void Player::create(b2Vec2 pos, b2Vec2* tab, int ammount, std::map<std::string,std::string>& map)
{
    m_respawnPoint = pos;
    m_shape.Set(tab,ammount);

    if(map.find("Acceleration") != map.end() )
        m_acceleration = std::stof( map["Acceleration"].c_str(), 0 );

    if(map.find("JumpForce") != map.end() )
        m_jumpForce = std::stof( map["JumpForce"].c_str(), 0 );

    std::cout << "[ARGUMENTS](PLAYER) Acceleration => (" << m_acceleration << ")\n";
    std::cout << "[ARGUMENTS](PLAYER) JumpForce => (" << m_jumpForce <<  ")\n";

    createBody();
}


void Player::createBody()
{
    std::cout << "[PLAYER] new body \n";
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(m_respawnPoint.x, m_respawnPoint.y);
    m_body = m_world.CreateBody(&bodyDef);

    /* body */

    b2FixtureDef boxFixDef;
    boxFixDef.shape = &m_shape;

    boxFixDef.density = 1.0f;
    boxFixDef.friction = 0.f;
    boxFixDef.restitution = 0.20f;
    m_body->CreateFixture(&boxFixDef);
    //m_body->SetFixedRotation(true);

    m_body->SetUserData( new ObjectData(ObjectData::Type::Player) );
}

void Player::kill()
{
    Assets::sound.setBuffer(Assets::kill);
    Assets::sound.play();
    std::cout << "[PLAYER] kill \n";
    ((ObjectData*)m_body->GetUserData())->setType(ObjectData::Type::Corpse);
    m_body->GetFixtureList()->SetFriction(1.f);
    m_body->GetFixtureList()->SetRestitution(0.001f);
    m_body->SetLinearVelocity( b2Vec2(m_body->GetLinearVelocity().x *0.2 , m_body->GetLinearVelocity().y  *0.2  ) );

    createBody();
    m_doKill = false;
}


void Player::onUpdate()
{
    if(m_body)
    {
        //std::cout << "[Player] positon => ("<< Math::ToPixel(m_body->GetPosition().x) << ","<< Math::ToPixel(m_body->GetPosition().y) << ") \n";

        if(m_doKill)
        {
            kill();
        }
    }
}

void Player::move(MoveDirection dir)
{
    if(m_body)
    {
        b2Vec2 oldVelocity = m_body->GetLinearVelocity();
        b2Vec2 newVelocity;

        if(dir == MoveDirection::Left)
            newVelocity = b2Vec2(  -m_acceleration, oldVelocity.y);
        else if (dir == MoveDirection::Right)
            newVelocity = b2Vec2(   m_acceleration, oldVelocity.y);
        else
            newVelocity = b2Vec2( oldVelocity.x / 2 , oldVelocity.y);


        m_body->SetLinearVelocity(newVelocity);
    }
}
void Player::jump()
{
    if(m_canJump && m_body)
    {
        const b2Vec2 oldVelocity = m_body->GetLinearVelocity();

        const b2Vec2 newVelocity = b2Vec2(  oldVelocity.x , oldVelocity.y - m_jumpForce);
        
        if(m_world.GetGravity().y > 0 )
            const b2Vec2 newVelocity = b2Vec2(  oldVelocity.x , oldVelocity.y + m_jumpForce);
        
        m_body->SetLinearVelocity(newVelocity);
        m_canJump = false;

        Assets::sound.setBuffer(Assets::jump);
        Assets::sound.play();
    }
}
