#ifndef SKIN_H
#define SKIN_H

class b2Body;
class TextureContext;
enum SkinType
{
    eStaticSkinType,
    eSkinTypeMax
};
class Skin
{
    public:
        Skin();
        virtual ~Skin();
        void render(b2Body* body);
        virtual void vRender()=0;
        virtual SkinType getType()=0;
    protected:
    private:
        friend class GraphicsManager;
        TextureContext* texture;
        unsigned int program;
};

#endif // SKIN_H
