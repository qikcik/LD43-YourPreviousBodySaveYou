#include <iostream>
#include <fstream>
#include <sstream>



#include "SFML/Graphics.hpp"
#include "window/gameLoop.hpp"
#include "game/gameState.hpp"
#include "assets/Assets.hpp"

int main(int argc, char **argv)
{
    Assets::loadAll();
    sf::RenderWindow window(sf::VideoMode(1280,720),"LD43");
    GameLoop game( window );

    if(argc > 1) 
    {
        std::cout << "[DebugMode] Level =>" << argv[1] << std::endl;
        game.run( new GameState( std::stof( argv[1], 0 ) )) ;
    }
    else game.run( new GameState( 0 )) ;

    return 0;
}