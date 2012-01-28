#ifndef MULTIFIXTUREBODYPARTFACTORY_H
#define MULTIFIXTUREBODYPARTFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Physics/BodyParts/BodyPart.h>
#include <Box2D/Box2D.h>

class MultiFixtureBodyPartFactory : public AbstractFactory<BodyPart, MultiFixtureBodyPartFactory>
{
    public:
        MultiFixtureBodyPartFactory();
        virtual ~MultiFixtureBodyPartFactory();
        void init(FactoryLoader* _loader, AbstractFactories* _factories);
        BodyPart* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "MultiFixtureBodyPartFactory";
        }
    protected:
    private:
        AbstractFactoryBase<BodyPart>* bodyFactory;
        std::vector<AbstractFactoryBase<BodyPart>*> fixtureFactories;
};

#endif // MULTIFIXTUREBODYPARTFACTORY_H
