#ifndef BUBBLEFACTORY_H
#define BUBBLEFACTORY_H

#include <Factory/Factory.h>
#include <Physics/PhysicsManager.h>


class BubbleFactory : public Factory
{
    public:
        BubbleFactory();
        virtual ~BubbleFactory();
        Entity* createEntity(FactoryDef* data);
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2CircleShape shapeDef;
};

#endif // BUBBLEFACTORY_H
