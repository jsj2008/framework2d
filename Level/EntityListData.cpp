#include "EntityListData.h"
#include <Level/EntityData.h>

EntityListData::EntityListData()
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

void EntityListData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{
}

void EntityListData::build(AbstractFactories* _factories, Level* _level)
{
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        entities[i]->build(_factories, _level);
    }
}
