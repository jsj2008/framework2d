#ifndef XMLRESOURCEPROVIDER_H
#define XMLRESOURCEPROVIDER_H

#include <Level/XmlResourceManager.h>

class XmlResourceProvider : public XmlResourceManager
{
    public:
        XmlResourceProvider();
        virtual ~XmlResourceProvider();
    protected:
    private:
        TiXmlDocument* loadDocument(const std::string& _filename);
        TiXmlHandle getFolder(TiXmlHandle _handle, const std::string& _folderName);
        TiXmlHandle getLeaf(TiXmlHandle _handle, const std::string& _folderName);
};

#endif // XMLRESOURCEPROVIDER_H
