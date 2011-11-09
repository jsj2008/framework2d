#include "XmlDataSaver.h"

XmlDataSaver::XmlDataSaver()
{
    //ctor
}

XmlDataSaver::~XmlDataSaver()
{
    //dtor
    for (auto iter = loadedDocuments.begin(); iter != loadedDocuments.end(); iter++)
    {
        bool success = iter->second->SaveFile();
        assert(success);
    }
}

TiXmlHandle XmlDataSaver::createElement(const std::string& _address, const std::string& _type)
{
    assert(currentQueriedType == "");
    currentQueriedType = _type;
    TiXmlHandle handle = getHandle(_address);
    currentQueriedType = "";
    return handle;
}

TiXmlDocument* XmlDataSaver::loadDocument(const std::string& _filename)
{
    TiXmlDocument* document = new TiXmlDocument("Resources/Output/" + _filename);
    TiXmlElement* root = new TiXmlElement("Root");
    root->SetAttribute("Name", _filename);
    document->LinkEndChild(root);
    //document->Clear();
    return document;
}
TiXmlHandle XmlDataSaver::getFolder(TiXmlHandle _handle, const std::string& _folderName)
{
    for (TiXmlElement* element = _handle.FirstChildElement().Element(); element; element = element->NextSiblingElement())
    {
        const char* name = element->Attribute("Name");
        if (name != nullptr && name == _folderName)
        {
            return element;
        }
    }
    TiXmlElement* element = new TiXmlElement("Collection");
    element->SetAttribute("Name", _folderName);
    _handle.Element()->LinkEndChild(element);
    return element;
}
TiXmlHandle XmlDataSaver::getLeaf(TiXmlHandle _handle, const std::string& _folderName)
{
    for (TiXmlElement* element = _handle.FirstChildElement().Element(); element; element = element->NextSiblingElement())
    {
        const char* name = element->Attribute("Name");
        if (name != nullptr && name == _folderName)
        {
            element->SetValue(currentQueriedType);
            return element;
        }
    }
    TiXmlElement* element = new TiXmlElement(currentQueriedType);
    element->SetAttribute("Name", _folderName);
    _handle.Element()->LinkEndChild(element);
    return element;
}

















