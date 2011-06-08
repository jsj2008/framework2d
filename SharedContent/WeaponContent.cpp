#include "WeaponContent.h"
#include <Factory/FactoryDefList.h>
#include <AbstractFactory/AbstractFactoryList.h>
#include <AbstractFactory/FactoryParameters.h>

WeaponContent::WeaponContent(const char* _name)
:SharedContent(_name)
{
    //ctor
    projectile = "grenade";
    reloadFrames = 10;
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
    //PositionVelocityParameters parameters(position,direction*100);
    FactoryParameters parameters({{"position",position},{"v",direction*100}});
    g_AbstractFactoryList.useFactory(projectile,&parameters);
}
