#ifndef LEVELGEOMETRYFACTORY_H
#define LEVELGEOMETRYFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;
class PhysicsManager;
class Skin;

class LevelGeometryFactory : public AbstractFactory<Entity, LevelGeometryFactory>
{
    public:
        LevelGeometryFactory();
        virtual ~LevelGeometryFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "LevelGeometryFactory";
        }
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
        PhysicsManager* physicsManager;
        AbstractFactoryBase<CollisionResponse>* collisionResponse;

        AbstractFactoryBase<Skin>* skinFactory;
};

#endif // LEVELGEOMETRYFACTORY_H
