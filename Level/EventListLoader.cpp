#include "EventListLoader.h"
#include <Level/XmlResourceProvider.h>
#include <Level/EventListData.h>

EventListLoader::EventListLoader(XmlResourceProvider* _provider)
{
    //ctor
    provider = _provider;
}

EventListLoader::~EventListLoader()
{
    //dtor
}

EventListData* EventListLoader::virtualLoad(const std::string& _listName)
{
    EventListData* list = new EventListData(_listName);
    TiXmlHandle handle = provider->getHandle(_listName);
    return list;
}
