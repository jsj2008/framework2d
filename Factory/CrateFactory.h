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
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
};

#endif // CRATEFACTORY_H
