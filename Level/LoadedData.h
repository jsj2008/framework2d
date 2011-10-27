#ifndef LOADEDDATA_H
#define LOADEDDATA_H

#include <string>
class XmlDataSaver;

class LoadedData
{
    public:
        LoadedData(const std::string& _address);
        virtual ~LoadedData();
        void increment(){referenceCount++;}
        void decrement();
        void save(XmlDataSaver* _saver);
    protected:
    private:
        virtual void virtualSave(XmlDataSaver* _saver)=0;
        std::string address;
        unsigned short referenceCount;
};

#endif // LOADEDDATA_H
