#include "TextFileFactoryLoader.h"

TextFileFactoryLoader::TextFileFactoryLoader(const char* _filename, AbstractFactories* _factories, bool logUndefined)
:FactoryLoader(_factories, logUndefined),
handle(nullptr)
{
    //ctor
    if (_filename == nullptr) return;
    doc = TiXmlDocument(_filename);
    if (!doc.LoadFile())
    {
        return;//g_Log.error(std::string("Failed to load XML file ") + _filename);
    }
    handle = &doc;
    handle = handle.FirstChildElement("FactoryTypes").FirstChild();
}

TextFileFactoryLoader::~TextFileFactoryLoader()
{
    //dtor
}

bool TextFileFactoryLoader::isValid()
{
    return handle.Element()->NextSiblingElement();
}
bool TextFileFactoryLoader::next()
{
    TiXmlElement* element = handle.Element();
    if (element == nullptr) return false;
    type = element->Value();
    name = element->GetText();

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
            mvalues.addDynamicArrayValue(type.substr(0, type.size()-5), name, values.size(), &values[0]);
        }
        else
        {
            mvalues.addDynamicValue(type, name, value);
        }
    }
    handle = element->NextSiblingElement();
    return true;
}
