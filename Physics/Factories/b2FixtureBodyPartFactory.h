#ifndef b2FixtureBodyPartFACTORY_H
#define b2FixtureBodyPartFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Box2D/Box2D.h>

class b2FixtureBodyPartFactory : public AbstractFactory<BodyPart, b2FixtureBodyPartFactory>
{
    public:
        b2FixtureBodyPartFactory();
        virtual ~b2FixtureBodyPartFactory();
        void init(FactoryLoader* _loader, AbstractFactories* _factories);
        BodyPart* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "b2FixtureBodyPartFactory";
        }
    protected:
    private:
        AbstractFactoryBase<CollisionResponse>* responseFactory;
        PhysicsManager* physicsManager;
        b2FixtureDef fixtureDef;
        enum ShapeType
        {
            e_Circle = b2Shape::e_circle,
            e_Polygon = b2Shape::e_polygon,
            e_Rect,
            e_ShapeTypeMax,
        };
        ShapeType type;
};

#endif // b2FixtureBodyPartFACTORY_H
