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
        void addBody(StandardFactoryDef def){level->addBody(def);}
        void addJoint(b2JointDef* def){level->addJoint(def);}
        void removeBody(b2Body* body){level->removeBody(body);}
        void renderBackLayers(){level->renderBackLayers();}
        void tempRender(){level->tempRender();}
        void removeJoint(b2Joint* joint){level->removeJoint(joint);}
        void loadLevel(const char* name){level = new Level(name);}
        void saveLevel(const char* name){delete level;}
    protected:
    private:
        Level* level;
}g_LevelManager;

#endif // LEVELMANAGER_H
