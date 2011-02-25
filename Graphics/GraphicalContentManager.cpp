#include "GraphicalContentManager.h"
#include <string>
#include <Graphics/Contexts/TextureContext.h>
#include <Graphics/Contexts/ShaderContext.h>
MaterialDef::MaterialDef(char* _materialName)
{
    materialName = _materialName;
    textureName = shaderName = NULL;
}
MaterialDef::MaterialDef(char* _materialName, char* _textureName)
{
    materialName = _materialName;
    textureName = _textureName;
    shaderName = NULL;
}
GraphicalContentManager::GraphicalContentManager()
{
    //ctor
    textures.push(NULL);
    MaterialDef blank("");
    addMaterial(blank);
    MaterialDef player("player", "player.bmp");
    addMaterial(player);
}

GraphicalContentManager::~GraphicalContentManager()
{
    //dtor
    for (int i = 0; i < materials.size(); i++)
    {
        materials[i].assertDelete();
    }
}
MaterialContext* GraphicalContentManager::getMaterial(const char* materialName)
{
    MaterialContext* material = &materials[materialMap[materialName]];
    material->grab();
    return material;
}
unsigned int GraphicalContentManager::findMaterial(const char* materialName)
{
    return materialMap[materialName];
}
unsigned int GraphicalContentManager::addMaterial(MaterialDef& def)
{
    unsigned int index = materials.size();
    TextureContext* texture;
    if (def.textureName == NULL)
    {
        texture = &textures[0];
    }
    else
    {
        texture = addTexture(def.textureName);
    }
    materials.push(MaterialContext(texture));
    materialMap[def.materialName] = index;
    return index;
}
TextureContext* GraphicalContentManager::addTexture(const char* name)
{
    unsigned int index = textureMap[name];
    if (index == 0)
    {
        index = textures.size();
        textures.push(TextureContext(name));
        textureMap[name] = index;
    }
    return &textures[index];
}

























