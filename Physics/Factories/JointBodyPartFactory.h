#ifndef JOINTBODYPARTFACTORY_H
#define JOINTBODYPARTFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Box2D/Box2D.h>
class PhysicsManager;

class JointBodyPartFactory : public AbstractFactory<BodyPart, JointBodyPartFactory>
{
    public:
        JointBodyPartFactory();
        virtual ~JointBodyPartFactory();
        static std::string name()
        {
            return "JointBodyPartFactory";
        }
        void init(FactoryLoader* _loader, AbstractFactories* _factories);
        BodyPart* useFactory(FactoryParameters* _parameters);
    protected:
    private:
        b2RevoluteJointDef jointDef;
        PhysicsManager* world;
};

#endif // JOINTBODYPARTFACTORY_H
