#ifndef GRAPHICALCONTENTMANAGER_H
#define GRAPHICALCONTENTMANAGER_H

#include <Graphics/Contexts/MaterialContext.h>
#include <Graphics/Contexts/StaticModelContext.h>
#include <Graphics/Contexts/ShaderContext.h>
#include <Graphics/Contexts/TextureContext.h>
#include <unordered_map>
#include <locale>
#include <vector>
#include <string>
#include <Types/MyStack.h>
class Icon;

class GraphicalContentManager
{
    public:
        GraphicalContentManager();
        virtual ~GraphicalContentManager();
        MaterialContext* getMaterial(const char* name);
        TextureContext* getTexture(const char* name);
        StaticModelContext* getModel(const char* name);
    protected:
    private:
        struct MaterialDef
        {
            MaterialDef(const char* _materialName);
            MaterialDef(const char* _materialName, const char* _textureName, const char* _shaderName);
            MaterialDef(const char* _materialName, const char* _textureName);
            void parseMaterialFile();
            char materialName[32];
            char textureName[32];
            char shaderName[32];
        };
        MaterialContext* addMaterial(MaterialDef& def);
        TextureContext* addTexture(const char* name); /// These two functions check for its previous existance, addMaterial does not
        ShaderContext* addShader(const char* name);
        std::unordered_map<std::string, TextureContext> textureMap;
        std::unordered_map<std::string, ShaderContext> shaderMap;
        std::unordered_map<std::string, StaticModelContext> staticModelMap;
        std::unordered_map<std::string, MaterialContext> materialMap;
};
#endif // GRAPHICALCONTENTMANAGER_H
