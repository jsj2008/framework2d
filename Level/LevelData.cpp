#include "LevelData.h"
#include <Level/EntityListData.h>
#include <Level/EventListData.h>
#include <Level/FactoryListData.h>
#include <Level/Level.h>
#include <Level/XmlDataSaver.h>
#include <AbstractFactory/AbstractFactories.h>

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

Level* LevelData::build()
{
    Level* level = new Level(nullptr);
    /// Process event lists
    AbstractFactories* factories = level->getFactories();
    factories->init();
    factories->setWorld(level->getWorld());

    for (unsigned int i = 0; i < factoryLists.size(); i++)
    {
        factoryLists[i]->build(factories);
    }

    for (unsigned int i = 0; i < entityLists.size(); i++)
    {
        entityLists[i]->build(factories);
    }
    return level;
}

void LevelData::virtualSave(XmlDataSaver* _saver)
{
}





















