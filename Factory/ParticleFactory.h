#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H

#include <Factory/Factory.h>
#include <Physics/PhysicsManager.h>


class ParticleFactory : public Factory
{
    public:
        ParticleFactory();
        virtual ~ParticleFactory();
        Entity* createEntity(FactoryDef* def);
    protected:
    private:
        b2BodyDef bodyDef;
        b2CircleShape shape;
};

#endif // PARTICLEFACTORY_H
