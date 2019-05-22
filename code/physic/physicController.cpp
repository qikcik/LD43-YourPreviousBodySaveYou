#include "physicController.hpp"
#include "math.hpp"
#include <iostream>


PhysicController::PhysicController(b2Vec2 Gravity,DrawerHandler& drawer)
    : m_world( b2Vec2( Gravity ) )
    , m_drawer( drawer) 
{

}

PhysicController::~PhysicController()
{
    for ( b2Body* body = m_world.GetBodyList(); body ; body = body->GetNext())
    {
        delete (ObjectData*)body->GetUserData();
    }
}

void PhysicController::onUpdate(float DeltaTime) 
{
    m_world.Step( DeltaTime, 8, 3);
}

void PhysicController::onDraw(sf::RenderWindow &win) 
{
    Math::Scale = (win.getSize().y / 20.f);
    sf::View view( sf::FloatRect(0.f, 0.f, win.getSize().x , win.getSize().y));
    view.setCenter(0,0);
    win.setView(view);

    for ( b2Body* body = m_world.GetBodyList(); body ; body = body->GetNext())
    {
        if( ((ObjectData*)body->GetUserData())->getType() == ObjectData::Type::Shooter )
        {
            ((ShooterObj*)((ObjectData*)body->GetUserData())->extra)->update(body);
        }

        for ( b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            b2Shape* shape = fixture->GetShape();
            if(shape->GetType() == b2Shape::e_polygon)
            {
                b2PolygonShape* polygonShape = (b2PolygonShape*)fixture->GetShape();

                sf::ConvexShape todraw;
                todraw.setPointCount(polygonShape->GetVertexCount());

                for( int i = 0; i != polygonShape->GetVertexCount() ; i++)
                {
                    todraw.setPoint(i, Math::ToPixel(polygonShape->GetVertex(i)) );
                }

                todraw.rotate( Math::ToDeg( body->GetAngle() ) );
                todraw.setPosition( Math::ToPixel( body->GetPosition() ) );

                m_drawer.draw(win,todraw, (ObjectData*)body->GetUserData() );
            }
        }
    }
}