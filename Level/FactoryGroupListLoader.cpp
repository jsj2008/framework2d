#include "FactoryGroupListLoader.h"
#include <tinyxml.h>
#include <Level/XmlResourceProvider.h>

FactoryGroupListLoader::FactoryGroupListLoader(XmlResourceProvider* _provider)
{
    //ctor
    provider = _provider;
}

FactoryGroupListLoader::~FactoryGroupListLoader()
{
    //dtor
}

FactoryGroupListData* FactoryGroupListLoader::virtualLoad(const std::string& _listName, FactoryGroupListData* list)
{
    list->init(_listName);
    TiXmlHandle handle = provider->getHandle(_listName);
    TiXmlElement* element = handle.FirstChildElement("FactoryGroup").Element();
    for (; element; element = element->NextSiblingElement("FactoryGroup"))
    {
        list->addFactoryGroup(loadFactoryGroup(_listName, element));
    }
    return list;
}

FactoryGroupData* FactoryGroupListLoader::loadFactoryGroup(const std::string& _listName, TiXmlElement* _element)
{
    const char* name = _element->Attribute("Name");
    FactoryGroupData* data = new FactoryGroupData(name);
    FactoryGroupData::Child* child = data->getRoot();
    loadChild(child, _element);
    /*TiXmlElement* propertyBag = _element->FirstChildElement("PropertyBag");
    PropertyBagData* propertyBagData = new PropertyBagData;
    XmlPropertyBagLoader loader(propertyBag);
    loader.readParameters(propertyBagData);
    std::vector<FactoryData*> childFactories;
    TiXmlElement* childElement = _element->FirstChildElement("FactoryGroup");
    for (; childElement; childElement = childElement->NextSiblingElement("FactoryGroup"))
    {
        childFactories.push_back(loadFactory(_listName, childElement));
    }

    FactoryData* factory = new FactoryData(type, name, product, propertyBagData, childFactories);
    factory->init(_listName + name);
    return factory;*/
}

void FactoryGroupListLoader::loadChild(FactoryGroupData::Child* _child, TiXmlElement* _element)
{
    TiXmlElement* childElement = _element->FirstChildElement("Child");
    for (; childElement; childElement = childElement->NextSiblingElement("Child"))
    {
        const char* name = childElement->Attribute("Name");
        const char* type = childElement->Attribute("Type");
        _child->addChild(new FactoryGroupData::Child(name, type));
        loadChild(_child, childElement);
    }
}






















