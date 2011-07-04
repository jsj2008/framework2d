#ifndef AIENTITYFACTORY_H
#define AIENTITYFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;
class b2Body;
class Brain;
class Skin;

class AIEntityFactory : public AbstractFactory<Entity, AIEntityFactory>
{
    public:
        AIEntityFactory(FactoryLoader* loader);
        virtual ~AIEntityFactory();
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "AIEntityFactory";
        }
    protected:
    private:
        std::string weapon;
        AbstractFactoryBase<b2Body>* bodyFactory;
        AbstractFactoryBase<Brain>* brainFactory;
        AbstractFactoryBase<Skin>* skinFactory;
        std::string materialName;
};

#endif // AIENTITYFACTORY_H