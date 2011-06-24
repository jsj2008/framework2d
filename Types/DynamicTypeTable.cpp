#include "DynamicTypeTable.h"
#include <fstream>
#include <vector>
#include <Types/Vec2f.h>

// FIXME should put this in
/*DynamicTypeTable::DynamicTypeTable(const DynamicTypeTable& rhs)
{
    for (auto i = rhs.values.begin(); i != rhs.values.end(); i++)
    {
        values[i->first] = i->second->clone();
    }
    for (auto i = rhs.typeInfoMap.begin(); i != rhs.typeInfoMap.end(); i++)
    {
        typeInfoMap[i->first] = i->second;
    }
}*/
template <typename T>
std::ostream& operator<< (std::ostream &out, const std::vector<T> &elements)
{
    unsigned short size = elements.size();
    out << size << ' ';
    for (unsigned short i = 0; i < size; i++)
    {
        T element = elements[i];
        out << element << ' ';
    }
}
template <typename T>
std::istream& operator>> (std::istream &in, std::vector<T> &elements)
{
    unsigned short size;
    in >> size;
    elements.reserve(size);
    for (unsigned short i = 0; i < size; i++)
    {
        T element;
        in >> element;
        elements.push_back(element);
    }
}

DynamicTypeTable::DynamicTypeTable()
{
    registerType<int>("int");
    registerType<float>("float");
    registerType<std::string>("string");
    registerType<Vec2f>("Vec2f");
    registerType<std::vector<Vec2f>>("Vec2fArray");
    registerType<void*>("userData");
}
template <typename T>
void DynamicTypeTable::registerType(const TypeIndex& name)
{
    types[name] = new TemplateType<T>;
    const char* typeId = typeid(T).name();
    typeInfoMap[typeId] = name;
}
TypeTable::Value* DynamicTypeTable::addDynamicValue(const TypeIndex& type, const ValueIndex& name)
{
    assert(values.find(name) == values.end());
    assert(types.find(type) != types.end());
    Value* ret = types[type]->instance();
    values[name] = ret;
    return ret;
}
void DynamicTypeTable::addDynamicValue(const TypeIndex& type, const ValueIndex& name, std::istream* parseSource)
{
    Value* value = addDynamicValue(type,name);
    value->set(parseSource);
}
using namespace std;
ostream& operator<< (ostream &out, const DynamicTypeTable &table)
{
    unsigned short size = table.values.size();
    out << size << ' ';
    for (auto i = table.values.begin(); i != table.values.end(); i++)
    {
        std::string typeId = i->second->getTypeId();
        std::string type = table.typeInfoMap[typeId];
        out << type << ' ';
        std::string name = i->first;
        out << name << ' ';
        i->second->output(&out);
    }
    return out;
}

/*istream& operator>> (istream &in, DynamicTypeTable &table)
{
    return in;
}
*/
