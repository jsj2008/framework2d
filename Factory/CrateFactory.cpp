#include "CrateFactory.h"
#include <Entities/Crate.h>

CrateFactory::CrateFactory(int _width, int _height)
{
    //ctor
    width = _width;
    height = _height;
}

CrateFactory::~CrateFactory()
{
    //dtor
}
Entity* CrateFactory::createEntity(Vec2f* origin)
{
    Entity* ret = new Crate;
    return ret;
}
