#ifndef TEXTURECONTEXT_H
#define TEXTURECONTEXT_H


class TextureContext
{
    public:
        TextureContext(const char* _textureName);
        void bindTexture();
        /// These are the reference counting functions
        void grab(); /// ++
        void release(); /// --
    protected:
    private:
        unsigned int texture;
        unsigned int referenceCount;
        char textureName[32];
        void loadFromFile();

        friend class GraphicalContentManager;
        virtual ~TextureContext();
};

#endif // TEXTURECONTEXT_H
