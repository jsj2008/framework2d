#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;

class CrateFactory : public AbstractFactory<Entity, CrateFactory>
{
    public:
        CrateFactory();
        virtual ~CrateFactory();
        Entity* useFactory(FactoryParameters* parameters);
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "CrateFactory";
        }
    protected:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
        AbstractFactoryBase<Skin>* skinFactory;
    private:
};

#endif // CRATEFACTORY_H
