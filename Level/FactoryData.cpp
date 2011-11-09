#include "FactoryData.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Entity.h>

FactoryData::FactoryData(const char* _type, const char* _name, const char* _product, FactoryParameters* _params)
:loader(_type, _name, _params->getTypeTable(), nullptr)
{
    //ctor
    delete _params;
    product = _product;
}

FactoryData::~FactoryData()
{
    //dtor
}

void FactoryData::build(AbstractFactories* _factories)
{
    loader.setFactories(_factories);
    _factories->addFactory(product, &loader);
}

void FactoryData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{

}
