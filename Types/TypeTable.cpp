#include "TypeTable.h"
#include <Log/Log.h>

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
