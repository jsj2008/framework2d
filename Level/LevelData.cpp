#include "LevelData.h"
#include <Level/EntityListData.h>
#include <Level/EventListData.h>
#include <Level/FactoryListData.h>
#include <Level/FactoryGroupListData.h>
#include <Level/Level.h>
#include <Level/XmlDataSaver.h>
#include <Entities/Entity.h>
#include <Physics/PhysicsManager.h>
#include <AbstractFactory/AbstractFactories.h>

LevelData::LevelData()
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
    AbstractFactories* factories = new AbstractFactories;
    Level* level = new Level(new PhysicsManager(factories->getCollisionDatabase()), factories);
    /// Process event lists
    factories->init();
    factories->setWorld(level->getWorld());

    for (unsigned int i = 0; i < factoryLists.size(); i++)
    {
        factoryLists[i]->build(factories);
    }
    for (unsigned int i = 0; i < factoryGroupLists.size(); i++)
    {
        factoryGroupLists[i]->build(factories);
    }

    for (unsigned int i = 0; i < entityLists.size(); i++)
    {
        entityLists[i]->build(factories, level);
    }

    /*{
        auto waterFactory = factories->getFactory<Entity>("WaterParticle");
        FactoryParameters params;
        for (int i = -10; i != 9; i++)
        {
            for (int ii = -20; ii != 10; ii++)
            {
	      params.add<Vec2f>("position", {float(i),float(ii)});
                waterFactory->use(&params, level);
            }
        }
    }*/
    return level;
}

void LevelData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{
    TiXmlHandle element = _saver->createElement(address, "Level");
    for (unsigned int i = 0; i < eventLists.size(); i++)
    {
        eventLists[i]->save(_saver, &address);
    }
    for (unsigned int i = 0; i < entityLists.size(); i++)
    {
        entityLists[i]->save(_saver, &address);
    }
    for (unsigned int i = 0; i < factoryLists.size(); i++)
    {
        factoryLists[i]->save(_saver, &address);
    }
}





















