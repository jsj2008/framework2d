#ifndef WEAPON_H
#define WEAPON_H

#include <GameObject.h>
#include <AbstractFactory/AbstractFactory.h>
class Vec2f;
class FiringMechanism;
class WeaponAction;

/*
    Control mechanism

    Projectile weapon : Projectile factory, firing mechanism

    Control mechanism (input; drag and drop, fire in direction, place at point)
    Firing mechanism (how the gun operates; full auto, targeting system, create at point)
    Action (fire projectile, teleport, make bubble)
*/
class Weapon : public GameObject<Weapon>
{
    public:
        struct ImmutableData
        {
            AbstractFactoryBase<FiringMechanism>* mechanismFactory;
            AbstractFactoryBase<WeaponAction>* actionFactory;
            void init(FactoryLoader* _loader, AbstractFactories * _factories);
        };
        Weapon(const Weapon::ImmutableData&, FactoryParameters* _parameters);
        virtual ~Weapon();
        virtual void fireBegin(const Vec2f& source, const Vec2f& position){}
        virtual void fireMove(const Vec2f& source, const Vec2f& position){}
        void fireEnd(const Vec2f& source, const Vec2f& position);

        static std::string factoryName()
        {
            return "WeaponFactory";
        }
        static std::string name()
        {
            return "Weapon";
        }

        static void registerActions(GameObjectType* _type);
    protected:
    private:
        const Weapon::ImmutableData& data;
        FiringMechanism* mechanism;
        WeaponAction* action;
};

#endif // WEAPON_H
