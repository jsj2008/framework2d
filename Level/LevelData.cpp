#include "LevelData.h"
#include <Level/EntityListData.h>
#include <Level/EventListData.h>
#include <Level/FactoryListData.h>

LevelData::LevelData(const std::string& _address)
:LoadedData(_address)
{
    //ctor
}

LevelData::~LevelData()
{
    //dtor
    for (unsigned int i = 0; i < eventLists.size(); i++)
    {
        eventLists[i]->decrement();
    }
    for (unsigned int i = 0; i < entityLists.size(); i++)
    {
        entityLists[i]->decrement();
    }
    for (unsigned int i = 0; i < factoryLists.size(); i++)
    {
        factoryLists[i]->decrement();
    }
}

void LevelData::removeEntityList(unsigned int _index)
{
    delete entityLists[_index];
    entityLists.erase(entityLists.begin()+_index);
}

