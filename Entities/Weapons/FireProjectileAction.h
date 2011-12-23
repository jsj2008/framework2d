#ifndef FIREPROJECTILEACTION_H
#define FIREPROJECTILEACTION_H

#include <Entities/Weapons/WeaponAction.h>
#include <AbstractFactory/AutoSelfFactory.h>

class FireProjectileAction : public WeaponAction
{
    public:
        struct ImmutableData
        {
            void init(FactoryLoader* _loader, AbstractFactories* _factories);
            AbstractFactoryBase<Entity>* projectileFactory;
        };
        FireProjectileAction(const FireProjectileAction::ImmutableData& _immutableData, FactoryParameters* _parameters);
        virtual ~FireProjectileAction();
        static std::string factoryName()
        {
            return "FireProjectileActionFactory";
        }
        void fire(const Vec2f& _source, const Vec2f& _position);
    protected:
    private:
        const FireProjectileAction::ImmutableData& immutableData;

};

#endif // FIREPROJECTILEACTION_H
