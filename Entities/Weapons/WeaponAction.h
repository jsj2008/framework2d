#ifndef WEAPONACTION_H
#define WEAPONACTION_H

#include <GameObject.h>
class Vec2f;

class WeaponAction: public GameObject<WeaponAction>
{
    public:
        WeaponAction();
        virtual ~WeaponAction();
        static void registerActions();
        virtual void fire(const Vec2f& _source, const Vec2f& _position)=0;
    protected:
    private:
};

#endif // WEAPONACTION_H
