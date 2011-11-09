#include "EntityData.h"
#include <AbstractFactory/AbstractFactories.h>
#include <Entities/Entity.h>

EntityData::EntityData(const char* _type, FactoryParameters* _params)
{
    //ctor
    type = _type;
    params = _params;
}

EntityData::~EntityData()
{
    //dtor
    delete params;
}

void EntityData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{

}

void EntityData::build(AbstractFactories* _factories)
{
    _factories->useFactory<Entity>(type, params);
}
