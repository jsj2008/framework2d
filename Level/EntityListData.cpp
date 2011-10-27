#include "EntityListData.h"
#include <Level/EntityData.h>

EntityListData::EntityListData(const std::string& _address)
:LoadedData(_address)
{
    //ctor
}

EntityListData::~EntityListData()
{
    //dtor
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        entities[i]->decrement();
    }
}

void EntityListData::virtualSave(XmlDataSaver* _saver)
{
}

void EntityListData::build(AbstractFactories* _factories)
{
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        entities[i]->build(_factories);
    }
}
