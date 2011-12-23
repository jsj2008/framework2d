#include "LevelLoader.h"
#include <Level/LevelData.h>
#include <Level/XmlResourceProvider.h>
#include <Log/Log.h>

LevelLoader::LevelLoader(XmlResourceProvider* _provider)
:eventListLoader(_provider),
factoryListLoader(_provider),
entitylistLoader(_provider)
{
    //ctor
    provider = _provider;
}

LevelLoader::~LevelLoader()
{
    //dtor
}

#define LIST_FUNCTIONS 3
void LevelLoader::virtualLoad(const std::string& _levelName, LevelData* _data)
{
    static void (LevelLoader::*addListFunctions[LIST_FUNCTIONS])(LevelData* _data, const std::string& _address) =
    {
        &LevelLoader::addEventList,
        &LevelLoader::addEntityList,
        &LevelLoader::addFactoryList,
    };
    static const char* listFunctionNames[LIST_FUNCTIONS] =
    {
        "EventList",
        "EntityList",
        "FactoryList",
    };

    _data->init(_levelName);
    TiXmlHandle handle = provider->getHandle(_levelName);
    for (unsigned int i = 0; i < LIST_FUNCTIONS; i++)
    {
        std::vector<std::string> names = getChildrenOfType(listFunctionNames[i], handle.Element(), _levelName);
        for (unsigned int ii = 0; ii < names.size(); ii++)
        {
            (this->*addListFunctions[i])(_data, names[ii]);
        }
    }
}

std::vector<std::string> LevelLoader::getChildrenOfType(const std::string& _type, TiXmlElement* _root, const std::string& _rootAddress)
{
    std::vector<std::string> ret;
    {
        TiXmlElement* element = _root->FirstChildElement(_type);
        for (; element; element = element->NextSiblingElement(_type))
        {
            const char* name = element->Attribute("Name");
            if (name == nullptr)
                g_Log.error("Name not specified");
            ret.push_back(_rootAddress + '/' + name);
        }
    }
    {
        TiXmlElement* element = _root->FirstChildElement(_type + "Ref");
        for (; element; element = element->NextSiblingElement(_type + "Ref"))
        {
            const char* text = element->GetText();
            if (text == nullptr)
                g_Log.error("No text element");
            ret.push_back(text);
        }
    }
    return ret;
}

void LevelLoader::addEventList(LevelData* _data, const std::string& _address)
{
    EventListData* entityList = eventListLoader.load(_address);
    _data->addEventList(entityList);
}
void LevelLoader::addEntityList(LevelData* _data, const std::string& _address)
{
    EntityListData* entityList = entitylistLoader.load(_address);
    _data->addEntityList(entityList);
}
void LevelLoader::addFactoryList(LevelData* _data, const std::string& _address)
{
    FactoryListData* factoryList = factoryListLoader.load(_address);
    _data->addFactoryList(factoryList);
}
















