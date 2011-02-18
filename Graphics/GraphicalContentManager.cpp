#include "GraphicalContentManager.h"
#include <string>
#include <Graphics/Contexts/TextureContext.h>
#include <Graphics/Contexts/ShaderContext.h>
MaterialDef::MaterialDef()
{
    textureName = shaderName = NULL;
}
MaterialDef::MaterialDef(char* _textureName)
{
    textureName = _textureName;
    shaderName = NULL;
}
GraphicalContentManager::GraphicalContentManager()
{
    //ctor
    textures.push(0);
    MaterialDef blank;
    addMaterial(blank);
    MaterialDef player("player.bmp");
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
MaterialContext* GraphicalContentManager::getMaterial(unsigned int reference)
{
    materials[reference].grab();
    return &materials[0] + reference;
}
unsigned int GraphicalContentManager::findMaterial(const char* materialName)
{
    return materialMap[materialName];
}
unsigned int GraphicalContentManager::addMaterial(MaterialDef& def)
{
    unsigned int ret = materials.size();
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
    return ret;
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

























