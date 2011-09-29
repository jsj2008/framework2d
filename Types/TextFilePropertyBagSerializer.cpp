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

void TextFilePropertyBagSerializer::outputValue(SerializationHelperBase* _value)
{
    _value->textWrite(file);
}

void TextFilePropertyBagSerializer::outputString(const std::string& _str)
{
    *file << _str << ' ';
}

void TextFilePropertyBagSerializer::startArray(unsigned int _size)
{
    *file << _size << ' ';
}
