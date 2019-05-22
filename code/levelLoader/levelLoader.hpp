#pragma once

#include <Box2D/Box2D.h>
#include <map>

class HandleCreator
{
    public:
        virtual ~HandleCreator() {};

        virtual void setGravity(b2Vec2 g) =0;
        virtual void create(std::string type, b2Vec2 pos, b2Vec2* tab, int ammount, std::map<std::string,std::string>& map) =0;
};

struct LevelData 
{
    bool isLoad = false;
    std::string name;
    std::string desc1;
    std::string desc2;
};  

class LevelLoader
{
    public:
        LevelLoader(HandleCreator& creator);
        LevelData load(std::string filepatch);

    protected:
        HandleCreator& m_handleCreator;

};