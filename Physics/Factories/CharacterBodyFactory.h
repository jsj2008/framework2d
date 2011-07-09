#ifndef CHARACTERBODYFACTORY_H
#define CHARACTERBODYFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Box2D/Box2D.h>
class FactoryLoader;

class CharacterBodyFactory : public AbstractFactory<b2Body, CharacterBodyFactory>
{
    public:
        CharacterBodyFactory();
        virtual ~CharacterBodyFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        b2Body* useFactory(FactoryParameters* params);
        static std::string name()
        {
            return "CharacterBodyFactory";
        }
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
        b2BodyDef wheelBody;
        b2FixtureDef wheelFixture;
        b2CircleShape wheelShape;
        b2RevoluteJointDef wheelJoint;

        Vec2f dimensions;
};

#endif // CHARACTERBODYFACTORY_H
