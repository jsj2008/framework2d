#include "FactoryLoader.h"
#include <Log/Log.h>
using namespace FactoryLoaderPrivate;

FactoryLoader::FactoryLoader(AbstractFactories* _factories, bool logUndefined)
:mvalues(logUndefined)
{
    //ctor
    factories = _factories;
}

FactoryLoader::FactoryLoader(const std::string& _type, const std::string& _name, TypeTable* _table, AbstractFactories* _factories)
:mvalues(*_table)
{
    type = _type;
    name = _name;
    factories = _factories;
}

FactoryLoader::~FactoryLoader()
{
    //dtor
    /*for (auto i = types.begin(); i != types.end(); i++)
    {
        delete i->second;
    }*/
}
void FactoryLoader::syntaxError(const std::string& message)
{
    g_Log.error("In class " + name + " of type " + type + ": " + message);
}
void FactoryLoader::warning(const std::string& message)
{
    g_Log.warning(message);
}

void FactoryLoader::end()
{
    /*for (auto i = values.begin(); i != values.end(); i++)
    {
        g_Log.warning(i->second->name() + " " + i->first + " defined but not used");
        delete i->second;
    } FIXME do this*/
    mvalues.clear();
}
