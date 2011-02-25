#include "CrateFactory.h"
#include <Entities/Crate.h>
using namespace std;

CrateFactory::CrateFactory()
{
    //ctor
}

CrateFactory::~CrateFactory()
{
    //dtor
}
Entity* CrateFactory::createEntity(FactoryDef* data)
{
    Entity* ret = new Crate;
    return ret;
}
