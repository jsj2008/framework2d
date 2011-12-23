#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <unordered_map>
#include <tinyxml.h>
class Model;
class VertexArray;

class ModelLoader
{
    public:
        ModelLoader();
        virtual ~ModelLoader();
        Model* loadModel(const std::string& _address);
        TiXmlHandle getXmlNode(const std::string& _address);
    protected:
    private:
        std::unordered_map<std::string, TiXmlDocument*> loadedDocuments;
        TiXmlHandle getDocument(const std::string& _filename);

        VertexArray* loadVertexArray(const std::string& _address);
};

#endif // MODELLOADER_H
