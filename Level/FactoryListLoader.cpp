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
        const char* type = element->Attribute("Type");
        const char* name = element->Attribute("Name");
        const char* product = element->Attribute("Product");
        TiXmlElement* propertyBag = element->FirstChildElement("PropertyBag");
        PropertyBagData* propertyBagData = new PropertyBagData;
        XmlPropertyBagLoader loader(propertyBag);
        loader.readParameters(propertyBagData);

        FactoryData* factory = new FactoryData(type, name, product, propertyBagData);
        factory->init(_listName + name);
        list->addFactory(factory);
    }
    return list;
}
