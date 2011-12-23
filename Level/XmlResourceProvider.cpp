#include "XmlResourceProvider.h"

XmlResourceProvider::XmlResourceProvider()
{
    //ctor
}

XmlResourceProvider::~XmlResourceProvider()
{
    //dtor
}


TiXmlDocument* XmlResourceProvider::loadDocument(const std::string& _filename)
{
    TiXmlDocument* document = new TiXmlDocument("Resources/" + _filename);
    document->LoadFile();
    return document;
}

TiXmlHandle XmlResourceProvider::getFolder(TiXmlHandle _handle, const std::string& _folderName)
{
    for (TiXmlElement* element = _handle.FirstChildElement().Element(); element; element = element->NextSiblingElement())
    {
        const char* name = element->Attribute("Name");
        if (name != nullptr && name == _folderName)
        {
            return element;
        }
    }
    return nullptr;
}
TiXmlHandle XmlResourceProvider::getLeaf(TiXmlHandle _handle, const std::string& _folderName)
{
    return getFolder(_handle, _folderName);
}
















