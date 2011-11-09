#ifndef XMLDATASAVER_H
#define XMLDATASAVER_H

#include <Level/XmlResourceManager.h>

class XmlDataSaver : public XmlResourceManager
{
    public:
        XmlDataSaver();
        virtual ~XmlDataSaver();
        TiXmlHandle createElement(const std::string& _address, const std::string& _type);
    protected:
    private:
        std::string currentQueriedType;
        TiXmlDocument* loadDocument(const std::string& _filename);
        void closingDocument(TiXmlDocument* _document);
        TiXmlHandle getFolder(TiXmlHandle _handle, const std::string& _folderName);
        TiXmlHandle getLeaf(TiXmlHandle _handle, const std::string& _folderName);
};

#endif // XMLDATASAVER_H
