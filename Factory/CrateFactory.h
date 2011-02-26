#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include "Factory.h"
#include <Physics/PhysicsManager.h>


class CrateFactory : public Factory
{
    public:
        CrateFactory();
        virtual ~CrateFactory();
        Entity* createEntity(FactoryDef* data);
    protected:
    private:
        b2BodyDef bodyDef;
        b2PolygonShape shape;
        float density;
};

#endif // CRATEFACTORY_H
