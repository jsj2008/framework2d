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
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape shapeDef;
};

#endif // AIENTITYFACTORY_H
