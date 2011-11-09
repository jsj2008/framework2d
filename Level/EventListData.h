#ifndef EVENTLISTDATA_H
#define EVENTLISTDATA_H

#include <Level/LoadedData.h>
class TiXmlElement;

class EventListData : public LoadedData
{
    public:
        EventListData();
        virtual ~EventListData();
    protected:
    private:
        void virtualSave(XmlDataSaver* _saver, const std::string* _address);
};

#endif // EVENTLISTDATA_H
