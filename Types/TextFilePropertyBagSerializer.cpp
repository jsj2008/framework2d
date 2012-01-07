#include "TextFilePropertyBagSerializer.h"
#include <Types/SerializationTypes.h>

TextFilePropertyBagSerializer::TextFilePropertyBagSerializer(std::ofstream* _file)
:PropertyBagSerializer(new SerializationTypes)
{
    //ctor
    file = _file;
}

TextFilePropertyBagSerializer::~TextFilePropertyBagSerializer()
{
    //dtor
}

void TextFilePropertyBagSerializer::outputValueUntyped(SerializationHelperBase* _value)
{
    _value->textWrite(file);
}

void TextFilePropertyBagSerializer::setNumberOfProperties(unsigned int _size)
{
    *file << _size << ' ';
}

void TextFilePropertyBagSerializer::setVersion(int _version)
{
}

void TextFilePropertyBagSerializer::createProperty(const std::string& _typeIndex, const std::string& _name)
{
    *file << _typeIndex << ' ' << _name << ' ';
}

void TextFilePropertyBagSerializer::startFactory(const std::string& _name)
{
    *file << _name << ' ';
}
void TextFilePropertyBagSerializer::endFactory()
{

}

void TextFilePropertyBagSerializer::endFactories()
{

}
void TextFilePropertyBagSerializer::startArray(unsigned int _size)
{
    *file << _size << ' ';
}
void TextFilePropertyBagSerializer::arrayValue(SerializationHelperBase* _value)
{
    _value->textWrite(file);
}
void TextFilePropertyBagSerializer::endArray()
{
}

void TextFilePropertyBagSerializer::startFactories(unsigned int _size, const std::string& _name)
{
    *file << _size << ' ';
}
