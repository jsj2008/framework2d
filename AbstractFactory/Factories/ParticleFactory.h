#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class ParticleFactory : public AbstractFactory
{
    public:
        ParticleFactory(FactoryLoader* loader);
        virtual ~ParticleFactory();
        Entity* useFactory(FactoryParameters* parameters);
    protected:
    private:
        float density;
        int lifetime;
        std::string materialName;

        b2CircleShape shape;
};

#endif // PARTICLEFACTORY_H
