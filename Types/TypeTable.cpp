#include "TypeTable.h"
#include <Log/Log.h>
#include <Types/Vec2i.h>
#include <sstream>
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
    auto iter = values.find(name);
    assert(iter != values.end());
    delete iter->second;
    values.erase(iter);
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

TypeTable::TypeTable(bool _logUndefined)
{
    logUndefined = _logUndefined;
    //registerType<int>("int");
    //registerType<float>("float");
    registerType<std::string>("string");
    registerType<Vec2f>("Vec2f");
    registerType<std::vector<Vec2f>>("Vec2fArray");
    registerType<std::vector<Vec2i>>("Vec2iArray");
    registerType<void*>("userData");
}
template <typename T>
void TypeTable::registerType(const TypeIndex& _name)
{
    //std::string oldName = EvaluateTypeName<T>();
    if (name<T>() != _name)
    {
        TemplateType<T>* oldType = static_cast<TemplateType<T>*>(types[name<T>()]);
        if (oldType != nullptr)
        {
            assert(dynamic_cast<TemplateType<T>*>(types[name<T>()]));
            types[_name] = oldType; /// Its still in the old location too
        }
        else
        {
            types[_name] = new TemplateType<T>();
        }
        name<T>() = _name;
    }
    auto iter = untypedValues.find(_name);
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


std::vector<std::string> TypeTable::getUndefinedLog()
{
    assert(logUndefined);
    std::vector<std::string> ret;
    for (auto i = undefinedLog.begin(); i != undefinedLog.end(); i++)
    {
        ret.push_back(i->first);
    }
    return ret;
}
/*template <typename T>
TypeTable::AutomaticRegister<T>::AutomaticRegister()
{

}*/
std::unordered_map<TypeTable::TypeIndex,TypeTable::Type*> TypeTable::types;


//#include <AbstractFactory/EvaluateTypeName.h>







