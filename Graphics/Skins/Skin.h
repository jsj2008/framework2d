#ifndef SKIN_H
#define SKIN_H

class b2Body;
class MaterialContext;
enum SkinType
{
    eStaticSkinType,
    eConvexPolygonSkinType,
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
        MaterialContext* material;
        unsigned int program;
};

#endif // SKIN_H
