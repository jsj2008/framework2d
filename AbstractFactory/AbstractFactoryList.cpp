#include "AbstractFactoryList.h"
#include <iostream>

AbstractFactoryListBase::AbstractFactoryListBase(std::unordered_map<std::string, AbstractFactoryListBase*>* factoryLists, const std::string& _productName)
{
    (*factoryLists)[_productName] = this;
}
AbstractFactoryListBase::~AbstractFactoryListBase()
{
}

void privatePrint(std::ostream* stream, const std::string& factoryType, const std::string& factoryInstance, const std::string& productName, const std::string& realProductName)
{
    if (productName != realProductName)
    {
        *stream << productName << "* " << factoryType << ' ' << factoryInstance << ", renamed from " << realProductName << std::endl;
    }
    else
    {
        *stream << productName << "* " << factoryType << ' ' << factoryInstance << ';' << std::endl;
    }
}
