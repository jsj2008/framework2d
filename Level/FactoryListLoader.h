#ifndef FACTORYLISTLOADER_H
#define FACTORYLISTLOADER_H

#include <Level/DataLoader.h>
#include <Level/FactoryListData.h>
#include <string>
class FactoryListData;
class XmlResourceProvider;

class FactoryListLoader : public DataLoader<FactoryListLoader, FactoryListData>
{
    public:
        FactoryListLoader(XmlResourceProvider* _provider);
        virtual ~FactoryListLoader();
        FactoryListData* virtualLoad(const std::string& _listName);
    protected:
    private:
        XmlResourceProvider* provider;
};

#endif // FACTORYLISTLOADER_H
