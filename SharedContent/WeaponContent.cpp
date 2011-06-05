#include "WeaponContent.h"
#include <Factory/ProjectileDef.h>
#include <Factory/FactoryDefList.h>

WeaponContent::WeaponContent(const char* _name)
:SharedContent(_name)
{
    //ctor
}

WeaponContent::~WeaponContent()
{
    //dtor
}

void WeaponContent::load()
{

}
void WeaponContent::unload()
{

}

void WeaponContent::vGrab()
{

}
void WeaponContent::vRelease()
{

}
void WeaponContent::fire(const Vec2f& source, const Vec2f& direction)
{
    Vec2f position = source;
    position += direction*3;
    g_FactoryDefList.singleUse(def);
}
