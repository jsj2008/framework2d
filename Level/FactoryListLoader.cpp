#include "FactoryListLoader.h"
#include <Level/XmlResourceProvider.h>
#include <Level/FactoryListData.h>
#include <Level/FactoryData.h>
#include <AbstractFactory/FactoryParameters.h>
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

FactoryListData* FactoryListLoader::virtualLoad(const std::string& _listName)
{
    FactoryListData* list = new FactoryListData(_listName);
    TiXmlHandle handle = provider->getHandle(_listName);
    TiXmlElement* element = handle.FirstChildElement("Factory").Element();
    for (; element; element = element->NextSiblingElement("Factory"))
    {
        const char* type = element->Attribute("Type");
        const char* name = element->Attribute("Name");
        TiXmlElement* propertyBag = element->FirstChildElement("PropertyBag");
        FactoryParameters* params = new FactoryParameters;
        XmlPropertyBagLoader loader(propertyBag);
        loader.readParameters(params);

        FactoryData* factory = new FactoryData(type, name, params, _listName + name);
        list->addFactory(factory);
    }
    return list;
}
