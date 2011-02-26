#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <unordered_map>
#include <Factory/ConvexGeometryDef.h>
#include <Entities/StaticGeometry.h>
#include <Factory/CrateDef.h>
#include <Level/Level.h>

extern class LevelManager
{
    public:
        LevelManager();
        virtual ~LevelManager();
        void addPlatform(ConvexGeometryDef* def){return level->addPlatform(def);}
        void addCrate(CrateDef* def){return level->addCrate(def);}
        void removeBody(b2Body* body){return level->removeBody(body);}
        void loadLevel(const char* name){level = new Level(name);}
        void saveLevel(const char* name){delete level;}
    protected:
    private:
        Level* level;
}g_LevelManager;

#endif // LEVELMANAGER_H
