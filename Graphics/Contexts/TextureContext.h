#ifndef TEXTURECONTEXT_H
#define TEXTURECONTEXT_H

#include <Graphics/Contexts/GraphicalContext.h>

class TextureContext: public GraphicalContext
{
    public:
        TextureContext(const char* _textureName = NULL);
        virtual ~TextureContext();
        void assertDelete();
        void bind();
    protected:
    private:
        void load();
        void unload();
};

#endif // TEXTURECONTEXT_H
