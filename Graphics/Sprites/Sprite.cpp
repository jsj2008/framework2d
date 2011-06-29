#include "Sprite.h"

Sprite::Sprite(Skin* _skin)
{
    //ctor
    skin = _skin;
    next = prev = nullptr;
}

Sprite::~Sprite()
{
    //dtor
}
