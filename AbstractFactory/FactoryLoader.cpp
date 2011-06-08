#include "FactoryLoader.h"
#include <Log/Log.h>
using namespace FactoryLoaderPrivate;

FactoryLoader::FactoryLoader(const char* filename)
:file(filename)
{
    //ctor
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

bool FactoryLoader::next()
{
    file >> type;
    file >> name;
    std::string token;
    file >> token;
    if (token[0] != '{')
    {
        if (!file.good()) return false;
        syntaxError("Syntax error, '{' expected, " + token + " read instead");
    }
    while (file.good())
    {
        file >> token;
        if (token[0] == '}')
        {
            return true;
        }
        else
        {
            std::string variableName;
            file >> variableName;
            /*if (types.find(token) == types.end())
            {
                syntaxError("Type " + token + " not defined");
            }
            if (values.find(variableName) != values.end())
            {
                warning("Variable " + variableName + " already defined, redefining");
            }
            values[variableName] = types[token]->instance(&file);*/
            mvalues.addDynamicValue(token,variableName,&file);
        }
    }
    return false;
}

void FactoryLoader::end()
{
    /*for (auto i = values.begin(); i != values.end(); i++)
    {
        g_Log.warning(i->second->name() + " " + i->first + " defined but not used");
        delete i->second;
    }
    values.clear();*/
}

/*template <typename T>
void FactoryLoader::addType(const std::string& name)
{
    assert(types.find(name) == types.end());
    types[name] = new TemplateType<T>;
}
*/
