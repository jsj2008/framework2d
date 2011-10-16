#include "FactoryParameters.h"

FactoryParameters::FactoryParameters(bool logUndefined)
:table(logUndefined)
{
    //ctor
}

FactoryParameters::FactoryParameters(std::initializer_list<std::pair<std::string,Vec2f>> list)
:table(false)
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        add(i->first,i->second);
    }
}

FactoryParameters::~FactoryParameters()
{
    //dtor
}

void FactoryParameters::clear()
{
    table.clear();
}
std::vector<std::string> FactoryParameters::getUndefinedLog()
{
    return table.getUndefinedLog();
}

void FactoryParameters::output(PropertyBagSerializer* _serializer)
{
    table.output(_serializer);
}

using namespace std;
istream& operator>> (istream &in, FactoryParameters &params)
{
    unsigned short size;
    in >> size;
    for (unsigned short i = 0; i < size; i++)
    {
        std::string type;
        in >> type;
        std::string name;
        in >> name;
        params.table.addDynamicValue(type, name, &in);
    }
    return in;
}
void FactoryParameters::addDynamicValue(const TypeTable::TypeIndex& _type, const TypeTable::ValueIndex& _name, const std::string& _value)
{
    table.addDynamicValue(_type, _name, _value);
}
