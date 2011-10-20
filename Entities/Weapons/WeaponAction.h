#ifndef WEAPONACTION_H
#define WEAPONACTION_H

class Vec2f;

class WeaponAction
{
    public:
        WeaponAction();
        virtual ~WeaponAction();
        virtual void fire(const Vec2f& _source, const Vec2f& _position)=0;
    protected:
    private:
};

#endif // WEAPONACTION_H
