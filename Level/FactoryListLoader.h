#ifndef FACTORYLISTLOADER_H
#define FACTORYLISTLOADER_H

#include <Level/DataLoader.h>
#include <Level/FactoryListData.h>
#include <string>
class FactoryListData;
class XmlResourceProvider;
class TiXmlElement;

class FactoryListLoader : public DataLoader<FactoryListLoader, FactoryListData>
{
    public:
        FactoryListLoader(XmlResourceProvider* _provider);
        virtual ~FactoryListLoader();
        FactoryListData* virtualLoad(const std::string& _listName, FactoryListData* list);
    protected:
    private:
        XmlResourceProvider* provider;
        FactoryData* loadFactory(const std::string& _listName, TiXmlElement* _element);
};

#endif // FACTORYLISTLOADER_H
