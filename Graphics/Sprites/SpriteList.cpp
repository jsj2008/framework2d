#include "SpriteList.h"
#include <Graphics/Sprites/Sprite.h>

SpriteList::SpriteList()
{
    //ctor
}

SpriteList::~SpriteList()
{
    //dtor
}

void SpriteList::addSprite(Sprite* _sprite)
{
    first->prev = _sprite;
    _sprite->next = first;
    first = _sprite;
}
void SpriteList::deleteSprite(Sprite* _sprite)
{
    _sprite->prev->next = _sprite->next;
    _sprite->next->prev = _sprite->prev;
    delete _sprite;
}
