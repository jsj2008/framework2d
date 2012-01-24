#include "FactoryListLoader.h"
#include <Level/XmlResourceProvider.h>
#include <Level/FactoryListData.h>
#include <Level/FactoryData.h>
#include <Level/PropertyBagData.h>
#include <Types/XmlPropertyBagLoader.h>

FactoryListLoader::FactoryListLoader(XmlResourceProvider* _provider)
{
    //ctor
    provider = _provider;
}

FactoryListLoader::~FactoryListLoader()
{
    //dtor
}

FactoryListData* FactoryListLoader::virtualLoad(const std::string& _listName, FactoryListData* list)
{
    list->init(_listName);
    TiXmlHandle handle = provider->getHandle(_listName);
    TiXmlElement* element = handle.FirstChildElement("Factory").Element();
    for (; element; element = element->NextSiblingElement("Factory"))
    {
        list->addFactory(loadFactory(_listName, element));
    }
    return list;
}

FactoryData* FactoryListLoader::loadFactory(const std::string& _listName, TiXmlElement* _element)
{
    const char* type = _element->Attribute("Type");
    const char* name = _element->Attribute("Name");
    const char* product = _element->Attribute("Product");
    TiXmlElement* propertyBag = _element->FirstChildElement("PropertyBag");
    PropertyBagData* propertyBagData = new PropertyBagData;
    XmlPropertyBagLoader loader(propertyBag);
    loader.readParameters(propertyBagData);
    std::vector<FactoryData*> childFactories;
    TiXmlElement* childElement = _element->FirstChildElement("Factory");
    for (; childElement; childElement = childElement->NextSiblingElement("Factory"))
    {
        childFactories.push_back(loadFactory(_listName, childElement));
    }

    FactoryData* factory = new FactoryData(type, name, product, propertyBagData, childFactories);
    factory->init(_listName + name);
    return factory;
}
