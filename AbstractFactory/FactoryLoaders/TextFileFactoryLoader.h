#ifndef TEXTFILEFACTORYLOADER_H
#define TEXTFILEFACTORYLOADER_H

#include <AbstractFactory/FactoryLoader.h>


class TextFileFactoryLoader : public FactoryLoader
{
    public:
        TextFileFactoryLoader(const char* filename, bool logUndefined = false);
        virtual ~TextFileFactoryLoader();
        bool isValid();
        bool next();
        std::vector<std::string> getUndefinedLog(){return mvalues.getUndefinedLog();}
    protected:
    private:
        std::ifstream file;
};

#endif // TEXTFILEFACTORYLOADER_H
