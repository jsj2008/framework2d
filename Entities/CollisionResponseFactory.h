#ifndef COLLISIONRESPONSEFACTORY_H
#define COLLISIONRESPONSEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Entities/CollisionDatabase.h>

class CollisionResponseFactory : public AbstractFactory<CollisionResponse, CollisionResponseFactory>
{
    public:
        CollisionResponseFactory();
        virtual ~CollisionResponseFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        static std::string name()
        {
            return "CollisionResponseFactory";
        }
        CollisionResponse* useFactory(FactoryParameters* parameters);
    protected:
    private:
        CollisionResponse* handle;
};

#endif // COLLISIONRESPONSEFACTORY_H
