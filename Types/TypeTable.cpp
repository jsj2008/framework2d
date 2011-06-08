#include "TypeTable.h"

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
        delete i->second;
    }
    values.clear();
}
