#include "UndoResources.h"

UndoResources::UndoResources()
{
    //ctor
}

UndoResources::~UndoResources()
{
    //dtor
}

UndoResources& UndoResources::global()
{
    static UndoResources resources;
    return resources;
}
UndoResource UndoResources::createEntry()
{
    unsigned int ret = entries.size();
    entries.push_back(nullptr);
    return ret;
}
void UndoResources::setValue(UndoResource _resourceId, void* _value)
{
    void* oldValue = entries[_resourceId];
    entries[_resourceId] = _value;
    if (oldValue != nullptr)
    {
        values.erase(oldValue);
    }
    if (_value != nullptr)
    {
        values[_value] = _resourceId;
    }
}
void* UndoResources::getValue(UndoResource _resourceId)
{
    return entries[_resourceId];
}
UndoResource UndoResources::getEntry(void* _value)
{
    auto ret = values.find(_value);
    if (ret != values.end())
    {
        return ret->second;
    }
    throw -1;
}
UndoResource UndoResources::getEntrySafely(void* _value)
{
    try
    {
        return getEntry(_value);
    }
    catch (int i)
    {
        UndoResource newResource = createEntry();
        setValue(newResource, _value);
        return newResource;
    }
}
