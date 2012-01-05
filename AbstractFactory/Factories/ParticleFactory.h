#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;
class PhysicsManager;
class Skin;

class ParticleFactory : public AbstractFactory<Entity, ParticleFactory>
{
    public:
        ParticleFactory();
        virtual ~ParticleFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "ParticleFactory";
        }
    protected:
    private:
        float density;
        int lifetime;
        std::string materialName;

        AbstractFactoryBase<BodyPart>* bodyFactory;
        AbstractFactoryBase<Skin>* skinFactory;
};

#endif // PARTICLEFACTORY_H
