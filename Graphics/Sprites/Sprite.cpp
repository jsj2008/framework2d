#include "Sprite.h"
#ifndef NULL
#define NULL 0
#endif

Sprite::Sprite(Skin* _skin)
{
    //ctor
    skin = _skin;
    next = prev = NULL;
}

Sprite::~Sprite()
{
    //dtor
}
