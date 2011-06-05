#ifndef EXPLOSIONFACTORY_H
#define EXPLOSIONFACTORY_H

#include <string>
#include <AbstractFactory/AbstractFactory.h>
#include <Box2D/Box2D.h>
class FactoryLoader;

class ExplosionFactory : public AbstractFactory
{
    public:
        ExplosionFactory(FactoryLoader* loader);
        virtual ~ExplosionFactory();
        Entity* useFactory(FactoryParameters* parameters);
    protected:
    private:
        std::string material;
        float damage;
        float force;
        float time;

        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2CircleShape shapeDef;
};

#endif // EXPLOSIONFACTORY_H
