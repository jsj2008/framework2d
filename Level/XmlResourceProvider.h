#ifndef XMLRESOURCEPROVIDER_H
#define XMLRESOURCEPROVIDER_H

#include <tinyxml.h>
#include <string>
#include <unordered_map>

class XmlResourceProvider
{
    public:
        XmlResourceProvider();
        virtual ~XmlResourceProvider();
        TiXmlHandle getHandle(const std::string& _name);
    protected:
    private:
        std::unordered_map<std::string, TiXmlDocument*> loadedDocuments;
        TiXmlDocument* loadDocument(const std::string& _filename);
        TiXmlHandle getFolder(TiXmlHandle _handle, const std::string& _folderName);
};

#endif // XMLRESOURCEPROVIDER_H
