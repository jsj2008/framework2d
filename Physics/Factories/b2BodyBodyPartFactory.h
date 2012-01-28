#ifndef B2BODYBODYPARTFACTORY_H
#define B2BODYBODYPARTFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Box2D/Dynamics/b2Body.h>

class b2BodyBodyPartFactory : public AbstractFactory<BodyPart, b2BodyBodyPartFactory>
{
    public:
        b2BodyBodyPartFactory();
        virtual ~b2BodyBodyPartFactory();
        void init(FactoryLoader* _loader, AbstractFactories* _factories);
        BodyPart* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "b2BodyBodyPartFactory";
        }
    protected:
    private:
        PhysicsManager* physicsManager;
        b2BodyDef bodyDef;
};

#endif // B2BODYBODYPARTFACTORY_H
