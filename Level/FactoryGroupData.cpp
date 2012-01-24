#include "FactoryGroupData.h"

FactoryGroupData::FactoryGroupData(const char* _name)
:name(_name),
root(_name, "")
{
    //ctor
}

FactoryGroupData::~FactoryGroupData()
{
    //dtor
}

GameObjectBase* FactoryGroupData::build(AbstractFactories* _factories)
{
    throw -1;
}

void FactoryGroupData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{
}

FactoryGroupData::Child::Child(const char* _name, const char* _type)
{
    name = _name;
    type = _type;
}
FactoryGroupData::Child::~Child()
{
    for (auto iter = children.begin(); iter != children.end(); iter++)
    {
        delete *iter;
    }
}
void FactoryGroupData::Child::addChild(Child* _child)
{
    children.push_back(_child);
}
