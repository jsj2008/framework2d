#ifndef AIENTITYFACTORY_H
#define AIENTITYFACTORY_H

#include <Box2D/Box2D.h>
#include <AbstractFactory/AbstractFactory.h>
class Entity;
class FactoryLoader;

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
        std::string materialName;
};

#endif // AIENTITYFACTORY_H
