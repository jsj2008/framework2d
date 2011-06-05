#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>


class ParticleFactory : public AbstractFactory
{
    public:
        ParticleFactory(float _density, int _lifetime);
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
