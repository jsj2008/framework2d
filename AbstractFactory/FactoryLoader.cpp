#include "FactoryLoader.h"
#include <Log/Log.h>

FactoryLoader::FactoryLoader(const char* filename)
:file(filename)
{
    //ctor
}

FactoryLoader::~FactoryLoader()
{
    //dtor
}
void FactoryLoader::syntaxError(const std::string& type, const std::string& name, const std::string& message)
{
    g_Log.error("In class " + name + " of type " + type + ": " + message);
}

const std::pair<std::string,std::string> FactoryLoader::next()
{
    std::string type;
    std::string name;
    file >> type;
    file >> name;
    std::string token;
    file >> token;
    if (token != "{")
    {
        syntaxError(type, name, "Syntax error, '{' expected, " + token + " read instead");
    }
    while (file.good())
    {
        file >> token;
        std::string variableName;
        file >> variableName;
        if (token == "float")
        {
            float value;
            file >> value;
            addFloat(variableName,value);
        }
        else if (token == "Vec2f")
        {
            float x;
            file >> x;
            float y;
            file >> y;
            addVec2f(variableName,Vec2f(x,y));
        }
        else if (token == "string")
        {
            file >> token;
            addString(variableName,token);
        }
        else if (token == "}")
        {
            break;
        }
        else
        {
            g_Log.error("Syntax error, expected either \"float\", \"Vec2f\" or \"string\"");
        }
    }
    return {type,name};
}

void FactoryLoader::end()
{
    for (auto i = floatValues.begin(); i != floatValues.end(); i++)
    {
        g_Log.warning("Float " + i->first + " defined but not used");
    }
    floatValues.clear();
    for (auto i = stringValues.begin(); i != stringValues.end(); i++)
    {
        g_Log.warning("String " + i->first + " defined but not used");
    }
    stringValues.clear();
}
float FactoryLoader::getFloat(const std::string& name, float normal)
{
    auto value = floatValues.find(name);
    if (value == floatValues.end())
    {
        g_Log.warning("float value \"" + name + "\" not defined, defaulting");
        return normal;
    }
    else
    {
        float ret = value->second;
        floatValues.erase(value);
        return ret;
    }
}
const Vec2f FactoryLoader::getVec2f(const std::string& name, const Vec2f& normal)
{
    auto value = floatValues.find(name + "x");
    if (value == floatValues.end())
    {
        g_Log.warning("Vec2f value \"" + name + "\" not defined exist, defaulting");
        return normal;
    }
    else
    {
        float x = value->second;
        floatValues.erase(value);
        value = floatValues.find(name + "y");
        float y = value->second;
        floatValues.erase(value);
        return Vec2f(x,y);
    }
}
const std::string FactoryLoader::getString(const std::string& name, const std::string& normal)
{
    auto value = stringValues.find(name);
    if (value == stringValues.end())
    {
        g_Log.warning("string value \"" + name + "\" not defined exist, defaulting");
        return normal;
    }
    else
    {
        std::string ret = value->second;
        stringValues.erase(value);
        return ret;
    }
}
void FactoryLoader::addFloat(const std::string& name, float value)
{
    if (floatValues.find(name) != floatValues.end())
    {
        g_Log.warning("Float value \"" + name + "\" already defined, rewriting");
    }
    floatValues[name] = value;
}
void FactoryLoader::addVec2f(const std::string& name, const Vec2f& value)
{
    addFloat(name + "x", value.x);
    addFloat(name + "y", value.y);
}
void FactoryLoader::addString(const std::string& name, const std::string& value)
{
    if (stringValues.find(name) != stringValues.end())
    {
        g_Log.warning("String value \"" + name + "\" already defined, rewriting");
    }
    stringValues[name] = value;
}
