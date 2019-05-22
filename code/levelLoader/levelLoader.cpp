#include "levelLoader.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

#include "../lib/json/json.hpp"


LevelLoader::LevelLoader(HandleCreator& creator)
    :m_handleCreator(creator)
{

}

LevelData LevelLoader::load(std::string filepatch)
{
    std::cout << "[LOADER] Start => " << filepatch << std::endl;

    LevelData data;
    const float box2DmaxWorldSize = 20.f;
    float Scale = 0.f;

    std::ifstream file(filepatch);
    if (!( file.is_open() )) return data;

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string string = buffer.str();

    json::JSON parser = json::JSON::Load(string);

    int gravity = parser["layers"][0]["properties"]["Gravity"].ToInt();
    std::cout << "[ARGUMENTS](WORLD) Gravity => (" << gravity << ")\n";

    m_handleCreator.setGravity(b2Vec2( 0, gravity));

    data.name = parser["layers"][0]["properties"]["Name"].ToString();
    data.desc1 = parser["layers"][0]["properties"]["Desc1"].ToString();
    data.desc2 = parser["layers"][0]["properties"]["Desc2"].ToString();

    std::cout << "[ARGUMENTS](WORLD) Info => (" << data.name << "," << data.desc1 << "," << data.desc2 << ")\n";

    int sizeX = parser["layers"][0]["properties"]["SizeX"].ToInt();
    int sizeY = parser["layers"][0]["properties"]["SizeY"].ToInt();

    std::cout << "[ARGUMENTS](WORLD) SizeX and SizeY => (" << sizeX << "," << sizeY << ")\n";

    float LargeSizeMap = std::max( sizeX, sizeY );
    //float LargeSizeMap = sizeY;

    Scale = box2DmaxWorldSize / LargeSizeMap;


    json::JSON objects = parser["layers"][0]["objects"];


    for( auto &object : objects.ArrayRange() )
    {
        b2Vec2 pos;
        if( LargeSizeMap == sizeX )
            pos = b2Vec2 (object["x"].ToInt()*Scale - 10.f , object["y"].ToInt()*Scale - (sizeY* Scale / 2 )  );
        else 
            pos = b2Vec2  (object["x"].ToInt()*Scale - (sizeX *Scale / 2) , object["y"].ToInt()*Scale - 10.f  );
            
        std::string type = object["type"].ToString();
        json::JSON polygon =  object["polygon"];

        int ammount = polygon.ArrayRange().end() - polygon.ArrayRange().begin();
        b2Vec2 tab[50];
        int i =0;
        for( auto &vertex : polygon.ArrayRange() )
        {
            tab[i] = b2Vec2( vertex["x"].ToInt() * Scale , vertex["y"].ToInt() * Scale );
            i++;
        }
        json::JSON property = object["properties"];

        std::map<std::string,std::string> map;


        for( auto &j : property.ObjectRange() )
        {
            std::stringstream  key; 
            key << j.first;

            std::stringstream  value; 
            value << j.second;
            

            map[key.str()] = value.str();
        }

        m_handleCreator.create(type,pos,tab,ammount, map);
    }

    data.isLoad = true;
    return data;
}

