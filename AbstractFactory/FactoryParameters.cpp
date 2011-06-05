#include "FactoryParameters.h"

FactoryParameters::FactoryParameters()
{
    //ctor
}
/*FactoryParameters::FactoryParameters(std::initializer_list<std::pair<std::string,float>> list)
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        parameters.insert(*i);
    }
}*/
FactoryParameters::FactoryParameters(std::initializer_list<std::pair<std::string,Vec2f>> list)
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        parameters.insert({i->first+"x",i->second.x});
        parameters.insert({i->first+"y",i->second.y});
    }
}

FactoryParameters::~FactoryParameters()
{
    //dtor
}

/*float FactoryParameters::getFloat(const std::string& name)
{
    return parameters[name];
}*/

const Vec2f FactoryParameters::getVec2f(const std::string& name)
{
    return Vec2f(parameters[name+"x"],parameters[name+"y"]);
}
