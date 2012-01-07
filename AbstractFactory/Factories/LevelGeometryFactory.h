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
        Entity* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "LevelGeometryFactory";
        }
    protected:
    private:
        AbstractFactoryBase<CollisionResponse>* collisionResponse;

        AbstractFactoryBase<Skin>* skinFactory;
        AbstractFactoryBase<BodyPart>* bodyFactory;
};

#endif // LEVELGEOMETRYFACTORY_H
