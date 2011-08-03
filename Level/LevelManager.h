#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <Entities/StaticGeometry.h>
#include <Level/Level.h>
class FactoryParameters;

class LevelManager
{
    public:
        LevelManager();
        virtual ~LevelManager();
        Level* getLevel(){return level;}
        void addJoint(b2JointDef* def){level->addJoint(def);}
        void renderBackLayers(){level->renderBackLayers();}
        void render(){level->render();}
        void removeJoint(b2Joint* joint){level->removeJoint(joint);}
        Level* loadLevel(const char* name){level = new Level(name); return level;}
        void saveLevel(const char* name){delete level;}
        bool update(){return level->update();}
    protected:
    private:
        Level* level;
};

#endif // LEVELMANAGER_H
