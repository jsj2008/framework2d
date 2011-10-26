#include "LoadedData.h"

LoadedData::LoadedData(const std::string& _address)
{
    //ctor
    address = _address;
    referenceCount = 1;
}

LoadedData::~LoadedData()
{
    //dtor
}

void LoadedData::decrement()
{
    referenceCount--;
    if (referenceCount == 0)
    {
        delete this;
    }
}
