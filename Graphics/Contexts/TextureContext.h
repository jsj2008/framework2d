#ifndef TEXTURECONTEXT_H
#define TEXTURECONTEXT_H


#define MAX_FILENAME 32
class TextureContext
{
    public:
        TextureContext();
        virtual ~TextureContext();
        void assertDelete();
        TextureContext(const char* _textureName);
        void bindTexture();
        /// These are the reference counting functions
        void grab(); /// ++
        void release(); /// --
    protected:
    private:
        unsigned int texture;
        unsigned int referenceCount;
        char textureName[MAX_FILENAME];
        void loadFromFile();
};

#endif // TEXTURECONTEXT_H
