#ifndef CRATEFACTORY_H
#define CRATEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Skin;
class BodyPart;
class Entity;
class FactoryLoader;

class CrateFactory : public AbstractFactory<Entity, CrateFactory>
{
    public:
        CrateFactory();
        virtual ~CrateFactory();
        Entity* useFactory(FactoryParameters* _parameters);
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "CrateFactory";
        }
    protected:
        AbstractFactoryBase<Skin>* skinFactory;
        AbstractFactoryBase<BodyPart>* bodyFactory;
    private:
};

#endif // CRATEFACTORY_H
