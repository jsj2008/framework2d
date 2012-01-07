#ifndef TEXTURECONTEXT_H
#define TEXTURECONTEXT_H

#include <Graphics/Contexts/GraphicalContext.h>

class TextureContext: public GraphicalContext
{
    public:
        TextureContext(const char* _textureName = nullptr);
        virtual ~TextureContext();
        void assertDelete();
        void bind();
    protected:
    private:
        unsigned int texture;
        void load();
        void unload();
};

#endif // TEXTURECONTEXT_H
