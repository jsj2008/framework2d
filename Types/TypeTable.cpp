#include "TypeTable.h"
#include <Log/Log.h>
#include <sstream>
#include <AbstractFactory/EvaluateTypeName.h>

TypeTable::~TypeTable()
{
    /// FIXME for some reason this breaks things
    /*for (auto i = values.begin(); i != values.end(); i++)
    {
        delete i->second;
    }
    values.clear();*/
}
void TypeTable::removeValue(const ValueIndex& name)
{
    assert(values.find(name) != values.end());
    Value* value = values[name];
    delete value;
    values.erase(name);
}

void TypeTable::clear()
{
    for (auto i = values.begin(); i != values.end(); i++)
    {
        g_Log.warning("Value " + i->first + " not used");
        delete i->second;
    }
    values.clear();
}

#include <Types/Vec2f.h>

// FIXME should put this in
/*TypeTable::TypeTable(const TypeTable& rhs)
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
    return out;
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
    return in;
}

TypeTable::TypeTable()
{
    registerType<int>("int");
    registerType<float>("float");
    registerType<std::string>("string");
    registerType<Vec2f>("Vec2f");
    registerType<std::vector<Vec2f>>("Vec2fArray");
    registerType<void*>("userData");
}
template <typename T>
void TypeTable::registerType(const TypeIndex& _name)
{
    delete types[_name];
    types[_name] = new TemplateType<T>();
    auto iter = untypedValues.find(_name);
    typeInfoMap[_name] = demangle<T>();
    realToAliasNameMap[demangle<T>()] = _name;
    name<T>() = _name;
    if (iter != untypedValues.end())
    {
        while (!iter->second.empty())
        {
            UntypedValue* value = iter->second.top();
            iter->second.pop();
            values[value->getValueIndex()] = value->instance<T>();
            delete value;
        }
        untypedValues.erase(iter);
    }
}
TypeTable::Value* TypeTable::addDynamicValue(const TypeIndex& _type, const ValueIndex& _name)
{
    assert(values.find(_name) == values.end());
    Type* type = types[_type];
    if (type == nullptr)
    {
        UntypedValue* ret = new UntypedValue(_type, _name);
        untypedValues[_type].push(ret);
        return ret;
    }
    else
    {
        Value* ret = type->instance();
        values[_name] = ret;
        return ret;
    }
}
void TypeTable::addDynamicValue(const TypeIndex& type, const ValueIndex& _name, std::istream* parseSource)
{
    Value* value = addDynamicValue(type,_name);
    value->set(parseSource);
}
using namespace std;
ostream& operator<< (ostream &out, const TypeTable &table)
{
    unsigned short size = table.values.size();
    out << size << ' ';
    for (auto i = table.values.begin(); i != table.values.end(); i++)
    {
        std::string typeId = i->second->getTypeId();
        std::string type = TypeTable::typeInfoMap[typeId]; /// This is where the problem is I think, wrong type goes out, so it reads in to the untyped table
        out << typeId << ' ';
        std::string name = i->first;
        out << name << ' ';
        i->second->output(&out);
    }
    return out;
}
TypeTable::UntypedValue::UntypedValue(TypeIndex _type, const ValueIndex& _name)
:name(_name),
type(_type)
{

}
TypeTable::UntypedValue::~UntypedValue()
{

}
void TypeTable::UntypedValue::set(std::istream* parseSource)
{
    char stream[124];
    parseSource->getline(stream, 124);
    unparsedValue = stream;
}
#include <iostream>
void TypeTable::UntypedValue::output(std::ostream* parseDestination)
{
    std::cout << "Unknown how to output" << unparsedValue << ' ' << name << std::endl;
    throw -1;
}
std::string TypeTable::UntypedValue::getTypeId()
{
    std::cout << "Unknown type:" << unparsedValue << ' ' << name << std::endl;
    throw -1;
}
TypeTable::Value* TypeTable::UntypedValue::clone()
{
    return nullptr;
}
template <typename T>
TypeTable::Value* TypeTable::UntypedValue::instance()
{
    Value* value = new TemplateValue<T>();
    std::stringstream stream(unparsedValue);
    value->set(&stream);
    return value;
}
std::unordered_map<TypeTable::TypeIndex,TypeTable::Type*> TypeTable::types;
std::unordered_map<std::string,std::string> TypeTable::typeInfoMap;
std::unordered_map<std::string,std::string> TypeTable::realToAliasNameMap;














