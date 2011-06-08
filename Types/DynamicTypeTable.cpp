#include "DynamicTypeTable.h"
#include <fstream>
#include <Types/Vec2f.h>

DynamicTypeTable::DynamicTypeTable()
{
    registerType<int>("int");
    registerType<float>("float");
    registerType<std::string>("string");
    registerType<Vec2f>("Vec2f");
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
