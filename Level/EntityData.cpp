#include "EntityData.h"
#include <AbstractFactory/FactoryParameters.h>

EntityData::EntityData(const char* _type, FactoryParameters* _params, const std::string& _address)
:LoadedData(_address)
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
