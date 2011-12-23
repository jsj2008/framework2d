#include "LoadedData.h"

LoadedData::LoadedData()
{
    //ctor
    referenceCount = 1;
}

LoadedData::~LoadedData()
{
    //dtor
}

void LoadedData::init(const std::string& _address)
{
    address = _address;
}

void LoadedData::decrement()
{
    referenceCount--;
    if (referenceCount == 0)
    {
        delete this;
    }
}

void LoadedData::save(XmlDataSaver* _saver, const std::string* _address)
{
    virtualSave(_saver, _address);
}
