#ifndef ENTITYLISTLOADER_H
#define ENTITYLISTLOADER_H

#include <Level/DataLoader.h>
#include <Level/EntityListData.h>
#include <string>
class XmlResourceProvider;

class EntityListLoader : public DataLoader<EntityListLoader, EntityListData>
{
    public:
        EntityListLoader(XmlResourceProvider* _provider);
        virtual ~EntityListLoader();
        EntityListData* virtualLoad(const std::string& _listName);
    protected:
    private:
        XmlResourceProvider* provider;
};

#endif // ENTITYLISTLOADER_H
