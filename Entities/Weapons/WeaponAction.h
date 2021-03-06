#ifndef WEAPONACTION_H
#define WEAPONACTION_H

#include <GameObject.h>
class Vec2f;

class WeaponAction: public GameObject<WeaponAction>
{
    public:
        WeaponAction();
        virtual ~WeaponAction();
        static void registerActions(GameObjectType* _type);
        virtual void fire(const Vec2f& _source, const Vec2f& _position)=0;

        static std::string name()
        {
            return "WeaponAction";
        }
    protected:
    private:
};

#endif // WEAPONACTION_H
