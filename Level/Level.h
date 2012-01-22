#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <string>
#include <GameObject.h>
#include <AbstractFactory/AbstractFactories.h>
class Entity;
class b2Joint;
class b2JointDef;
class TextureContext;
class PhysicsManager;
class EntityList;

class Level : public GameObject<Level>
{
    public:
        Level(PhysicsManager* _world, AbstractFactories* _factories);
        virtual ~Level();
        Entity* addBody(const std::string& factory, FactoryParameters* _parameters);
        void addJoint(b2JointDef* def);
        void render();
        void renderBackLayers();
        void removeBody(Entity* body, std::pair<std::string,FactoryParameters>* _saveConstruction = nullptr);
        void removeJoint(b2Joint* joint);
        void tick();
        PhysicsManager* getWorld(){return world;}
        AbstractFactories* getFactories();
        void loadLevel();
        EntityList* getEntityList(){return entityList;}

        static void registerActions(GameObjectType* _type);
        static std::string name()
        {
            return "Level";
        }
    protected:
    private:
        void saveLevel();
        std::unordered_map<b2Joint*, b2JointDef*> jointToDefTable;

        std::unordered_map<Entity*, std::pair<std::string,FactoryParameters> > table;

        PhysicsManager* world;
        EntityList* entityList;
        AbstractFactories* factories;
};

#endif // LEVEL_H
