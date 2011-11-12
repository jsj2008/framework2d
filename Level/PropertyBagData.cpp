#include "PropertyBagData.h"
#include <AbstractFactory/FactoryParameters.h>

PropertyBagData::PropertyBagData()
{
    //ctor
}

PropertyBagData::~PropertyBagData()
{
    //dtor
}

void PropertyBagData::build(TypeTable* _params)
{
    for (auto iter = properties.begin(); iter != properties.end(); iter++)
    {
        (*iter)->outputProperty(_params);
    }
}

void PropertyBagData::addDynamicValue(const std::string& _type, const std::string& _name, const std::string& _value)
{
    properties.push_back(new StandardProperty(_type, _name, _value));
}

void PropertyBagData::addDynamicArrayValue(const std::string& _type, const std::string& _name, int _size, const std::string* _values)
{
    properties.push_back(new ArrayProperty(_type, _name, _size, _values));
}

PropertyBagData::PropertyData::PropertyData(const std::string& _name)
{
    name = _name;
}

PropertyBagData::StandardProperty::StandardProperty(const std::string& _name, const std::string& _type, const std::string& _value)
:PropertyData(_name)
{
    type = _type;
    value = _value;
}

PropertyBagData::ArrayProperty::ArrayProperty(const std::string& _type, const std::string& _name, int _size, const std::string* _values)
:PropertyData(_name)
{
    type = _type;
    values.resize(_size);
    for (int i = 0; i < _size; i++)
    {
        values[i] = _values[i];
    }
}

void PropertyBagData::StandardProperty::outputProperty(TypeTable* _table)
{
    _table->addDynamicValue(type, name, value);
}
void PropertyBagData::ArrayProperty::outputProperty(TypeTable* _table)
{
    _table->addDynamicArrayValue(type, name, values.size(), &values[0]);
}

void PropertyBagData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{
    g_Log.error("PropertyBagData::virtualSave not defined");
}






