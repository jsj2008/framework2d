#include "XmlResourceManager.h"
#include <Log/Log.h>

XmlResourceManager::XmlResourceManager()
{
    //ctor
}

XmlResourceManager::~XmlResourceManager()
{
    //dtor
    for (auto iter = loadedDocuments.begin(); iter != loadedDocuments.end(); iter++)
    {
        delete iter->second;
    }
}

TiXmlHandle XmlResourceManager::getHandle(const std::string& _name)
{
    unsigned int dotIndex = _name.find('.');
    std::string documentName = _name.substr(0, dotIndex + 4);
    TiXmlDocument* document = getDocument(documentName);

    TiXmlHandle element = document->RootElement();
    std::string tailname = _name.substr(dotIndex + 5, _name.size());
    while (tailname.size() != 0)
    {
        int slashIndex = tailname.find('/');
        if (slashIndex == -1)
        {
            std::string folderName = tailname.substr(0, slashIndex);
            return getLeaf(element, folderName);
        }
        else
        {
            std::string folderName = tailname.substr(0, slashIndex);
            tailname = tailname.substr(slashIndex + 1, tailname.size());
            element = getFolder(element, folderName);
        }
    }
    if (element.ToElement() == nullptr)
    {
        g_Log.error(std::string("Failed to get xml element ") + _name);
    }
    return element;
}

TiXmlDocument* XmlResourceManager::getDocument(const std::string& _filename)
{
    auto iter = loadedDocuments.find(_filename);
    if (iter == loadedDocuments.end())
    {
        TiXmlDocument* document = loadDocument(_filename);
        loadedDocuments[_filename] = document;
        return document;
    }
    else return iter->second;
}









