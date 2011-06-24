#include "AbstractFactoryList.h"

AbstractFactoryListBase::AbstractFactoryListBase(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists, const std::string& productName)
{
    (*factoryLists)[productName] = this;
}
AbstractFactoryListBase::~AbstractFactoryListBase()
{
}
