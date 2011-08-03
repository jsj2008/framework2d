#ifndef EXPLOSIONFACTORY_H
#define EXPLOSIONFACTORY_H

#include <string>
#include <AbstractFactory/AbstractFactory.h>
#include <Box2D/Box2D.h>
class FactoryLoader;
class Entity;
class PhysicsManager;

class ExplosionFactory : public AbstractFactory<Entity, ExplosionFactory>
{
    public:
        ExplosionFactory();
        virtual ~ExplosionFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "ExplosionFactory";
        }
    protected:
    private:
        std::string material;
        float damage;
        float force;
        float time;

        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2CircleShape shapeDef;
        PhysicsManager* physicsManager;
};

#endif // EXPLOSIONFACTORY_H
