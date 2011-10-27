#include <AbstractFactory/FactoryLoader.h>
#ifndef TEXTFILEFACTORYLOADER_H
#define TEXTFILEFACTORYLOADER_H

#include <tinyxml.h>

class TextFileFactoryLoader : public FactoryLoader
{
    public:
        TextFileFactoryLoader(const char* filename, AbstractFactories* _factories, bool logUndefined = false);
        virtual ~TextFileFactoryLoader();
        bool isValid();
        bool next();
        std::vector<std::string> getUndefinedLog(){return mvalues.getUndefinedLog();}
    protected:
    private:
        TiXmlDocument doc;
        TiXmlHandle handle;
};

#endif // TEXTFILEFACTORYLOADER_H
