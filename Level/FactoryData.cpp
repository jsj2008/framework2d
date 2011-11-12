#include "FactoryData.h"
#include <Entities/Entity.h>
#include <AbstractFactory/FactoryLoaders/CppFactoryLoader.h>
#include <Level/PropertyBagData.h>

FactoryData::FactoryData(const char* _type, const char* _name, const char* _product, PropertyBagData* _propertyBag)
:loader(nullptr)
{
    //ctor
    product = _product;
    propertyBag = _propertyBag;
    loader.setType(_type);
    loader.setName(_name);
}

FactoryData::~FactoryData()
{
    //dtor
}

GameObjectBase* FactoryData::build(AbstractFactories* _factories)
{
    loader.setFactories(_factories);
    propertyBag->build(loader.getTypeTable());
    return _factories->addFactory(product, &loader);
}

void FactoryData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{

}
