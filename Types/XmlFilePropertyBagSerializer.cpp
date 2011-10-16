#include "XmlFilePropertyBagSerializer.h"

XmlFilePropertyBagSerializer::XmlFilePropertyBagSerializer(const char* _filename)
:PropertyBagSerializer(new SerializationTypes)
{
    //ctor
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    output.LinkEndChild(decl);
}

XmlFilePropertyBagSerializer::~XmlFilePropertyBagSerializer()
{
    //dtor
	output.SaveFile( "Level.xml" );
}

/*void XmlFilePropertyBagSerializer::outputString(const std::string& _str)
{
    TiXmlElement* element = new TiXmlElement(_str);
    elements.top()->LinkEndChild(element);

    elements.push(element);
}*/
void XmlFilePropertyBagSerializer::outputValueUntyped(SerializationHelperBase* _value)
{
    std::stringstream stream;
    _value->textWrite(&stream);
    elements.top()->SetAttribute("Value", stream.str());

    elements.pop();
}
void XmlFilePropertyBagSerializer::setNumberOfProperties(unsigned int _size)
{
}

void XmlFilePropertyBagSerializer::createProperty(const std::string& _typeIndex, const std::string& _name)
{
    TiXmlElement* element = new TiXmlElement(_typeIndex);
    element->SetAttribute("Name", _name);
    elements.top()->LinkEndChild(element);

    elements.push(element);
}

void XmlFilePropertyBagSerializer::setVersion(int _version)
{
    elements.top()->SetAttribute("Version", _version);
}
void XmlFilePropertyBagSerializer::startFactory(const std::string& _name)
{
    TiXmlElement* element = new TiXmlElement(_name);
    elements.top()->LinkEndChild(element);

    elements.push(element);
}
void XmlFilePropertyBagSerializer::endFactory()
{
    elements.pop();
}
void XmlFilePropertyBagSerializer::endFactories()
{
    elements.pop();
}
void XmlFilePropertyBagSerializer::startArray(unsigned int _size)
{
    elements.top()->SetAttribute("Value", "Array");
}
void XmlFilePropertyBagSerializer::arrayValue(SerializationHelperBase* _value)
{
    std::stringstream stream;
    _value->textWrite(&stream);
    TiXmlElement* element = new TiXmlElement("Member");
    element->SetAttribute("Value", stream.str());
    elements.top()->LinkEndChild(element);
}
void XmlFilePropertyBagSerializer::endArray()
{
    elements.pop();
}


void XmlFilePropertyBagSerializer::startFactories(unsigned int _size, const std::string& _name)
{
    elements.push(new TiXmlElement("Factories"));
    output.LinkEndChild(elements.top());
}
