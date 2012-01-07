#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;
class PhysicsManager;
class Skin;

class TileFactory : public AbstractFactory<Entity, TileFactory>
{
    public:
        TileFactory();
        virtual ~TileFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "TileFactory";
        }
    protected:
    private:
        AbstractFactoryBase<BodyPart>* bodyFactory;

        AbstractFactoryBase<Skin>* skinFactory;
};

#endif // TILEFACTORY_H
