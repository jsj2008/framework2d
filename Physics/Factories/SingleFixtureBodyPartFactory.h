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
        PhysicsManager* physicsManager;
        enum ShapeType
        {
            e_Circle = b2Shape::e_circle,
            e_Polygon = b2Shape::e_polygon,
            e_Rect,
            e_ShapeTypeMax,
        };
        ShapeType type;
};

#endif // SINGLEFIXTUREBODYPARTFACTORY_H
