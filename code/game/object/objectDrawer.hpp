# pragma once
#include "../../physic/physicController.hpp"
#include "objectData.hpp"

class ObjectDrawer : public DrawerHandler
{
    public:
        virtual ~ObjectDrawer() {}

        void draw(sf::RenderWindow &win,sf::ConvexShape &shape, ObjectData* Data ) 
        {
            if(Data->getType() == ObjectData::Type::Player)
            {
                shape.setFillColor(sf::Color(52,152,219));
            }
            if(Data->getType() == ObjectData::Type::Corpse)
            {
                shape.setFillColor(sf::Color(220, 220, 220));
            }
            if(Data->getType() == ObjectData::Type::Normal)
            {
                
            }
            if(Data->getType() == ObjectData::Type::Kill)
            {
                shape.setFillColor(sf::Color::Red);
            }
            if(Data->getType() == ObjectData::Type::Win)
            {
                shape.setFillColor(sf::Color::Green);
            }
            if(Data->getType() == ObjectData::Type::Jumper)
            {
                shape.setFillColor(sf::Color(115, 73, 172));
            }

            if(Data->getType() == ObjectData::Type::Shooter)
            {
                shape.setFillColor(sf::Color::Red);
            }


            win.draw(shape);
        }
};