#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <string>
#include <AbstractFactory/FactoryParameters.h>
class Entity;
class b2Joint;
class b2JointDef;
class TextureContext;
class ParallaxLayer;
class PhysicsManager;
class EntityList;

class Level
{
    public:
        Level(const char* _name);
        virtual ~Level();
        Entity* addBody(const std::string& factory, FactoryParameters* parameters);
        void addJoint(b2JointDef* def);
        void render();
        void renderBackLayers();
        void removeBody(Entity* body, std::pair<std::string,FactoryParameters>* _saveConstruction = nullptr);
        void removeJoint(b2Joint* joint);
        void tick();
        PhysicsManager* getWorld(){return world;}
        void loadLevel();
        EntityList* getEntityList(){return entityList;}
    protected:
    private:
        const char* name;
        void saveLevel();
        std::unordered_map<b2Joint*, b2JointDef*> jointToDefTable;
        Vec2f backgroundScale;
        Vec2f backgroundTransform;
        std::vector<ParallaxLayer*> parallaxLayers;

        std::unordered_map<Entity*, std::pair<std::string,FactoryParameters> > table;

        PhysicsManager* world;
        EntityList* entityList;
};

#endif // LEVEL_H
