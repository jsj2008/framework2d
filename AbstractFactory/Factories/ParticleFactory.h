#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class ParticleFactory : public AbstractFactory<Entity, ParticleFactory>
{
    public:
        ParticleFactory(FactoryLoader* loader);
        virtual ~ParticleFactory();
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "ParticleFactory";
        }
    protected:
    private:
        float density;
        int lifetime;
        std::string materialName;

        b2CircleShape shape;
};

#endif // PARTICLEFACTORY_H
