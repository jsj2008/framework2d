#include "CppFactoryLoader.h"
#include <Types/XmlFilePropertyBagSerializer.h>

CppFactoryLoader::CppFactoryLoader(AbstractFactories* _factories)
:FactoryLoader(_factories)
{
    //ctor
}

CppFactoryLoader::~CppFactoryLoader()
{
    //dtor
}

CppFactoryLoader::CppFactoryLoader(const std::string& _type, const std::string& _name, TypeTable* _table, AbstractFactories* _factories)
:FactoryLoader(_type, _name, _table, _factories)
{

}
bool CppFactoryLoader::isValid()
{
    return true;
}
bool CppFactoryLoader::next()
{
    return false;
}

void CppFactoryLoader::output()
{
    XmlFilePropertyBagSerializer file("Resources/EntityFactories.xml", true);
    file.startFactoryDefinitions();
    file.startFactoryDefinition(type, name);
    mvalues.output(&file);
    file.endFactoryDefinition();
    file.endFactoryDefinitions();
    /**stream << type << ' ' << name << std::endl << '{' << std::endl;
    mvalues.output(stream);
    *stream << std::endl << '}' << std::endl;*/
}

void CppFactoryLoader::addDynamicValue(const std::string& _type, const std::string& _name, const std::string& _value)
{
    mvalues.addDynamicValue(_type, _name, _value);
}
