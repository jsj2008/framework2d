#include "Entity.h"
#include <Graphics/Skins/Skin.h>
#include <AbstractFactory/AbstractFactories.h>

Entity::Entity()
{
    //ctor
    mSkin = 0;
    mBody = 0;
}

Entity::~Entity()
{
    //dtor
    delete mSkin;
}

void Entity::render()
{
    mSkin->render(mBody);
}
