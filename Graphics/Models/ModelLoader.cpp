#include "ModelLoader.h"
#include <Graphics/Models/Model.h>
#include <Graphics/Models/VertexArray.h>
#include <Log/Log.h>

ModelLoader::ModelLoader()
{
    //ctor
}

ModelLoader::~ModelLoader()
{
    //dtor
    for (auto i = loadedDocuments.begin(); i != loadedDocuments.end(); i++)
    {
        delete i->second;
    }
}
#include <iostream>
Model* ModelLoader::loadModel(const std::string& _address)
{
    TiXmlHandle handle = getXmlNode(_address);
    if (handle.Element() == nullptr)
    {
        g_Log.error("Unable to find model " + _address);
    }
    if (handle.Element()->Value() != std::string("Model"))
    {
        g_Log.error(_address + " is not a model");
    }
    Model* model = new Model();
    TiXmlElement* vertexAttribute = handle.FirstChild("VertexSpec").FirstChild("VertexAttribute").Element();
    for( ; vertexAttribute; vertexAttribute = vertexAttribute->NextSiblingElement())
    {
        std::string attribute = vertexAttribute->Attribute("Name");
        VertexArray* array = loadVertexArray(vertexAttribute->Attribute("Array"));
        model->setVertexAttribute(attribute, array);
    }
    return model;
}

VertexArray* ModelLoader::loadVertexArray(const std::string& _address)
{
    VertexArray* array = new VertexArray;
    return array;
}
std::string getSeparater(const std::string& _address, unsigned int* _iter)
{
    if (*_iter >= _address.size())
        throw -1;
    int startPoint = *_iter;
    while (true)
    {
        if (_address[*_iter] == '/')
        {
            (*_iter)++;
            return _address.substr(startPoint, ((*_iter)-1)-startPoint);
        }
        else
        {
            if (_address[*_iter] == '\0')
            {
                (*_iter)++;
                return _address.substr(startPoint, ((*_iter)-1)-startPoint);
            }
            (*_iter)++;
        }
    }
}
TiXmlHandle ModelLoader::getXmlNode(const std::string& _address)
{
    unsigned int stringIter = 0;
    std::string filename = getSeparater(_address, &stringIter);
    TiXmlHandle handle = getDocument(filename);

    try
    {
        while (true)
        {
            std::string nextSeparater = getSeparater(_address, &stringIter);
            for (TiXmlElement* element = handle.FirstChildElement().Element(); element; element = element->NextSiblingElement())
            {
                if (element->Attribute("Name") == nextSeparater)
                {
                    handle = element;
                }
            }
        }
    }
    catch (int i)
    {
        return handle;
    }
    //g_Log.error("Unable to find node " + _address);
}

TiXmlHandle ModelLoader::getDocument(const std::string& _filename)
{
    auto iter = loadedDocuments.find(_filename);
    if (iter == loadedDocuments.end())
    {
        TiXmlDocument* document = new TiXmlDocument(_filename);
        if (!document->LoadFile())
        {
            delete document;
            g_Log.error("Unable to find xml file " + _filename);
        }
        loadedDocuments[_filename] = document;
        return document;
    }
    else
    {
        return iter->second;
    }
}
