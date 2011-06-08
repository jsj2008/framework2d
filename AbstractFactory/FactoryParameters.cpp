#include "FactoryParameters.h"

FactoryParameters::FactoryParameters()
{
    //ctor
}

FactoryParameters::FactoryParameters(std::initializer_list<std::pair<std::string,Vec2f>> list)
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
ostream& operator<< (ostream &out, const FactoryParameters & params)
{
    out << params.table;
    out << '\n';
    return out;
}
