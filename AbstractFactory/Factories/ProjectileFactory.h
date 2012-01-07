#ifndef PROJECTILEFACTORY_H
#define PROJECTILEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Box2D/Box2D.h>
class Entity;
class FactoryLoader;
class PhysicsManager;
class Skin;

class ProjectileFactory : public AbstractFactory<Entity, ProjectileFactory>
{
    public:
        ProjectileFactory();
        virtual ~ProjectileFactory();
        void init(FactoryLoader* loader, AbstractFactories* factories);
        Entity* useFactory(FactoryParameters* _parameters);
        static std::string name()
        {
            return "ProjectileFactory";
        }
    protected:
    private:
        AbstractFactoryBase<BodyPart>* bodyFactory;
        AbstractFactoryBase<Skin>* skinFactory;
        float radius;

        short damage;
        AbstractFactoryBase<Entity>* explosionFactory;
        /// Expiry _parameters
        float expiryTime;
        float maximumImpact;
        float proximity;
};

#endif // PROJECTILEFACTORY_H
