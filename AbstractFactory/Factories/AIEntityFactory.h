#ifndef AIENTITYFACTORY_H
#define AIENTITYFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
class FactoryLoader;

class AIEntityFactory : public AbstractFactory
{
    public:
        AIEntityFactory(FactoryLoader* loader);
        virtual ~AIEntityFactory();
        Entity* useFactory(FactoryParameters* parameters);
    protected:
    private:
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
        b2BodyDef wheelBody;
        b2FixtureDef wheelFixture;
        b2CircleShape wheelShape;
        b2RevoluteJointDef wheelJoint;

        int aiType;
        Vec2f dimensions;
        std::string weapon;
        std::string materialName;
};

#endif // AIENTITYFACTORY_H
