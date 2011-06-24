#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;

class CrateFactory : public AbstractFactory<Entity, CrateFactory>
{
    public:
        CrateFactory(FactoryLoader* loader);
        virtual ~CrateFactory();
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "CrateFactory";
        }
    protected:
        Vec2f dimensions;
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
    private:
};

#endif // CRATEFACTORY_H
