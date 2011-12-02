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
        Entity* useFactory(FactoryParameters* parameters);
        static std::string name()
        {
            return "ProjectileFactory";
        }
    protected:
    private:
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2CircleShape shapeDef;
        PhysicsManager* physicsManager;

        AbstractFactoryBase<Skin>* skinFactory;
        float radius;

        short damage;
        AbstractFactoryBase<Entity>* explosionFactory;
        /// Expiry parameters
        float expiryTime;
        float maximumImpact;
        float proximity;
        AbstractFactoryBase<CollisionResponse>* collisionResponse;
};

#endif // PROJECTILEFACTORY_H
