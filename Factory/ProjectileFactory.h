#ifndef PROJECTILEFACTORY_H
#define PROJECTILEFACTORY_H

#include <Factory/Factory.h>
#include <Box2D/Box2D.h>

class ProjectileFactory : public Factory
{
    public:
        ProjectileFactory();
        virtual ~ProjectileFactory();
        Entity* createEntity(FactoryDef* data);
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2CircleShape shapeDef;
};

#endif // PROJECTILEFACTORY_H
