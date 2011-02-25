#ifndef GRAPHICALCONTENTMANAGER_H
#define GRAPHICALCONTENTMANAGER_H

#include <Graphics/Contexts/MaterialContext.h>
#include <unordered_map>
#include <locale>
#include <vector>
#include <string>
#include <Types/MyStack.h>
struct MaterialDef
{
    MaterialDef(char* _materialName);
    MaterialDef(char* _materialName, char* _textureName, char* _shaderName);
    MaterialDef(char* _materialName, char* _textureName);
    char* materialName;
    char *textureName;
    char *shaderName;
};
class GraphicalContentManager
{
    public:
        GraphicalContentManager();
        virtual ~GraphicalContentManager();
        MaterialContext* getMaterial(const char* name);
        unsigned int findMaterial(const char* materialName);
    protected:
    private:
        unsigned int addMaterial(MaterialDef& def);
        TextureContext* addTexture(const char* name); /// These two functions check for its previous existance, addMaterial does not
        ShaderContext* addShader(const char* name);
        MyStack<MaterialContext> materials;
        MyStack<TextureContext> textures;
        MyStack<ShaderContext> shaders;
        std::unordered_map<std::string, unsigned int> materialMap;
        std::unordered_map<std::string, unsigned int> textureMap;
        std::unordered_map<std::string, unsigned int> shaderMap;
};
#endif // GRAPHICALCONTENTMANAGER_H
