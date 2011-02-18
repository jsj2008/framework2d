#ifndef MaterialContext_H
#define MaterialContext_H

#define MAX_FILENAME 32
class TextureContext;
class ShaderContext;
class MaterialContext
{
    public:
        MaterialContext();
        virtual ~MaterialContext();
        void assertDelete();
        MaterialContext(TextureContext* _TextureContext);
        void bindTexture();
        /// These are the reference counting functions
        void grab(); /// ++
        void release(); /// --
    protected:
    private:
        TextureContext* mTextureContext;
};

#endif // MaterialContext_H
