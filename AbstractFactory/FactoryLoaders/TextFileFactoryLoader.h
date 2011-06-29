#ifndef TEXTFILEFACTORYLOADER_H
#define TEXTFILEFACTORYLOADER_H

#include <AbstractFactory/FactoryLoader.h>


class TextFileFactoryLoader : public FactoryLoader
{
    public:
        TextFileFactoryLoader(const char* filename);
        virtual ~TextFileFactoryLoader();
        bool isValid();
        bool next();
    protected:
    private:
        std::ifstream file;
};

#endif // TEXTFILEFACTORYLOADER_H
