#include "Entity.h"
#include <Graphics/Skins/Skin.h>

Entity::Entity()
{
    //ctor
    mSkin = 0;
    mBody = 0;
}

Entity::~Entity()
{
    //dtor
}

void Entity::render()
{
    mSkin->render(mBody);
}
