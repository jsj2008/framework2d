#ifndef AIENTITYFACTORY_H
#define AIENTITYFACTORY_H

#include <Factory/Factory.h>
#include <Box2D/Box2D.h>


class AIEntityFactory : public Factory
{
    public:
        AIEntityFactory();
        virtual ~AIEntityFactory();
        Entity* createEntity(FactoryDef* data);
    protected:
    private:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
        b2BodyDef wheelBody;
        b2FixtureDef wheelFixture;
        b2CircleShape wheelShape;
        b2RevoluteJointDef wheelJoint;

        b2BodyDef jumpBody;
        b2FixtureDef jumpFixture;
        b2PolygonShape jumpShape;
        Vec2f jumpAxis;
        b2PrismaticJointDef jumpJoint;
};

#endif // AIENTITYFACTORY_H
