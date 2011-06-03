#ifndef WEAPON_H
#define WEAPON_H

class Vec2f;

class Weapon
{
    public:
        Weapon();
        virtual ~Weapon();
        virtual void fire(const Vec2f& source, const Vec2f& direction)=0;
    protected:
    private:

};

#endif // WEAPON_H
