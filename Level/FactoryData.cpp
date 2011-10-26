#include "FactoryData.h"

FactoryData::FactoryData(const char* _type, const char* _name, FactoryParameters* _params, const std::string& _address)
:LoadedData(_address)
{
    //ctor
    type = _type;
    name = _name;
    params = _params;
}

FactoryData::~FactoryData()
{
    //dtor
    delete params;
}
