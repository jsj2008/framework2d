#ifndef MaterialContext_H
#define MaterialContext_H

#include <Graphics/Contexts/GraphicalContext.h>
class TextureContext;
class ShaderContext;

class MaterialContext: public GraphicalContext
{
    public:
        MaterialContext(const char* _name = nullptr);
        virtual ~MaterialContext();
        MaterialContext(TextureContext* _TextureContext);
        void bind();
    protected:
    private:
        void vGrab();
        void vRelease();
        void load(){}
        void unload(){}
        TextureContext* mTextureContext;
};

#endif // MaterialContext_H
