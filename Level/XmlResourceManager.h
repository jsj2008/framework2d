#ifndef XMLRESOURCEMANAGER_H
#define XMLRESOURCEMANAGER_H

#include <tinyxml.h>
#include <unordered_map>

class XmlResourceManager
{
    public:
        XmlResourceManager();
        virtual ~XmlResourceManager();
        TiXmlHandle getHandle(const std::string& _name);
    protected:
        TiXmlDocument* getDocument(const std::string& _filename);
        virtual TiXmlDocument* loadDocument(const std::string& _filename)=0;
        virtual TiXmlHandle getFolder(TiXmlHandle _handle, const std::string& _folderName)=0;
        virtual TiXmlHandle getLeaf(TiXmlHandle _handle, const std::string& _folderName)=0;
        std::unordered_map<std::string, TiXmlDocument*> loadedDocuments;
    private:
};

#endif // XMLRESOURCEMANAGER_H
