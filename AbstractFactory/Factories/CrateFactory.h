#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>


class CrateFactory : public AbstractFactory
{
    public:
        CrateFactory(const std::string& _materialName, float density);
        virtual ~CrateFactory();
        Entity* useFactory(FactoryParameters* parameters);
    protected:
        Vec2f dimensions;
        float density;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
        std::string materialName;
    private:
};

#endif // CRATEFACTORY_H
