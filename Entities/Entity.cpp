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
    delete mSkin;
}

void Entity::render()
{
    mSkin->render(mBody);
}
