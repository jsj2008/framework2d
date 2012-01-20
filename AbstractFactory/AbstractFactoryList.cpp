#include "AbstractFactoryList.h"

AbstractFactoryListBase::~AbstractFactoryListBase()
{
}

void AbstractFactoryListBase::registerActions(GameObjectType* _type)
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
