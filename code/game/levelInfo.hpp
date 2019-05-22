#pragma once

#include <SFML/Graphics.hpp>
#include "../assets/Assets.hpp"

class LevelInfo
{
    public:
        LevelInfo() {};
        ~LevelInfo() {};

        void set(std::string l, std::string n, std::string d, std::string d2, std::string d3 )
        {
            level.setString( l );
            name.setString(n);

            description.setString( d ); 
            description2.setString( d2 ); 
            description3.setString( d3 ); 
        }

        void setup(sf::RenderWindow &win)
        {
            level.setFont(Assets::font);
            level.setFillColor(sf::Color::White);
            level.setCharacterSize( 120.f );
            level.setPosition(sf::Vector2f( 0 , - 300 ));
            level.setOrigin( level.getGlobalBounds().width / 2.f , level.getGlobalBounds().height /2.f  ); 

            name.setFont(Assets::font);  
            name.setPosition(sf::Vector2f(0, -180));
            name.setOrigin( name.getGlobalBounds().width / 2.f , name.getGlobalBounds().height /2.f  ); 

            name.setFillColor(sf::Color::White);
            name.setCharacterSize( 60 );

            description.setFont(Assets::font);  
            description.setFillColor(sf::Color::White);
            description.setCharacterSize( 22 );
            description.setPosition(sf::Vector2f(0, -16  ));
            description.setOrigin( description.getGlobalBounds().width / 2.f , description.getGlobalBounds().height /2.f  ); 

            description2.setFont(Assets::font);  
            description2.setFillColor(sf::Color::White);
            description2.setCharacterSize( 22 );
            description2.setPosition(sf::Vector2f(0, 16 ));
            description2.setOrigin( description2.getGlobalBounds().width / 2.f , description2.getGlobalBounds().height /2.f  ); 

            description3.setFont(Assets::font);  
            description3.setFillColor(sf::Color::White);
            description3.setCharacterSize( 16 );
            description3.setPosition(sf::Vector2f(0, 300 ));
            description3.setOrigin( description3.getGlobalBounds().width / 2.f , description3.getGlobalBounds().height /2.f  ); 

        }

        void onDraw(sf::RenderWindow &win)
        {
            sf::View view( sf::FloatRect(0.f, 0.f, win.getSize().x , win.getSize().y));
            view.setCenter(0,0);
            win.setView(view);

            setup(win);
            win.draw(level);
            win.draw(name);
            win.draw(description);
            win.draw(description2);
            win.draw(description3);
        }
    
    private:
        sf::Text level;
        sf::Text name;
        sf::Text description;
        sf::Text description2;
        sf::Text description3;
};