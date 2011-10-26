#include "EntityListLoader.h"
#include <Level/EntityListData.h>
#include <Level/XmlResourceProvider.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Types/XmlPropertyBagLoader.h>
#include <Level/EntityData.h>

EntityListLoader::EntityListLoader(XmlResourceProvider* _provider)
{
    //ctor
    provider = _provider;
}

EntityListLoader::~EntityListLoader()
{
    //dtor
}

EntityListData* EntityListLoader::virtualLoad(const std::string& _listName)
{
    EntityListData* list = new EntityListData(_listName);
    TiXmlHandle handle = provider->getHandle(_listName);

    TiXmlElement* element = handle.FirstChildElement("Entity").Element();
    for (; element; element = element->NextSiblingElement("Entity"))
    {
        const char* type = element->Attribute("Type");
        TiXmlElement* propertyBag = element->FirstChildElement("PropertyBag");
        FactoryParameters* params = new FactoryParameters;
        XmlPropertyBagLoader loader(propertyBag);
        loader.readParameters(params);

        EntityData* entity = new EntityData(type, params, _listName);
        list->addEntity(entity);
    }
    return list;
}
