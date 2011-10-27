#include "FactoryListData.h"
#include <Level/FactoryData.h>

FactoryListData::FactoryListData(const std::string& _address)
:LoadedData(_address)
{
    //ctor
}

FactoryListData::~FactoryListData()
{
    //dtor
    for (unsigned int i = 0; i < factories.size(); i++)
    {
        factories[i]->decrement();
    }
}

void FactoryListData::build(AbstractFactories* _factories)
{
    for (unsigned int i = 0; i != factories.size(); i++)
    {
        factories[i]->build(_factories);
    }
}

void FactoryListData::virtualSave(XmlDataSaver* _saver)
{

}
