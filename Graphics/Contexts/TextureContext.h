#ifndef TEXTURECONTEXT_H
#define TEXTURECONTEXT_H


class TextureContext
{
    public:
        TextureContext(const char* _textureName);
        virtual ~TextureContext();
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
};

#endif // TEXTURECONTEXT_H
