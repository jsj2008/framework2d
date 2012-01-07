#include "EntityListLoader.h"
#include <Level/EntityListData.h>
#include <Level/XmlResourceProvider.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Types/XmlPropertyBagLoader.h>
#include <Level/EntityData.h>
#include <Level/PropertyBagData.h>

EntityListLoader::EntityListLoader(XmlResourceProvider* _provider)
{
    //ctor
    provider = _provider;
}

EntityListLoader::~EntityListLoader()
{
    //dtor
}

void EntityListLoader::virtualLoad(const std::string& _listName, EntityListData* _list)
{
    _list->init(_listName);
    TiXmlHandle handle = provider->getHandle(_listName);

    TiXmlElement* element = handle.FirstChildElement("Entity").Element();
    for (; element; element = element->NextSiblingElement("Entity"))
    {
        const char* type = element->Attribute("Type");
        TiXmlElement* propertyBagElement = element->FirstChildElement("PropertyBag");
        PropertyBagData* propertyBag = new PropertyBagData;
        XmlPropertyBagLoader loader(propertyBagElement);
        loader.readParameters(propertyBag);

        EntityData* entity = new EntityData(type, propertyBag);
        entity->init(_listName);
        _list->addEntity(entity);
    }
}
