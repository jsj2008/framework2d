#include "XmlPropertyBagLoader.h"
#include <Log/Log.h>
#include <AbstractFactory/FactoryParameters.h>

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
void XmlPropertyBagLoader::readParameters(FactoryParameters* _params)
{
    for (TiXmlElement* property = element->FirstChildElement(); property != nullptr; property = property->NextSiblingElement())
    {
        std::string type = property->Value();
        const char* name = property->Attribute("Name");
        const char* value = property->Attribute("Value");
        if (type.size() > 5 && type.substr(type.size()-5, type.size()) == "Array")
        {
            std::vector<std::string> values;
            for (TiXmlElement* arrayValue = property->FirstChildElement("Member"); arrayValue != nullptr; arrayValue = arrayValue->NextSiblingElement("Member"))
            {
                values.push_back(arrayValue->Attribute("Value"));
            }
            TypeTable* table = _params->getTypeTable();
            table->addDynamicArrayValue(type.substr(0, type.size()-5), name, values.size(), &values[0]);
        }
        else
        {
            _params->addDynamicValue(type, name, value);
        }
    }
}
void XmlPropertyBagLoader::endFactories()
{

}
