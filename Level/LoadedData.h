#ifndef LOADEDDATA_H
#define LOADEDDATA_H

#include <string>

class LoadedData
{
    public:
        LoadedData(const std::string& _address);
        virtual ~LoadedData();
        void increment(){referenceCount++;}
        void decrement();
    protected:
    private:
        std::string address;
        unsigned short referenceCount;
};

#endif // LOADEDDATA_H
