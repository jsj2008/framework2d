#ifndef EXPLOSIONFACTORY_H
#define EXPLOSIONFACTORY_H

#include <string>
#include <AbstractFactory/AbstractFactory.h>
#include <Box2D/Box2D.h>
class FactoryLoader;
class Entity;
class PhysicsManager;
class Skin;
class BodyPart;

class ExplosionFactory : public AbstractFactory<Entity, ExplosionFactory>
{
    public:
        ExplosionFactory();
        virtual ~ExplosionFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "ExplosionFactory";
        }
    protected:
    private:
        float damage;
        float force;
        float time;
        float radius;

        AbstractFactoryBase<Skin>* skinFactory;
        AbstractFactoryBase<BodyPart>* bodyFactory;
};

#endif // EXPLOSIONFACTORY_H
