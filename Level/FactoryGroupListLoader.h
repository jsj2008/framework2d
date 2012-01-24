#ifndef FACTORYGROUPLISTLOADER_H
#define FACTORYGROUPLISTLOADER_H

#include <Level/DataLoader.h>
#include <Level/FactoryGroupListData.h>
#include <Level/FactoryGroupData.h>
class XmlResourceProvider;
class TiXmlElement;
class FactoryGroupListLoader : public DataLoader<FactoryGroupListLoader, FactoryGroupListData>
{
    public:
        FactoryGroupListLoader(XmlResourceProvider* _provider);
        virtual ~FactoryGroupListLoader();
        FactoryGroupListData* virtualLoad(const std::string& _listName, FactoryGroupListData* list);
    protected:
    private:
        XmlResourceProvider* provider;
        FactoryGroupData* loadFactoryGroup(const std::string& _listName, TiXmlElement* _element);
        void loadChild(FactoryGroupData::Child* _child, TiXmlElement* _element);
};

#endif // FACTORYGROUPLISTLOADER_H
