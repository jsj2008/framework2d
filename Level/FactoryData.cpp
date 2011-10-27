#include "FactoryData.h"
#include <AbstractFactory/FactoryParameters.h>
#include <Entities/Entity.h>

FactoryData::FactoryData(const char* _type, const char* _name, FactoryParameters* _params, const std::string& _address)
:LoadedData(_address),
loader(_type, _name, _params->getTypeTable(), nullptr)
{
    //ctor
    delete _params;
}

FactoryData::~FactoryData()
{
    //dtor
}

void FactoryData::build(AbstractFactories* _factories)
{
    loader.setFactories(_factories);
    _factories->addFactory<Entity>(&loader);
}

void FactoryData::virtualSave(XmlDataSaver* _saver)
{

}
