#include "Weapon.h"
#include <Timer.h>

Weapon::Weapon(const ContentHandler<WeaponContent>& _content)
{
    //ctor
    content = _content;
    lastFireFrame = 0;
}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::fire(const Vec2f& source, const Vec2f& direction)
{
    unsigned int frame = g_Timer.getFrame();
    unsigned int frames = frame - lastFireFrame;
    if (frames > content->getReloadFrames())
    {
        lastFireFrame = frame;
        content->fire(source, direction);
    }
}
