#ifndef WEAPON_H
#define WEAPON_H

#include <SharedContent/WeaponContent.h>
class Vec2f;

class Weapon
{
    public:
        Weapon(const ContentHandler<WeaponContent>& _content);
        virtual ~Weapon();
        void fire(const Vec2f& source, const Vec2f& direction);
    protected:
    private:
        ContentHandler<WeaponContent> content;
        unsigned short lastFireFrame;

};

#endif // WEAPON_H
