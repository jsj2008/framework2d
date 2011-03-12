#include "GraphicalContentManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <Graphics/Contexts/TextureContext.h>
#include <Graphics/Contexts/ShaderContext.h>
GraphicalContentManager::MaterialDef::MaterialDef(const char* _materialName)
{
    strcpy(materialName,_materialName);
    textureName[0] = shaderName[0] = '\0';
}
GraphicalContentManager::MaterialDef::MaterialDef(const char* _materialName, const char* _textureName)
{
    strcpy(materialName,_materialName);
    strcpy(textureName,_textureName);
    shaderName[0] = '\0';
}
bool GraphicalContentManager::MaterialDef::parseMaterialFile()
{
    std::string fullFileName("Resources/Graphics/Materials/");
    fullFileName.append(materialName);
    fullFileName.append(".txt");
    std::ifstream file(fullFileName.c_str()); /// FIXME passing the string directly gives a linker error. Will probably be fixed in a newer version of g++
    if (!file.good())
    {
        std::cout << "Failed to open " << fullFileName << " for reading" << std::endl;
        return false;
    }
    while (file.good())
    {
        std::string input;
        file >> input;
        if (input == "texture")
        {
            file >> input;
            if (input == "=")
            {
                file >> textureName;
            }
            else
            {
                std::cout << "Expected a \"=\"" << std::endl;
            }
        }
        else if (input == "shader")
        {
            file >> input;
            if (input == "=")
            {
                file >> shaderName;
            }
            else
            {
                std::cout << "Expected a \"=\"" << std::endl;
            }
        }
        else
        {
            std::cout << "Unrecognised token: " << input << std::endl;
        }
    }
    fullFileName.replace(fullFileName.end()-4,fullFileName.end(),".mat");
    std::ofstream outfile(fullFileName.c_str(),std::ios::binary); /// FIXME also
    outfile.write((char*)this,sizeof(MaterialDef));
    return true;
}
GraphicalContentManager::GraphicalContentManager()
{
    //ctor
    textureMap[""] = TextureContext("");
    MaterialDef blank("");
    addMaterial(blank);
}

GraphicalContentManager::~GraphicalContentManager()
{
    //dtor
    materialMap.clear();
}
MaterialContext* GraphicalContentManager::getMaterial(const char* materialName)
{
    auto iter = materialMap.find(materialName);
    MaterialContext* material;
    if (iter == materialMap.end())
    {
        MaterialDef def(materialName);
        bool success = def.parseMaterialFile();
        if (success)
            material = addMaterial(def);
        else material = &materialMap[""];
    }
    else material = &iter->second;
    material->grab();
    return material;
}
StaticModelContext* GraphicalContentManager::getModel(const char* modelName)
{
    StaticModelContext* model = &staticModelMap[modelName];
    model->grab();
    return model;
}
MaterialContext* GraphicalContentManager::addMaterial(MaterialDef& def)
{
    TextureContext* texture;
    if (def.textureName[0] == '\0')
    {
        texture = &textureMap.begin()->second;
    }
    else
    {
        texture = getTexture(def.textureName);
    }
    return &(materialMap[def.materialName] = MaterialContext(texture));
}
TextureContext* GraphicalContentManager::getTexture(const char* name)
{
    if (name[0] == '\0')
    {
        return &textureMap.begin()->second;
    }
    TextureContext* texture;
    auto iter = textureMap.find(name);
    if (iter == textureMap.end())
    {
        texture = &(textureMap[name] = TextureContext(name));
    }
    else texture = &iter->second;
    return texture;
}

























