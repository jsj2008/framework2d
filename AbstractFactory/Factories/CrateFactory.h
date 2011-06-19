#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
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
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
        std::string materialName;
    private:
};

#endif // CRATEFACTORY_H
