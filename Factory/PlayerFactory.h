#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include <Factory/Factory.h>
#include <Physics/PhysicsManager.h>


class PlayerFactory : public Factory
{
    public:
        PlayerFactory();
        virtual ~PlayerFactory();
        Entity* createEntity(FactoryDef* def);
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
};

#endif // PLAYERFACTORY_H
