#ifndef PROJECTILEFACTORY_H
#define PROJECTILEFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Box2D/Box2D.h>
class FactoryLoader;

class ProjectileFactory : public AbstractFactory<Entity, ProjectileFactory>
{
    public:
        ProjectileFactory(FactoryLoader* loader);
        virtual ~ProjectileFactory();
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

        std::string material;
        float radius;

        short damage;
        std::string explosion;
        /// Expiry parameters
        float expiryTime;
        float maximumImpact;
        float proximity;
};

#endif // PROJECTILEFACTORY_H
