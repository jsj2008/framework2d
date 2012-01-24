#include "FactoryGroupListData.h"
#include <Level/FactoryGroupData.h>

FactoryGroupListData::FactoryGroupListData()
{
    //ctor
}

FactoryGroupListData::~FactoryGroupListData()
{
    //dtor
}

void FactoryGroupListData::build(AbstractFactories* _factories)
{
    for (unsigned int i = 0; i != factoriesGroups.size(); i++)
    {
        factoriesGroups[i]->build(_factories);
    }
}

void FactoryGroupListData::virtualSave(XmlDataSaver* _saver, const std::string* _address)
{

}
