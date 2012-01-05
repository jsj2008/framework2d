#include "EntityData.h"
#include <AbstractFactory/AbstractFactories.h>
#include <Level/PropertyBagData.h>
#include <Entities/Entity.h>

EntityData::EntityData(const char* _type, PropertyBagData* _propertyBag)
{
    //ctor
    type = _type;
    propertyBag = _propertyBag;
}

EntityData::~EntityData()
{
    //dtor
    delete propertyBag;
}

void EntityData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{

}

void EntityData::build(AbstractFactories* _factories)
{
    FactoryParameters params;
    propertyBag->build(params.getTypeTable());
    _factories->useFactory<Entity>(type, &params, nullptr);
}
