#ifndef EVENTLISTDATA_H
#define EVENTLISTDATA_H

#include <Level/LoadedData.h>
class EventListData : public LoadedData
{
    public:
        EventListData(const std::string& _address);
        virtual ~EventListData();
    protected:
    private:
};

#endif // EVENTLISTDATA_H
