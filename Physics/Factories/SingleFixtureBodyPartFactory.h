#ifndef SINGLEFIXTUREBODYPARTFACTORY_H
#define SINGLEFIXTUREBODYPARTFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Box2D/Box2D.h>

class SingleFixtureBodyPartFactory : public AbstractFactory<BodyPart, SingleFixtureBodyPartFactory>
{
    public:
        SingleFixtureBodyPartFactory();
        virtual ~SingleFixtureBodyPartFactory();
        void init(FactoryLoader* _loader, AbstractFactories* _factories);
        BodyPart* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "SingleFixtureBodyPartFactory";
        }
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        AbstractFactoryBase<CollisionResponse>* responseFactory;
        AbstractFactoryBase<b2Shape>* shapeFactory;
        PhysicsManager* physicsManager;
};

#endif // SINGLEFIXTUREBODYPARTFACTORY_H
