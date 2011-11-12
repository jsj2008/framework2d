#include "XmlPropertyBagLoader.h"
#include <Log/Log.h>
#include <AbstractFactory/FactoryParameters.h>
#include <Level/PropertyBagData.h>

XmlPropertyBagLoader::XmlPropertyBagLoader(const char* _filename)
:doc(_filename),
handle(&doc)
{
    //ctor
    if (!doc.LoadFile())
    {
        g_Log.error(std::string("Failed to load XML file ") + _filename);
    }
}
XmlPropertyBagLoader::XmlPropertyBagLoader(TiXmlElement* _propertyBag)
:handle(nullptr)
{
    //ctor
    element = _propertyBag;
}

XmlPropertyBagLoader::~XmlPropertyBagLoader()
{
    //dtor
}

int XmlPropertyBagLoader::getVersion()
{
    TiXmlElement* element = doc.FirstChildElement("Factories");
    int version = -1;
    element->QueryIntAttribute("Version", &version);
    return version;
}
bool XmlPropertyBagLoader::startFactories()
{
    handle = handle.FirstChildElement("Factories").FirstChild();
    element = handle.Element();
    return element != nullptr;
}
bool XmlPropertyBagLoader::next()
{
    element = element->NextSiblingElement();
    return element != nullptr;
}
const char* XmlPropertyBagLoader::getFactoryName()
{
    return element->Value();
}

void XmlPropertyBagLoader::readParameters(PropertyBagData* _propertyBag)
{
    for (TiXmlElement* property = element->FirstChildElement(); property != nullptr; property = property->NextSiblingElement())
    {
        std::string type = property->Attribute("Type");
        const char* name = property->Attribute("Name");
        if (std::string(property->Value()) == "Array")
        {
            std::vector<std::string> values;
            for (TiXmlElement* arrayValue = property->FirstChildElement("Member"); arrayValue != nullptr; arrayValue = arrayValue->NextSiblingElement("Member"))
            {
                values.push_back(arrayValue->Attribute("Value"));
            }
            _propertyBag->addDynamicArrayValue(type, name, values.size(), &values[0]);
        }
        else
        {
            const char* value = property->Attribute("Value");
            _propertyBag->addDynamicValue(type, name, value);
        }
    }
}

void XmlPropertyBagLoader::readParameters(FactoryParameters* _params)
{
    for (TiXmlElement* property = element->FirstChildElement(); property != nullptr; property = property->NextSiblingElement())
    {
        std::string type = property->Attribute("Type");
        const char* name = property->Attribute("Name");
        if (std::string(property->Value()) == "Array")
        {
            std::vector<std::string> values;
            for (TiXmlElement* arrayValue = property->FirstChildElement("Member"); arrayValue != nullptr; arrayValue = arrayValue->NextSiblingElement("Member"))
            {
                values.push_back(arrayValue->Attribute("Value"));
            }
            TypeTable* table = _params->getTypeTable();
            table->addDynamicArrayValue(type, name, values.size(), &values[0]);
        }
        else
        {
            const char* value = property->Attribute("Value");
            _params->addDynamicValue(type, name, value);
        }
    }
}
void XmlPropertyBagLoader::endFactories()
{

}
