#ifndef LOADEDDATA_H
#define LOADEDDATA_H

#include <string>
class XmlDataSaver;

class LoadedData
{
    public:
        LoadedData();
        virtual ~LoadedData();
        void init(const std::string& _address);
        void increment(){referenceCount++;}
        void decrement(); /// Automatically deletes self
        void save(XmlDataSaver* _saver, const std::string* _address);
    protected:
        std::string address;
    private:
        virtual void virtualSave(XmlDataSaver* _saver, const std::string* _address)=0;
        unsigned short referenceCount;
};

#endif // LOADEDDATA_H
