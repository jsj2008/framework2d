#include "XmlResourceProvider.h"
#include <Log/Log.h>

XmlResourceProvider::XmlResourceProvider()
{
    //ctor
}

XmlResourceProvider::~XmlResourceProvider()
{
    //dtor
}

TiXmlHandle XmlResourceProvider::getHandle(const std::string& _name)
{
    unsigned int dotIndex = _name.find('.');
    std::string documentName = _name.substr(0, dotIndex + 4);
    TiXmlDocument* document = loadDocument(documentName);

    TiXmlHandle element = document->RootElement();
    std::string tailname = _name.substr(dotIndex + 5, _name.size());
    while (tailname.size() != 0)
    {
        int slashIndex = tailname.find('/');
        if (slashIndex == -1)
        {
            std::string folderName = tailname.substr(0, slashIndex);
            element = getFolder(element, folderName);
            break;
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

TiXmlDocument* XmlResourceProvider::loadDocument(const std::string& _filename)
{
    auto iter = loadedDocuments.find(_filename);
    if (iter == loadedDocuments.end())
    {
        TiXmlDocument* document = new TiXmlDocument("Resources/" + _filename);
        document->LoadFile();
        loadedDocuments[_filename] = document;
        return document;
    }
    else return iter->second;
}

TiXmlHandle XmlResourceProvider::getFolder(TiXmlHandle _handle, const std::string& _folderName)
{
    for (TiXmlElement* element = _handle.FirstChildElement().Element(); element; element = element->NextSiblingElement())
    {
        const char* name = element->Attribute("name");
        if (name != nullptr && name == _folderName)
        {
            return element;
        }
    }
    return nullptr;
}
















