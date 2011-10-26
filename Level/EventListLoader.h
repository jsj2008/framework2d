#ifndef EVENTLISTLOADER_H
#define EVENTLISTLOADER_H

#include <Level/DataLoader.h>
#include <Level/EventListData.h>
#include <string>
class EventListData;
class XmlResourceProvider;

class EventListLoader : public DataLoader<EventListLoader, EventListData>
{
    public:
        EventListLoader(XmlResourceProvider* _provider);
        virtual ~EventListLoader();
        EventListData* virtualLoad(const std::string& _listName);
    protected:
    private:
        XmlResourceProvider* provider;
};

#endif // EVENTLISTLOADER_H
